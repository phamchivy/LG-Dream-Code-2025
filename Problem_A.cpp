#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int N, X, Y;
        cin >> N >> X >> Y;
        
        vector<int> V(N);
        for (int i = 0; i < N; i++) {
            cin >> V[i];
        }
        
        int my_speed = V[N-1];
        
        double min_other_time = 1e9;
        for (int i = 0; i < N-1; i++) {
            double time = (double)X / V[i];
            min_other_time = min(min_other_time, time);
        }
        
        double my_time_no_booster = (double)X / my_speed;
        
        if (my_time_no_booster < min_other_time) {
            cout << 0 << endl;
            continue;
        }
        
        double my_time_max_booster = 1.0 + (double)(X - Y) / my_speed;
        if (my_time_max_booster >= min_other_time) {
            cout << -1 << endl;
            continue;
        }
        
        int left = 1, right = Y;
        int result = Y;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            double my_time = 1.0 + (double)(X - mid) / my_speed;
            
            if (my_time < min_other_time) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        cout << result << endl;
    }
    
    return 0;
}
