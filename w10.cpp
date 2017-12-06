#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <queue>

using namespace std;

typedef priority_queue<pair<int, int>> PQ;  // (value, no)

int main()
{
    set<int> points;
    int n, d;
    cin >> n >> d;
    std::vector<PQ> max_heaps(1 << d), min_heaps(1 << d);
    int no = 1;
    int elem_cnt = 0;
    while (n-- > 0) {
        int op;
        cin >> op;
        if (!op) {
            // add
            ++elem_cnt;
            vector<int> coord(d);
            for (int i = 0; i < d; ++i) {
                cin >> coord[i];
            }
            for (int j = 0; j < (1 << d); ++j) {
                int j1 = j;
                int val = 0;
                for (int i = 0; i < d; ++i) {
                    int sign = (j1 % 2) ? 1 : -1;
                    val += sign * coord[i];
                    j1 >>= 1;
                }
                max_heaps[j].emplace(val, no);
                min_heaps[j].emplace(-val, no);
            }
            points.insert(no);
        } else {
            // delete
            --elem_cnt;
            int no_del;
            cin >> no_del;
            points.erase(no_del);
        }
        // query
        if (1 == elem_cnt) {
            cout << 0 << endl;
        } else {
            int max_diff = numeric_limits<int>::min();
            for (int j = 0; j < (1 << d); ++j) {
                while (points.find(max_heaps[j].top().second) == points.end()) {
                    max_heaps[j].pop();
                }
                while (points.find(min_heaps[j].top().second) == points.end()) {
                    min_heaps[j].pop();
                }
            }
            for (int j = 0; j < (1 << d); ++j) {
                max_diff = max(max_diff, max_heaps[j].top().first + min_heaps[j].top().first);
            }
            cout << max_diff << endl;
        }
        ++no;
    }
    return 0;
}
