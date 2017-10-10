#include <iostream>
#include <list>

using namespace std;

struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
};

class Snake {
public:
    Snake();
    void grow();
    bool move(char dir, int n_steps);   // return true on safe move, false on death
private:
    list<Point> positions;
    Point head;
    char dir;
protected:
    void _move_head(char dir);
    bool _check_collision();
};

Snake::Snake() : head(0, 0), dir('r')
{
    positions.emplace_back(head);
}

void Snake::_move_head(char dir)
{
    switch (dir) {
        case 'u':
            ++head.y;
            break;
        case 'r':
            ++head.x;
            break;
        case 'd':
            --head.y;
            break;
        case 'l':
            --head.x;
            break;
        default:
            break;
    }
}

bool Snake::_check_collision()
{
    for (auto it = positions.begin(); it != prev(positions.end()); ++it) {
        auto p = *it;
        if (p.x == head.x && p.y == head.y) {
            return true;
        }
    }
    return false;
}

void Snake::grow()
{
    _move_head(dir);
    positions.emplace_back(head);
}

bool Snake::move(char dir, int n_steps)
{
    this->dir = dir;
    while (n_steps-- > 0) {
        _move_head(dir);
        positions.emplace_back(head);
        positions.pop_front();
        if (_check_collision()) {
            return false;
        }
    }
    return true;
}

int main()
{
    int N;
    cin >> N;
    Snake snake;
    while (N-- > 0) {
        int i, n_steps;
        char op;
        cin >> i >> op;
        if (op == 'g') {
            snake.grow();
        } else {
            cin >> n_steps;
            if (!snake.move(op, n_steps)) {
                cout << i << endl;
                return 0;
            }
        }
    }
    cout << "safe" << endl;
    return 0;
}
