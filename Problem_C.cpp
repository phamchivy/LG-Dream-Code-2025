#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeDP {
    vector<vector<int>> children;
    vector<long long> value;
    vector<long long> dp_take;
    vector<long long> dp_not_take;
    int n;
    
    TreeDP(int n) : n(n) {
        children.resize(n + 1);
        value.resize(n + 1);
        dp_take.resize(n + 1);
        dp_not_take.resize(n + 1);
    }
    
    void dfs(int u) {
        // Base case: leaf node
        if (children[u].empty()) {
            dp_take[u] = value[u];
            dp_not_take[u] = 0;
            return;
        }
        
        // Process all children first
        for (int v : children[u]) {
            dfs(v);
        }
        
        // Case 1: Take node u (condition 1: children cannot be taken)
        dp_take[u] = value[u];
        for (int v : children[u]) {
            dp_take[u] += dp_not_take[v];
        }
        
        // Case 2: Don't take node u
        // Condition 2: at least one child must be taken
        
        // Calculate sum if we optimally choose each child
        long long sum_optimal = 0;
        bool has_child_wanting_to_be_taken = false;
        
        for (int v : children[u]) {
            long long best_for_child = max(dp_take[v], dp_not_take[v]);
            sum_optimal += best_for_child;
            if (dp_take[v] > dp_not_take[v]) {
                has_child_wanting_to_be_taken = true;
            }
        }
        
        if (has_child_wanting_to_be_taken) {
            // At least one child "wants" to be taken, so condition 2 is satisfied
            dp_not_take[u] = sum_optimal;
        } else {
            // No child "wants" to be taken, we must force at least one
            dp_not_take[u] = -1e18;
            
            for (int v : children[u]) {
                // Force child v to be taken
                long long score = dp_take[v];
                for (int w : children[u]) {
                    if (w != v) {
                        score += max(dp_take[w], dp_not_take[w]);
                    }
                }
                dp_not_take[u] = max(dp_not_take[u], score);
            }
        }
    }
    
    long long solve(int root) {
        dfs(root);
        return max(dp_take[root], dp_not_take[root]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        TreeDP tree(n);
        
        for (int i = 1; i <= n; i++) {
            cin >> tree.value[i];
        }
        
        int root = -1;
        for (int i = 1; i <= n; i++) {
            int p;
            cin >> p;
            if (p == 0) {
                root = i;
            } else {
                tree.children[p].push_back(i);
            }
        }
        
        cout << tree.solve(root) << endl;
    }
    
    return 0;
}
