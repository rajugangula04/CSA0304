/*
 * Q4: Red-Black Tree insertion (CLRS-style sentinel NIL).
 * Demonstrates the insertion sequence 10,20,30,15,25,5.
 */
#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;
typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

static Node *NIL;
static Node *root;

Node *new_node(int key) {
    Node *n = malloc(sizeof *n);
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->key = key; n->color = RED;
    n->left = n->right = n->parent = NIL;
    return n;
}
void left_rotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x; x->parent = y;
}
void right_rotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NIL) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NIL) root = x;
    else if (y == y->parent->right) y->parent->right = x;
    else y->parent->left = x;
    x->right = y; y->parent = x;
}
void insert_fixup(Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK; y->color = BLACK;
                z->parent->parent->color = RED; z = z->parent->parent;
            } else {
                if (z == z->parent->right) { z = z->parent; left_rotate(z); }
                z->parent->color = BLACK; z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK; y->color = BLACK;
                z->parent->parent->color = RED; z = z->parent->parent;
            } else {
                if (z == z->parent->left) { z = z->parent; right_rotate(z); }
                z->parent->color = BLACK; z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}
void insert(int key) {
    Node *z = new_node(key), *y = NIL, *x = root;
    while (x != NIL) {
        y = x;
        if (key < x->key) x = x->left;
        else if (key > x->key) x = x->right;
        else { free(z); return; }
    }
    z->parent = y;
    if (y == NIL) root = z;
    else if (key < y->key) y->left = z;
    else y->right = z;
    insert_fixup(z);
}
void inorder(Node *x) {
    if (x == NIL) return;
    inorder(x->left);
    printf("%d(%c) ", x->key, x->color == RED ? 'R' : 'B');
    inorder(x->right);
}
void print_tree(Node *x, int depth) {
    if (x == NIL) return;
    print_tree(x->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d(%c)\n", x->key, x->color == RED ? 'R' : 'B');
    print_tree(x->left, depth + 1);
}
void free_tree(Node *x) {
    if (x == NIL) return;
    free_tree(x->left); free_tree(x->right); free(x);
}
int main(void) {
    NIL = malloc(sizeof *NIL);
    if (!NIL) { perror("malloc"); return EXIT_FAILURE; }
    NIL->color = BLACK; NIL->left = NIL->right = NIL->parent = NIL;
    root = NIL;
    int keys[] = {10, 20, 30, 15, 25, 5};
    for (size_t i = 0; i < sizeof keys / sizeof keys[0]; i++) insert(keys[i]);
    puts("Red-Black Tree (sideways):");
    print_tree(root, 0);
    printf("Inorder: "); inorder(root); puts("");
    free_tree(root); free(NIL);
    return 0;
}
