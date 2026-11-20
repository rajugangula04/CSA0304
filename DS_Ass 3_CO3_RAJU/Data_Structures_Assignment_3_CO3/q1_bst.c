/*
 * Q1: Binary Search Tree (BST)
 * Operations: insert, search, inorder/preorder/postorder/level-order,
 * delete (all three cases), height, comparison count, save/rebuild demo.
 * Height convention: empty tree = -1, leaf = 0 (edge-based height).
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

static long comparisons = 0;

Node *new_node(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->key = key; n->left = n->right = NULL;
    return n;
}

Node *insert(Node *root, int key) {
    if (!root) return new_node(key);
    comparisons++;
    if (key < root->key) root->left = insert(root->left, key);
    else if (key > root->key) root->right = insert(root->right, key);
    /* Duplicate keys are ignored. */
    return root;
}

Node *search(Node *root, int key) {
    while (root) {
        comparisons++;
        if (key == root->key) return root;
        root = (key < root->key) ? root->left : root->right;
    }
    return NULL;
}

Node *minimum_node(Node *root) {
    while (root && root->left) root = root->left;
    return root;
}

Node *delete_node(Node *root, int key) {
    if (!root) return NULL;
    if (key < root->key) root->left = delete_node(root->left, key);
    else if (key > root->key) root->right = delete_node(root->right, key);
    else {
        if (!root->left) {
            Node *right = root->right; free(root); return right;
        }
        if (!root->right) {
            Node *left = root->left; free(root); return left;
        }
        Node *succ = minimum_node(root->right);
        root->key = succ->key;
        root->right = delete_node(root->right, succ->key);
    }
    return root;
}

int height(Node *root) {
    if (!root) return -1;
    int l = height(root->left), r = height(root->right);
    return 1 + (l > r ? l : r);
}
void inorder(Node *r) { if (r) { inorder(r->left); printf("%d ", r->key); inorder(r->right); } }
void preorder(Node *r) { if (r) { printf("%d ", r->key); preorder(r->left); preorder(r->right); } }
void postorder(Node *r) { if (r) { postorder(r->left); postorder(r->right); printf("%d ", r->key); } }

void levelorder(Node *root) {
    if (!root) return;
    int cap = 16, front = 0, rear = 0;
    Node **q = malloc((size_t)cap * sizeof(Node *));
    if (!q) { perror("malloc"); exit(EXIT_FAILURE); }
    q[rear++] = root;
    while (front < rear) {
        Node *cur = q[front++];
        printf("%d ", cur->key);
        if (rear + 2 > cap) {
            cap *= 2;
            Node **tmp = realloc(q, (size_t)cap * sizeof(Node *));
            if (!tmp) { free(q); perror("realloc"); exit(EXIT_FAILURE); }
            q = tmp;
        }
        if (cur->left) q[rear++] = cur->left;
        if (cur->right) q[rear++] = cur->right;
    }
    free(q);
}

/* Preorder serialization with # as a null marker. */
void save_preorder(Node *r, FILE *fp) {
    if (!r) { fprintf(fp, "# "); return; }
    fprintf(fp, "%d ", r->key);
    save_preorder(r->left, fp);
    save_preorder(r->right, fp);
}
Node *load_preorder(FILE *fp) {
    char token[64];
    if (fscanf(fp, "%63s", token) != 1) return NULL;
    if (token[0] == '#') return NULL;
    char *end; long value = strtol(token, &end, 10);
    if (*end != '\0') return NULL;
    Node *r = new_node((int)value);
    r->left = load_preorder(fp);
    r->right = load_preorder(fp);
    return r;
}
void free_tree(Node *r) { if (r) { free_tree(r->left); free_tree(r->right); free(r); } }

int main(void) {
    Node *root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80, 65};
    size_t n = sizeof(keys) / sizeof(keys[0]);
    for (size_t i = 0; i < n; i++) root = insert(root, keys[i]);

    printf("Inorder: "); inorder(root);
    printf("\nPreorder: "); preorder(root);
    printf("\nPostorder: "); postorder(root);
    printf("\nLevel-order: "); levelorder(root);
    printf("\nHeight (edges): %d\n", height(root));

    root = delete_node(root, 20);
    root = delete_node(root, 30);
    root = delete_node(root, 50);
    printf("After deleting 20, 30, 50 (inorder): "); inorder(root);
    printf("\n");

    FILE *fp = fopen("bst_preorder.txt", "w");
    if (fp) { save_preorder(root, fp); fclose(fp); puts("Saved tree to bst_preorder.txt"); }
    else puts("Could not save bst_preorder.txt");

    fp = fopen("bst_preorder.txt", "r");
    if (fp) {
        Node *rebuilt = load_preorder(fp); fclose(fp);
        printf("Rebuilt tree (inorder): "); inorder(rebuilt); printf("\n");
        free_tree(rebuilt);
    }
    free_tree(root);
    return 0;
}
