#include <iostream>

using namespace std;

struct Node {
    bool empty = true;
    int val = 0;
    Node *lc = NULL, *rc = NULL;
    void insert(int val);
    int find_common_ancestor(int a, int b);
};

int main()
{
    int N, M;
    cin >> N >> M;
    Node root;
    while (N-- > 0) {
        int val;
        cin >> val;
        root.insert(val);
    }
    while (M-- > 0) {
        int a, b;
        cin >> a >> b;
        cout << root.find_common_ancestor(a, b) << endl;
    }
    return 0;
}

void Node::insert(int val) {
    if (empty) {
        this->val = val;
        empty = false;
        return;
    }
    if (val < this->val) {
        if (lc == NULL) {
            lc = new Node;
        }
        lc->insert(val);
        return;
    }
    if (rc == NULL) {
        rc = new Node;
    }
    rc->insert(val);
}

int Node::find_common_ancestor(int a, int b) {
    if (a > b) {
        int t = a;
        a = b;
        b = t;
    }
    if (b < val) {
        return lc->find_common_ancestor(a, b);
    }
    if (a <= val) {
        return val;
    }
    return rc->find_common_ancestor(a, b);
}
