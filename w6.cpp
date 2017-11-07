#include <iostream>

using namespace std;

struct Node {
    Node *lc, *rc;
    int height;
    int get_max_distance();
};

Node *recon(int *pre_order, int *in_order, int size);

int main()
{
    int N;
    cin >> N;
    auto pre_order = new int[N], in_order = new int[N];
    for (int i = 0; i < N; ++i) {
        cin >> pre_order[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> in_order[i];
    }
    auto tree = recon(pre_order, in_order, N);
    delete [] pre_order, in_order;
    cout << tree->get_max_distance() << endl;
    return 0;
}

Node *recon(int *pre_order, int *in_order, int size)
{
    if (size == 0) {
        return NULL;
    }
    if (size == 1) {
        auto root = new Node;
        root->lc = root->rc = NULL;
        root->height = 0;
        return root;
    }
    int root_number = pre_order[0];
    int left_size;
    for (int i = 0; i < size; ++i) {
        if (in_order[i] == root_number) {
            left_size = i;
            break;
        }
    }
    auto root = new Node;
    root->lc = recon(pre_order + 1, in_order, left_size);
    root->rc = recon(pre_order + 1 + left_size, in_order + 1 + left_size, size - 1 - left_size);
    if (root->lc == NULL) {
        root->height = root->rc->height + 1;
    } else if (root->rc == NULL) {
        root->height = root->lc->height + 1;
    } else {
        root->height = max(root->lc->height, root->rc->height) + 1;
    }
    return root;
}

int Node::get_max_distance() {
    if (height == 0) {
        return 0;
    }
    int max_left = (lc == NULL) ? 0 : lc->get_max_distance(), max_right = (rc == NULL) ? 0 : rc->get_max_distance();
    int max_cross = (lc == NULL || rc == NULL) ? 0 : lc->height + rc->height + 2;
    return max(max(max_left, max_right), max_cross);
}