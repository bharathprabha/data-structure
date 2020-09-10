#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node *right, *left;
};

struct node *new_node(int data)
{
    struct node *temp = new node();
    temp->data = data;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
};

int min_value(struct node *root)
{
    struct node *temp = root;
    while (temp->left != nullptr)
    {
        temp = temp->left;
    }
    return temp->data;
}

bool find_key(struct node *root, int data)
{
    if (root == nullptr)
        return false;
    else if (root->data > data)
        return find_key(root->left, data);
    else if (root->data < data)
        return find_key(root->right, data);
    else
        return true;
}

int max_value(struct node *root)
{
    struct node *temp = root;
    while (temp->right != nullptr)
    {
        temp = temp->right;
    }
    return temp->data;
}

int find_max(int a, int b)
{
    return (a >= b) ? a : b;
}

int height(struct node *root)
{
    if (root == nullptr)
        return 0;
    else
    {
        return 1 + find_max(height(root->left), height(root->right));
    }
}

void inorder(struct node *root)
{
    if (root != nullptr)
    {
        inorder(root->left);
        cout << root->data;
        inorder(root->right);
    }
}

void preorder(struct node *root)
{
    if (root != nullptr)
    {
        cout << root->data;
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct node *root)
{
    if (root != nullptr)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data;
    }
}

struct node *insert(struct node *root, int data)
{
    if (root == nullptr)
        return new_node(data);
    if (root->data >= data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

struct node *delete_key(struct node *root, int data)
{
    if (root == NULL)
        return root;
    else if (root->data > data)
        root->left = delete_key(root->left, data);
    else if (root->data < data)
        root->right = delete_key(root->right, data);
    else
    {
        if (root->left == nullptr)
        {
            struct node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == nullptr)
        {
            struct node *temp = root->left;
            free(root);
            return temp;
        }
        else
        {
            struct node *temp = new_node(min_value(root->right));

            root->data = temp->data;

            root->right = delete_key(root->right, temp->data);
        }
    }
    return root;
}

int main()
{
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
    preorder(root);
    cout << " ";
    postorder(root);
    cout << " ";
    cout << min_value(root);
    cout << " ";
    cout << max_value(root);
    cout << " ";
    cout << find_key(root, 200);
    cout << " ";
    cout << find_key(root, 9);
    cout << " ";
    root = delete_key(root, 9);
    inorder(root);
    cout << " ";
    cout << height(root);
    return 0;
}