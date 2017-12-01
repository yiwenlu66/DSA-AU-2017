#include <iostream>
#include <limits>

using namespace std;

const int MAXN = 100;
const int INF = std::numeric_limits<int>::max();

int adjacency[MAXN * MAXN];
int min_dist[MAXN * MAXN];

int N;

int find_min_loop();

int main()
{
    int M;
    cin >> M;
    while (M-- > 0) {
        cin >> N;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> adjacency[i * N + j];
                if (-1 == adjacency[i * N + j]) {
                    adjacency[i * N + j] = INF;
                }
            }
        }
        cout << find_min_loop() << endl;
    }
    return 0;
}

int sum_with_inf(int i1, int i2, int i3 = 0)
{
    if (i1 == INF || i2 == INF || i3 == INF) {
        return INF;
    }
    return i1 + i2 + i3;
}

int find_min_loop()
{
    for (int i = 0; i < N * N; ++i) {
        min_dist[i] = adjacency[i];
    }

    int min_loop = INF;

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j && j != k && k != i) {
                    min_loop = min(min_loop,
                                   sum_with_inf(min_dist[i * N + j], adjacency[j * N + k], adjacency[k * N + i]));
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                min_dist[i * N + j] = min(min_dist[i * N + j], sum_with_inf(min_dist[i * N + k], min_dist[k * N + j]));
            }
        }
    }

    if (INF == min_loop) {
        return -1;
    }
    return min_loop;
}
