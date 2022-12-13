#include <iostream>


struct Node {
    int data;
    int index;
    int height;
    Node *left;
    Node *right;

    explicit Node(int data = 0) {
        this->data = data;
        index = 0;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};


int height(Node *node) {
    if (node)
        return node->height;
    return 0;
}

void fixNodeHeight(Node *node) {
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}


Node *LeftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    fixNodeHeight(x);
    fixNodeHeight(y);
    return y;
}

Node *RightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    fixNodeHeight(x);
    fixNodeHeight(y);
    return y;
}

Node *BigLeftRotate(Node *node) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
}

Node *BigRightRotate(Node *node) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
}

int getBalanceFactor(Node *node) {
    return height(node->right) - height(node->left);
}

Node *balance(Node *node) {
    fixNodeHeight(node);
    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->right) < 0)
            node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->left) > 0)
            node->left = LeftRotate(node->left);
        return RightRotate(node);
    }
    return node;
}

bool exist(Node *node, int x) {
    if (node == nullptr)
        return false;
    else if (x < node->data)
        return exist(node->left, x);
    else if (x > node->data)
        return exist(node->right, x);
    else
        return true;

}

Node *insert(Node *node, int data) {
    if (!node)
        return new Node(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);
    return balance(node);
}

void set_index(Node *node, int &index) {
    if (!node)
        return;
    node->index = index;
    index++;
    set_index(node->left, index);
    set_index(node->right, index);
}

void print(Node *node) {
    if (!node)
        return;
    printf("%d ", node->data);
    if (node->left)
        printf("%d ", node->left->index);
    else
        printf("0 ");
    if (node->right)
        printf("%d\n", node->right->index);
    else
        printf("0\n");
    print(node->left);
    print(node->right);
}

int main() {
    int n;
    std::cin >> n;
    Node *node;
    int left, right, data;
    for (int i = 0; i < n; ++i) {
        std::cin >> data;
        std::cin >> left;
        std::cin >> right;
        if (!exist(node, data))
            node = insert(node, data);
    }
    std::cin >> data;
    if (!exist(node, data)) {
        node = insert(node, data);
        n++;
    }

    printf("%d\n", n);
    int index = 1;
    set_index(node, index);
    print(node);
}