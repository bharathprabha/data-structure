#include <iostream>
using namespace std;

struct node {
    int data;
    struct node *right, *left;
};

struct node *new_node(int data) {
    struct node *temp = new node();
    temp->data = data;
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
        return 1 + find_max(height(root->left), height(root->right));
    }
}

void inorder(struct node *root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data;
        inorder(root->right);
    }
}

struct node *insert(struct node *root, int data) {
}

struct node *delete_key(struct node *root, int data) {
}

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
    return 0;
}
