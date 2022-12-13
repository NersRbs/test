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
    if (node == nullptr)
        return 0;
    else
        return node->height;
}

Node *LeftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(x->right), x->height) + 1;
    return y;
}

Node *RightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(x->left), x->height) + 1;
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

Node *insert(Node *node, int x) {
    if (node == nullptr)
        node = new Node(x);
    else if (x < node->data) {
        node->left = insert(node->left, x);
        if (height(node->left) - height(node->right) == 2) {
            if (x < node->left->data)
                node = RightRotate(node);
            else
                node = BigRightRotate(node);
        }
    } else if (x > node->data) {
        node->right = insert(node->right, x);
        if (abs(height(node->left) - height(node->right)) == 2) {
            if (x > node->right->data)
                node = LeftRotate(node);
            else
                node = BigLeftRotate(node);
        }
    }
    node->height = std::max(height(node->left), height((node->right))) + 1;
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
    Node array[n];
    int left, right;
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i].data;
        std::cin >> left;
        std::cin >> right;
        if (left)
            array[i].left = &array[left - 1];
        if (right)
            array[i].right = &array[right - 1];
    }
    Node *node;
    node = array;
    int value;
    std::cin >> value;
    if (n == 0)
        printf("1\n%d 0 0", value);
    else {
        if (!exist(node, value)) {
            node = insert(node, value);
            n++;
        }
        printf("%d\n", n);
        int index = 1;
        set_index(node, index);
        print(node);
    }
}