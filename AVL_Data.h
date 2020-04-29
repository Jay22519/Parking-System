/*** This file contains the code for the AVL Tree which is used to store the mapping details of the Vehicle and the
Parking position ***/

#include "max.h"



typedef struct node
{
    int vehicle_number;

    //For AVL Tree
    int height;
    struct node *left;
    struct node *right;

} Node;

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = maxa(height(y->left), height(y->right)) + 1;
    x->height = maxa(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}


Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = maxa(height(x->left), height(x->right)) + 1;
    y->height = maxa(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}


int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insertNode(Node *root, Node *node)
{
    if (root == NULL)
        return node;

    if (node->vehicle_number < root->vehicle_number)
    {
        root->left = insertNode(root->left, node);
    }

    else if (node->vehicle_number > root->vehicle_number)
    {
        root->right = insertNode(root->right, node);
    }

    root->height = 1 + maxa(height(root->left),
                           height(root->right));

    int balance = getBalance(root);


    // Left Left Case
    if (balance > 1 && node->vehicle_number < root->left->vehicle_number)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && node->vehicle_number > root->left->vehicle_number)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && node->vehicle_number > root->left->vehicle_number)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && node->vehicle_number < root->left->vehicle_number)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *searchNode(Node *root, int vehicle_number)
{
    if (root == NULL)
    {
        return root;
    }

    if (vehicle_number < root->vehicle_number)
    {
        return searchNode(root->left, vehicle_number);
    }

    else if (vehicle_number == root->vehicle_number)
    {
        return root;
    }

    else
    {
        return searchNode(root->right, vehicle_number);
    }
}

Node *minValueNode(Node *node)
{
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteNode(Node *root, int key)
{

    if (root == NULL)
        return root;

    if (key < root->vehicle_number)
        root->left = deleteNode(root->left, key);

    else if (key > root->vehicle_number)
        root->right = deleteNode(root->right, key);


    else
    {

        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {

            Node *temp = minValueNode(root->right);

            root->vehicle_number = temp->vehicle_number;

            root->right = deleteNode(root->right, temp->vehicle_number);
        }
    }


    if (root == NULL)
        return root;

    root->height = 1 + maxa(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
