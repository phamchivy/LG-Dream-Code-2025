#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;

int n, m;
long long x, C, D;
vector<long long> A, B;
vector<int> orderA, orderB; // Sắp xếp theo thứ tự tăng dần để pruning tốt hơn
unordered_map<long long, long long> memo;

// Encode state compactly
long long encode(int used_east, int used_west, int last_mountain, long long length) {
    // Chỉ lưu length trong khoảng hữu hạn để tránh collision
    long long compressed_length = min(length, D + 1);
    return ((long long)used_east << 42) | ((long long)used_west << 22) | 
           ((long long)last_mountain << 21) | compressed_length;
}

long long dfs(int used_east, int used_west, int last_mountain, long long total_length) {
    // Early pruning mạnh
    if (total_length > D) return 0;
    
    // Tối ưu: nếu đã sử dụng hết trails
    if (used_east == (1 << n) - 1 && used_west == (1 << m) - 1) {
        return (total_length >= C && total_length <= D) ? 1 : 0;
    }
    
    // Memoization với encoding tối ưu
    long long state = encode(used_east, used_west, last_mountain, total_length);
    if (memo.count(state)) {
        return memo[state];
    }
    
    long long result = 0;
    if (total_length >= C && total_length <= D) {
        result = 1;
    }
    
    // Pruning: tính minimum possible length
    long long min_remaining = 0;
    int remaining_trails = 0;
    
    if (last_mountain == 0) { // Last was East, go to West
        for (int idx = 0; idx < m; idx++) {
            int i = orderB[idx];
            if (!(used_west & (1 << i))) {
                long long new_length = total_length + x + B[i];
                if (new_length <= D) {
                    result = (result + dfs(used_east, used_west | (1 << i), 1, new_length)) % MOD;
                }
                // Early break nếu đã quá D
                else break;
            }
        }
    } else { // Last was West, go to East
        for (int idx = 0; idx < n; idx++) {
            int i = orderA[idx];
            if (!(used_east & (1 << i))) {
                long long new_length = total_length + x + A[i];
                if (new_length <= D) {
                    result = (result + dfs(used_east | (1 << i), used_west, 0, new_length)) % MOD;
                }
                // Early break nếu đã quá D
                else break;
            }
        }
    }
    
    // Giới hạn memo size để tránh memory overflow
    if (memo.size() < 500000) {
        memo[state] = result;
    }
    
    return result;
}

long long solve() {
    memo.clear();
    
    // Sắp xếp trails theo độ dài để pruning hiệu quả hơn
    orderA.resize(n);
    orderB.resize(m);
    for (int i = 0; i < n; i++) orderA[i] = i;
    for (int i = 0; i < m; i++) orderB[i] = i;
    
    sort(orderA.begin(), orderA.end(), [](int a, int b) { return A[a] < A[b]; });
    sort(orderB.begin(), orderB.end(), [](int a, int b) { return B[a] < B[b]; });
    
    long long result = 0;
    
    // Start với trails ngắn nhất trước để pruning tốt hơn
    for (int i = 0; i < n; i++) {
        if (A[i] <= D) { // Chỉ bắt đầu với trails có thể
            result = (result + dfs(1 << i, 0, 0, A[i])) % MOD;
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (B[i] <= D) { // Chỉ bắt đầu với trails có thể
            result = (result + dfs(0, 1 << i, 1, B[i])) % MOD;
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n >> m >> x >> C >> D;
        
        A.resize(n);
        B.resize(m);
        
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> B[i];
        }
        
        cout << solve() << endl;
    }
    
    return 0;
}
