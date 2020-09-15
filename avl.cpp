#include <iostream>
using namespace std;

struct node {
    int data;
    int height;
    struct node *right, *left;
};

struct node *new_node(int data) {
    struct node *temp = new node();
    temp->data = data;
    temp->height = 0;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
};

int find_max(int a, int b) {
    return (a >= b) ? a : b;
}

int height(struct node *root) {
    if (root == nullptr)
        return 0;
    else {
        return root->height;
    }
}

void inorder(struct node *root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data;
        inorder(root->right);
    }
}

struct node *left_rotation(struct node *y) {
    struct node *x = y->left;
    struct node *T1 = x->right;

    y->left = T1;
    x->right = y;

    y->height = 1 + find_max(height(y->left), height(y->right));
    x->height = 1 + find_max(height(x->left), height(x->right));

    return x;
}

struct node *right_rotation(struct node *x) {
    struct node *y = x->right;
    struct node *T1 = y->left;

    x->right = T1;
    y->left = x;

    y->height = 1 + find_max(height(y->left), height(y->right));
    x->height = 1 + find_max(height(x->left), height(x->right));

    return y;
}

int get_balance(struct node *root) {
    if (root == nullptr) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

struct node *insert(struct node *root, int data) {
    if (root == nullptr) {
        return (new_node(data));
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    } else {
        return root;
    }

    root->height = 1 + find_max(height(root->left), height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && data < root->left->data) {
        return right_rotation(root);
    } else if (balance < -1 && data > root->right->data) {
        return left_rotation(root);
    } else if (balance > 1 && data < root->left->data) {
        root->left = left_rotation(root->left);
        return right_rotation(root);
    } else if (balance < -1 && data < root->right->data) {
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }
    return root;
}

// struct node *delete_key(struct node *root, int data) {
// }

int main() {
    struct node *root = NULL;
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 9);
    root = insert(root, 4);
    root = insert(root, 3);
    inorder(root);
    cout << " ";
    cout << height(root);
    return 0;
}
