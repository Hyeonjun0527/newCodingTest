#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
TreeNode *create_node(int data) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *insert(TreeNode *root, int data) {
    if (root == NULL)
        return create_node(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}

int leaf_count(TreeNode *node) {
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    return leaf_count(node->left) + leaf_count(node->right);
}
void free_(TreeNode *node) {
    if (node) {
        free_(node->left);
        free_(node->right);
        free(node);
    }
}
int main(void) {
    int values[] = {50, 30, 75, 20, 55, 60, 80, 10, 25, 35, 45};
    int n = sizeof(values) / sizeof(values[0]);

    TreeNode *root = NULL;
    for (int i = 0; i < n; ++i)
        root = insert(root, values[i]);
    printf("리프 노드 수: %d\n", leaf_count(root));

    free_(root);
    return 0;
}
