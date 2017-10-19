#include <iostream>
#include <list>

using namespace std;

int main()
{
    int M, N;
    cin >> N >> M;
    list<int> people;
    for (int i = 1; i <= N; ++i) {
        people.emplace_back(i);
    }
    int number = 1;
    auto person = people.begin();
    int deleted_count = 0;
    while (deleted_count < N - 1) {
        if (number == M) {
            // remove current person
            ++deleted_count;
            auto next_person = next(person) == people.end() ? people.begin() : next(person);
            people.erase(person);
            person = next_person;
            number = 1;
        } else {
            person = next(person) == people.end() ? people.begin() : next(person);
            ++number;
        }
    }
    cout << *(people.begin()) << endl;
    return 0;
}
