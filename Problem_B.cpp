#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        vector<string> S(N), R(N);

        for (int i = 0; i < N; ++i) {
            cin >> S[i];
            R[i] = S[i];
            reverse(R[i].begin(), R[i].end());
        }

        // dp[i][0/1] lưu chuỗi nhị phân nếu đi tới i ở trạng thái đó
        vector<vector<string>> dp(N, vector<string>(2, ""));
        dp[0][0] = "0";
        dp[0][1] = "1";

        for (int i = 1; i < N; ++i) {
            for (int cur = 0; cur <= 1; ++cur) {
                string curr = (cur == 0 ? S[i] : R[i]);
                for (int prev = 0; prev <= 1; ++prev) {
                    if (dp[i - 1][prev] == "") continue;
                    string prevStr = (prev == 0 ? S[i - 1] : R[i - 1]);
                    if (prevStr < curr) {
                        string cand = dp[i - 1][prev] + (cur == 0 ? '0' : '1');
                        if (dp[i][cur] == "" || cand < dp[i][cur]) {
                            dp[i][cur] = cand;
                        }
                    }
                }
            }
        }

        string result = "";
        if (dp[N - 1][0] != "" && dp[N - 1][1] != "")
            result = min(dp[N - 1][0], dp[N - 1][1]);
        else if (dp[N - 1][0] != "")
            result = dp[N - 1][0];
        else
            result = dp[N - 1][1];

        cout << result << "\n";
    }

    return 0;
}
