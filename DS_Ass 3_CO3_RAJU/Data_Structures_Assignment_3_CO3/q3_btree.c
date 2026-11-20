/*
 * Q3: B-tree with minimum degree t=2 (max 3 keys per node).
 * Demonstrates insertion and inorder traversal for the assignment sequence.
 */
#include <stdio.h>
#include <stdlib.h>
#define T 2
#define MAX_KEYS (2*T-1)
#define MAX_CHILDREN (2*T)

typedef struct BNode {
    int n, leaf;
    int keys[MAX_KEYS];
    struct BNode *child[MAX_CHILDREN];
} BNode;

BNode *new_node(int leaf) {
    BNode *x = calloc(1, sizeof *x);
    if (!x) { perror("calloc"); exit(EXIT_FAILURE); }
    x->leaf = leaf;
    return x;
}
void traverse(BNode *x) {
    if (!x) return;
    int i;
    for (i = 0; i < x->n; i++) {
        if (!x->leaf) traverse(x->child[i]);
        printf("%d ", x->keys[i]);
    }
    if (!x->leaf) traverse(x->child[i]);
}
void split_child(BNode *parent, int i, BNode *full) {
    BNode *right = new_node(full->leaf);
    right->n = T - 1;
    for (int j = 0; j < T - 1; j++) right->keys[j] = full->keys[j + T];
    if (!full->leaf)
        for (int j = 0; j < T; j++) right->child[j] = full->child[j + T];
    full->n = T - 1;
    for (int j = parent->n; j >= i + 1; j--) parent->child[j + 1] = parent->child[j];
    parent->child[i + 1] = right;
    for (int j = parent->n - 1; j >= i; j--) parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = full->keys[T - 1];
    parent->n++;
}
void insert_nonfull(BNode *x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) { x->keys[i + 1] = x->keys[i]; i--; }
        if (i >= 0 && x->keys[i] == k) return;
        x->keys[i + 1] = k; x->n++;
    } else {
        while (i >= 0 && k < x->keys[i]) i--;
        i++;
        if (i <= x->n - 1 && x->keys[i] == k) return;
        if (x->child[i]->n == MAX_KEYS) {
            split_child(x, i, x->child[i]);
            if (k > x->keys[i]) i++;
            else if (k == x->keys[i]) return;
        }
        insert_nonfull(x->child[i], k);
    }
}
BNode *insert(BNode *root, int k) {
    if (!root) { root = new_node(1); root->keys[0] = k; root->n = 1; return root; }
    if (root->n == MAX_KEYS) {
        BNode *s = new_node(0);
        s->child[0] = root;
        split_child(s, 0, root);
        int i = (k > s->keys[0]) ? 1 : 0;
        if (k == s->keys[0]) return s;
        insert_nonfull(s->child[i], k);
        return s;
    }
    insert_nonfull(root, k);
    return root;
}
void print_tree(BNode *x, int depth) {
    if (!x) return;
    printf("Level %d: [", depth);
    for (int i = 0; i < x->n; i++) printf("%s%d", i ? " | " : "", x->keys[i]);
    puts("]");
    if (!x->leaf) for (int i = 0; i <= x->n; i++) print_tree(x->child[i], depth + 1);
}
void free_tree(BNode *x) {
    if (!x) return;
    if (!x->leaf) for (int i = 0; i <= x->n; i++) free_tree(x->child[i]);
    free(x);
}
int main(void) {
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    BNode *root = NULL;
    for (size_t i = 0; i < sizeof keys / sizeof keys[0]; i++) root = insert(root, keys[i]);
    puts("B-tree structure:");
    print_tree(root, 0);
    printf("Inorder: "); traverse(root); puts("");
    free_tree(root);
    return 0;
}
