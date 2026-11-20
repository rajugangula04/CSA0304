/*
 * Q5: Splay Tree insertion and access (zig, zig-zig, zig-zag).
 * The initial tree is built from the sample keys, then 3 and 9 are accessed.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;
Node *new_node(int key) {
    Node *n = malloc(sizeof *n);
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->key = key; n->left = n->right = NULL; return n;
}
Node *right_rotate(Node *y) {
    Node *x = y->left; y->left = x->right; x->right = y; return x;
}
Node *left_rotate(Node *x) {
    Node *y = x->right; x->right = y->left; y->left = x; return y;
}
Node *splay(Node *root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) {
        if (!root->left) return root;
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = right_rotate(root);
        } else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right) root->left = left_rotate(root->left);
        }
        return root->left ? right_rotate(root) : root;
    } else {
        if (!root->right) return root;
        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = left_rotate(root);
        } else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left) root->right = right_rotate(root->right);
        }
        return root->right ? left_rotate(root) : root;
    }
}
Node *insert(Node *root, int key) {
    if (!root) return new_node(key);
    root = splay(root, key);
    if (root->key == key) return root;
    Node *n = new_node(key);
    if (key < root->key) {
        n->right = root; n->left = root->left; root->left = NULL;
    } else {
        n->left = root; n->right = root->right; root->right = NULL;
    }
    return n;
}
void inorder(Node *r) { if (r) { inorder(r->left); printf("%d ", r->key); inorder(r->right); } }
void print_tree(Node *r, int depth) {
    if (!r) return;
    print_tree(r->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%d\n", r->key);
    print_tree(r->left, depth + 1);
}
void free_tree(Node *r) { if (r) { free_tree(r->left); free_tree(r->right); free(r); } }
int main(void) {
    Node *root = NULL;
    int keys[] = {10, 5, 15, 3, 9, 12, 18, 7};
    for (size_t i = 0; i < sizeof keys / sizeof keys[0]; i++) root = insert(root, keys[i]);
    puts("Initial tree (sideways):"); print_tree(root, 0);
    root = splay(root, 3);
    printf("\nAfter access 3, root = %d\n", root ? root->key : -1);
    root = splay(root, 9);
    printf("After access 9, root = %d\n", root ? root->key : -1);
    printf("Inorder: "); inorder(root); puts("");
    free_tree(root);
    return 0;
}
