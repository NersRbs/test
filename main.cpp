#include <iostream>

struct Node {
    int data;
    int height;
    Node *left;
    Node *right;

    explicit Node(int data) {
        this->data = data;
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

Node *insert(Node *node, int data) {
    if (!node)
        return new Node(data);
    if(data == node->data)
        return node;
    else if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);
    return balance(node);
}

Node *find_max(Node *node) {
    return node->right? find_max(node->right): node;
}

Node *removeMax(Node *node) {
    if (node->right == nullptr)
        return node->left;
    node->right = removeMax(node->right);
    return balance(node);
}


Node *remove(Node *node, int data) {
    if (!node)
        return nullptr;
    if (data < node->data)
        node->left = remove(node->left, data);
    else if (data > node->data)
        node->right = remove(node->right, data);
    else {
        Node *left = node->left;
        Node *right = node->right;
        delete node;
        if (!left)
            return right;
        Node *max = find_max(left);
        max->left = removeMax(left);
        max->right = right;
        return balance(max);
    }
    return balance(node);
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

int main() {
    int n;
    std::cin >> n;

    Node *node = nullptr;
    char command;
    int x;

    for (int i = 0; i < n; ++i) {
        std::cin >> command;
        std::cin >> x;
        if (command == 'A') {
            node = insert(node, x);
            if(node)
                std::cout << height(node->right) - height(node->left) << '\n';
            else
                std::cout << "0\n";
        } else if (command == 'D') {
            node = remove(node, x);
            if(node)
                std::cout << height(node->right) - height(node->left) << '\n';
            else
                std::cout << "0\n";
        } else if(command == 'C') {
            if (exist(node, x))
                std::cout << "Y\n";
            else
                std::cout << "N\n";
        }
    }
}