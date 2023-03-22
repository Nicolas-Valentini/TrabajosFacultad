#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n, l, w;
    pair<double, double> sprinklers[10000];

    while (cin >> n >> l >> w) {
        for (int i = 0; i < n; i++) {
            int p, r;
            cin >> p >> r;
            sprinklers[i] = make_pair(p, r);
        }
    
        for (int i = 0; i < n; i++) {
            int p = sprinklers[i].first;
            int r = sprinklers[i].second;
        
            double diff = pow(r, 2) - pow((double) w / 2, 2);
            double half_width = diff > 0 ? sqrt(diff) : 0;

            sprinklers[i] = make_pair(p - half_width, p + half_width);
        }
    
        sort(sprinklers, sprinklers + n);
        
        int needed = 0;
    
        double start = 0;
        bool possible = true;

        while (possible && start < l) {
            double best_end = 0;

            int i = 0;
    
            while (i < n && sprinklers[i].first <= start) {
                best_end = max(sprinklers[i].second, best_end);
                i++;
            }
    
            if (start == best_end) {
                possible = false;
            } else {
                start = best_end;
                needed++;
            }
        }
    
        cout << (possible ? needed : -1) << endl;
    }

    return 0;
}
