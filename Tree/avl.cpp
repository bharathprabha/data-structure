#include <iostream>
using namespace std;

struct node {
    int data;
    int height;
    struct node *right, *left;
};

node *new_node(int data) {
    node *temp = new node();
    temp->data = data;
    temp->height = 1;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
};

int find_max(int a, int b) {
    return (a >= b) ? a : b;
}

int height(node *root) {
    if (root == nullptr)
        return 0;
    else {
        return root->height;
    }
}

void inorder(node *root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data;
        inorder(root->right);
    }
}

node *left_rotation(node *y) {
    node *x = y->left;
    node *T1 = x->right;

    y->left = T1;
    x->right = y;

    y->height = 1 + find_max(height(y->left), height(y->right));
    x->height = 1 + find_max(height(x->left), height(x->right));

    return x;
}

node *right_rotation(node *x) {
    node *y = x->right;
    node *T1 = y->left;

    x->right = T1;
    y->left = x;

    y->height = 1 + find_max(height(y->left), height(y->right));
    x->height = 1 + find_max(height(x->left), height(x->right));

    return y;
}

int get_balance(node *root) {
    if (root == nullptr) {
        return 0;
    }
    return height(root->left) - height(root->right); 
}

node *insert(node *root, int data) {
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

int min_value(node *root) {
    node *temp = root;
    while (temp->left != nullptr) {
        temp = temp->left;
    }

    return temp->data;
}

node *delete_key(node *root, int data) {
    if (root == nullptr) {
        return root;
    }
    if (data < root->data) {
        root->left = delete_key(root->left, data);
    } else if (data > root->data) {
        root->right = delete_key(root->right, data);
    } else {
        if (root->left == nullptr) {
            node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == nullptr) {
            node *temp = root->left;
            free(root);
            return temp;
        } else {
            node *temp = new_node(min_value(root->right));

            root->data = temp->data;

            root->right = delete_key(root->right, temp->data);
        }
    }
    if (root == nullptr) {
        return root;
    }

    root->height = 1 + find_max(height(root->left), height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0) {
        return right_rotation(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0) {
        return left_rotation(root);
    }
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotation(root->left);
        return right_rotation(root);
    }
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotation(root->right);
        return left_rotation(root);
    }
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
    inorder(root);
    cout << " ";
    cout << height(root);
    root = delete_key(root, 7);
    root = delete_key(root, 3);
    root = delete_key(root, 9);
    cout << " ";
    inorder(root);
    cout << " ";
    cout << height(root);
    return 0;
}
