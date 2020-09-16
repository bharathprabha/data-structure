#include <iostream>
#include <queue>

using namespace std;

struct node {
    int data;
    struct node *right, *left;
};

node *new_node(int data) {
    node *temp = new node();
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
};

int min_value(node *root) {
    node *temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp->data;
}

bool find_key(node *root, int data) {
    if (root == NULL)
        return false;
    else if (root->data > data)
        return find_key(root->left, data);
    else if (root->data < data)
        return find_key(root->right, data);
    else
        return true;
}

int find_max(int a, int b) {
    return (a >= b) ? a : b;
}

int height(node *root) {
    if (root == NULL)
        return 0;
    else {
        return 1 + find_max(height(root->left), height(root->right));
    }
}

void levl_order(node *root) {
    if (root == NULL) return;

    queue<node *> expo;

    node *temp;

    expo.push(root);
    expo.push(NULL);
    while (expo.size() > 1) {
        temp = expo.front();

        expo.pop();

        if (temp == NULL) {
            expo.push(NULL);
            cout << "\n";
        } else {
            if (temp->left) {
                expo.push(temp->left);
            }
            if (temp->right) {
                expo.push(temp->right);
            }

            cout << temp->data << " ";
        }
    }
}

void inorder(node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data;
        inorder(root->right);
    }
}

node *insert(node *root, int data) {
    if (root == NULL)
        return new_node(data);
    if (root->data >= data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

int main() {
    node *root = NULL;
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 9);
    root = insert(root, 4);
    root = insert(root, 3);
    levl_order(root);
    return 0;
}