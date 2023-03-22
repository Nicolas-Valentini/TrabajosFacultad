#include <iostream>
#include <algorithm>
#include <math.h>
#include <tuple>
#include <climits>
 
using namespace std;

tuple<double, double, int> sprinklers[10000];
 
int precalc[10000];
int costs[10000][10000];
 
bool sortbysec(const tuple<double, double, int>& a, const tuple<double, double, int>& b) {
    return get<1>(a) < get<1>(b);
}
 
int f(int i, int p) {
    if (p == -1) return -1;
    if (i == -1) return INT_MAX;
    if (costs[i][p] != -1) return costs[i][p];
 
    double start = get<0>(sprinklers[i]);
    double end   = get<1>(sprinklers[i]);
 
    double coverage = get<1>(sprinklers[p]);
    int cost = get<2>(sprinklers[i]);
 
    if (start <= 0 && end >= coverage) {
        costs[i][p] = min(f(i - 1, p), cost);
    } else if (start > coverage || end < coverage) {
        costs[i][p] = f(i - 1, p);
    } else {
        int cost_to_start = f(i - 1, precalc[i]);
        if (cost_to_start != INT_MAX) {
            cost_to_start += cost;
        }
        costs[i][p] = min(f(i - 1, p), cost_to_start);
    }
 
    return costs[i][p];
}
 
int main() {
    int n, l, w;

    while (cin >> n >> l >> w) {
        for (int i = 0; i < n; i++) {
            int p, r, c;
            cin >> p >> r >> c;
            sprinklers[i] = make_tuple(p, r, c);
        }
 
        for (int i = 0; i < n; i++) {
            int p = get<0>(sprinklers[i]);
            int r = get<1>(sprinklers[i]);
            int c = get<2>(sprinklers[i]);
 
            double diff = pow(r, 2) - pow((double) w / 2, 2);
            double half_width = diff > 0 ? sqrt(diff) : 0;
 
            sprinklers[i] = make_tuple(p - half_width, p + half_width, c);
        }
 
        sort(sprinklers, sprinklers + n, sortbysec);
 
        for (int i = 0; i < n; i++) {
            double start = get<0>(sprinklers[i]);
 
            for (int j = 0; j < n; j++) {
                double end = get<1>(sprinklers[j]);
 
                if (end >= start) {
                    precalc[i] = j;
                    break;
                }
            }
        }
 
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                costs[i][j] = -1;
            }
        }
 
        int min_coverage = -1;
 
        for (int i = 0; i < n; i++) {
            if (get<1>(sprinklers[i]) >= l) {
                min_coverage = i;
                break;
            }
        }
 
        int res = f(n - 1, min_coverage);
        cout << (res == INT_MAX ? -1 : res) << endl;
    }
 
    return 0;
}
