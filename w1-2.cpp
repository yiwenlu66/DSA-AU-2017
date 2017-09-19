#include <iostream>

using namespace std;

int all_solutions[8][9] = {
    {8, 1, 6, 3, 5, 7, 4, 9, 2},
    {6, 1, 8, 7, 5, 3, 2, 9, 4},
    {4, 9, 2, 3, 5, 7, 8, 1, 6},
    {2, 9, 4, 7, 5, 3, 6, 1, 8},
    {6, 7, 2, 1, 5, 9, 8, 3, 4},
    {8, 3, 4, 1, 5, 9, 6, 7, 2},
    {2, 7, 6, 9, 5, 1, 4, 3, 8},
    {4, 3, 8, 9, 5, 1, 2, 7, 6},
};

int num_solutions(char input[9]);
bool match(char input[9], int solution[9]);

int main()
{
    int N;
    char input[9];
    cin >> N;
    while (N-- > 0) {
        for (int i = 0; i < 9; ++i) {
            cin >> input[i];
        }
        cout << num_solutions(input) << endl;
    }
    return 0;
}


int num_solutions(char input[9])
{
    int n = 0;
    for (int i = 0; i < 8; ++i) {
        if (match(input, all_solutions[i])) {
            ++n;
        }
    }
    return n;
}

bool match(char input[9], int solution[9])
{
    for (int i = 0; i < 9; ++i) {
        if (input[i] != '*' && input[i] != solution[i] + '0') {
            return false;
        }
    }
    return true;
}
