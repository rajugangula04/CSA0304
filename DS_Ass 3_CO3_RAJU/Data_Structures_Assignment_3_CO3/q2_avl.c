/*
 * Q2: AVL Tree insertion, four balancing cases through rotations,
 * preorder traversal and height. Height convention: empty = 0, leaf = 1.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;

int max(int a, int b) { return a > b ? a : b; }
int node_height(Node *n) { return n ? n->height : 0; }
Node *new_node(int key) {
    Node *n = malloc(sizeof *n);
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->key = key; n->left = n->right = NULL; n->height = 1;
    return n;
}
void fix(Node *n) { n->height = 1 + max(node_height(n->left), node_height(n->right)); }
int balance(Node *n) { return n ? node_height(n->left) - node_height(n->right) : 0; }

Node *rotate_right(Node *y) {
    Node *x = y->left, *t2 = x->right;
    x->right = y; y->left = t2;
    fix(y); fix(x);
    return x;
}
Node *rotate_left(Node *x) {
    Node *y = x->right, *t2 = y->left;
    y->left = x; x->right = t2;
    fix(x); fix(y);
    return y;
}
Node *insert(Node *root, int key) {
    if (!root) return new_node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    else return root;

    fix(root);
    int b = balance(root);
    if (b > 1 && key < root->left->key) return rotate_right(root);           /* LL */
    if (b < -1 && key > root->right->key) return rotate_left(root);          /* RR */
    if (b > 1 && key > root->left->key) {                                    /* LR */
        root->left = rotate_left(root->left); return rotate_right(root);
    }
    if (b < -1 && key < root->right->key) {                                  /* RL */
        root->right = rotate_right(root->right); return rotate_left(root);
    }
    return root;
}
void preorder(Node *r) { if (r) { printf("%d ", r->key); preorder(r->left); preorder(r->right); } }
void inorder(Node *r) { if (r) { inorder(r->left); printf("%d ", r->key); inorder(r->right); } }
void free_tree(Node *r) { if (r) { free_tree(r->left); free_tree(r->right); free(r); } }

int main(void) {
    int keys[] = {10, 20, 30, 40, 50, 25};
    Node *root = NULL;
    for (size_t i = 0; i < sizeof keys / sizeof keys[0]; i++) root = insert(root, keys[i]);
    printf("Inorder: "); inorder(root);
    printf("\nPreorder: "); preorder(root);
    printf("\nHeight (nodes): %d\n", node_height(root));
    printf("Root: %d\n", root ? root->key : -1);
    free_tree(root);
    return 0;
}
