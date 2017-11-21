#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator<(const Point &other) const { return x < other.x || (x == other.x && y < other.y); }
    bool operator>(const Point &other) const { return x > other.x || (x == other.x && y > other.y); }
};

struct Node {
    Point point;
    int cost;
    Node(Point point, int cost) : point(point), cost(cost) {}
};

int main()
{
    int x_final, y_final;
    int n_forbidden;
    set<Point> forbidden;
    cin >> x_final >> y_final;
    cin >> n_forbidden;
    while (n_forbidden-- > 0) {
        int x, y;
        cin >> x >> y;
        forbidden.insert(Point(x, y));
    }

    queue<Node> frontier;
    set<Point> frontier_set;
    set<Point> explored;
    frontier.push(Node(Point(0, 0), 0));
    frontier_set.insert(Point(0, 0));
    while (!frontier.empty()) {
        Node current = frontier.front();
        frontier.pop();
        frontier_set.erase(current.point);
        explored.insert(current.point);
        vector<Point> neighbors;
        neighbors.emplace_back(Point(current.point.x + 1, current.point.y + 2));
        neighbors.emplace_back(Point(current.point.x + 1, current.point.y - 2));
        neighbors.emplace_back(Point(current.point.x - 1, current.point.y + 2));
        neighbors.emplace_back(Point(current.point.x - 1, current.point.y - 2));
        neighbors.emplace_back(Point(current.point.x + 2, current.point.y + 1));
        neighbors.emplace_back(Point(current.point.x + 2, current.point.y - 1));
        neighbors.emplace_back(Point(current.point.x - 2, current.point.y + 1));
        neighbors.emplace_back(Point(current.point.x - 2, current.point.y - 1));
        for (auto neighbor : neighbors) {
            if (neighbor.x == x_final && neighbor.y == y_final) {
                cout << current.cost + 1 << endl;
                return 0;
            }
            if (max(abs(neighbor.x), abs(neighbor.y)) > 100) {
                continue;
            }
            if (forbidden.find(neighbor) != forbidden.end() || explored.find(neighbor) != explored.end() || frontier_set.find(neighbor) != frontier_set.end()) {
                continue;
            }
            frontier.push(Node(neighbor, current.cost + 1));
            frontier_set.insert(neighbor);
        }
    }

    cout << "fail" << endl;

    return 0;
}
