#include <iostream>
#include <stack>
#include <deque>

using namespace std;

/*
 * Notations:
 * - s1: the input stack
 * - s2: the intermediate stack
 * - n: the number of elements in the input stack
 * - m: the number of elements in the intermediate stack
 */

typedef stack<int> Stack;
typedef deque<int> OutputSequence;

const int MAX_K = 10000;
const int MAX_CATALAN_INDEX = 9;
const int CATALAN[1 + MAX_CATALAN_INDEX] = {1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862};

const int ELLIPSIS = -1;    // indicate "..." in the output sequence

inline int get_catalan(int n) { // return catalan(n) if n<=MAX_CATALAN_INDEX, MAX_K otherwise
    return n <= MAX_CATALAN_INDEX ? CATALAN[n] : MAX_K;
}

OutputSequence get_kth_permutation(int s1_top, int s1_bottom, Stack &s2, int k);
int get_num_permutations(int n, int m); // return MAX_K if the actual number of permutations is larger than MAX_K

int main()
{
    int N;
    cin >> N;
    while (N-- > 0) {
        int M, K;
        cin >> M >> K;
        if (get_catalan(M) < K) {
            cout << "ERROR" << endl;
        } else {
            Stack s2;
            auto result = get_kth_permutation(1, M, s2, K);
            int prev;
            for (auto it = result.begin(); it != result.end(); ++it) {
                if (*it != ELLIPSIS) {
                    cout << *it << " ";
                } else {
                    ++it;
                    for (int j = prev + 1; j <= *it; ++j) {
                        cout << j << " ";
                    }
                }
                prev = *it;
            }
            cout << endl;
        }
    }
    return 0;
}


OutputSequence get_kth_permutation(int s1_top, int s1_bottom, Stack &s2, int k)
{
    // trivial case: k==1
    if (k == 1) {
        OutputSequence result;
        while (!s2.empty()) {
            int t = s2.top();
            s2.pop();
            result.push_back(t);
        }
        if (s1_top <= s1_bottom) {
            result.push_back(s1_top);
            result.push_back(ELLIPSIS);
            result.push_back(s1_bottom);
        }
        return result;
    }

    // push the top of the initial stack to the intermediate stack if the later is empty
    if (s2.empty()) {
        s2.push(s1_top++);
    }

    // number of permutations with the top of the intermediate stack used as the first element
    int offset = get_num_permutations(s1_bottom - s1_top + 1, static_cast<int>(s2.size()) - 1);
    if (offset >= k) {
        // the k-th permutation indeed starts with the top of the intermediate stack
        int head = s2.top();
        s2.pop();
        auto result = get_kth_permutation(s1_top, s1_bottom, s2, k);
        result.emplace_front(head);
        return result;
    }

    // there are less than k permutations starting with the top of the intermediate stack;
    // fall back to the second smallest head by pushing the top of the initial stack to the intermediate stack.
    s2.push(s1_top++);
    return get_kth_permutation(s1_top, s1_bottom, s2, k - offset);
}


int get_num_permutations(int n, int m)
{
    static bool initialized = false;
    static int lut[1 + MAX_CATALAN_INDEX][1 + MAX_CATALAN_INDEX];  // [n, m]
    if (!initialized) {
        for (int i = 0; i <= MAX_CATALAN_INDEX; ++i) {
            // when the intermediate stack is empty, the number of permutations is the catalan number
            lut[i][0] = CATALAN[i];
        }
        for (int j = 0; j <= MAX_CATALAN_INDEX; ++j) {
            // when the initial stack is empty, there is only one permutation
            lut[0][j] = 1;
        }
        // otherwise, there are two options for state transition:
        // (1) push the top of the initial stack to the intermediate stack,
        // (2) pop the top of the intermediate stack;
        // i.e. lut[i][j] = lut[i-1][j+1] + lut[i][j-1]
        for (int i = 1; i <= MAX_CATALAN_INDEX; ++i) {
            for (int j = 1; j <= MAX_CATALAN_INDEX; ++j) {
                lut[i][j] = lut[i - 1][j + 1] + lut[i][j - 1];
            }
        }
        initialized = true;
    }
    if (max(m, n) > MAX_CATALAN_INDEX) {
        return MAX_K;
    }
    return min(MAX_K, lut[n][m]);
}
