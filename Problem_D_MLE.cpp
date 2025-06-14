#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int MOD = 1000000007;

struct State {
    int used_east;
    int used_west;
    int last_mountain;
    long long total_length;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, m;
        long long x, C, D;
        cin >> n >> m >> x >> C >> D;
        
        vector<long long> A(n), B(m);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> B[i];
        }
        
        queue<State> q;
        long long result = 0;
        
        // Start with single trails
        for (int i = 0; i < n; i++) {
            State state = {1 << i, 0, 0, A[i]};
            q.push(state);
            if (A[i] >= C && A[i] <= D) {
                result = (result + 1) % MOD;
            }
        }
        
        for (int i = 0; i < m; i++) {
            State state = {0, 1 << i, 1, B[i]};
            q.push(state);
            if (B[i] >= C && B[i] <= D) {
                result = (result + 1) % MOD;
            }
        }
        
        // BFS to explore all possible routes
        while (!q.empty()) {
            State curr = q.front();
            q.pop();
            
            // Try extending to the other mountain
            if (curr.last_mountain == 0) { // Last was East, go to West
                for (int i = 0; i < m; i++) {
                    if (!(curr.used_west & (1 << i))) {
                        long long new_length = curr.total_length + x + B[i];
                        if (new_length <= D) {
                            State new_state = {curr.used_east, curr.used_west | (1 << i), 1, new_length};
                            q.push(new_state);
                            
                            if (new_length >= C) {
                                result = (result + 1) % MOD;
                            }
                        }
                    }
                }
            } else { // Last was West, go to East
                for (int i = 0; i < n; i++) {
                    if (!(curr.used_east & (1 << i))) {
                        long long new_length = curr.total_length + x + A[i];
                        if (new_length <= D) {
                            State new_state = {curr.used_east | (1 << i), curr.used_west, 0, new_length};
                            q.push(new_state);
                            
                            if (new_length >= C) {
                                result = (result + 1) % MOD;
                            }
                        }
                    }
                }
            }
        }
        
        cout << result << endl;
    }
    
    return 0;
}
