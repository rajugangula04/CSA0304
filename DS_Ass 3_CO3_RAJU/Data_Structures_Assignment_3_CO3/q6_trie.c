/*
 * Q6: Trie for lowercase English contacts.
 * Supports insertion, exact search, prefix count and autocomplete.
 * Prefix count is stored in each node and counts words passing through it.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET 26
typedef struct Trie {
    struct Trie *child[ALPHABET];
    int end;
    int words;
} Trie;

Trie *node(void) {
    Trie *t = calloc(1, sizeof *t);
    if (!t) { perror("calloc"); exit(EXIT_FAILURE); }
    return t;
}
void insert(Trie *t, const char *word) {
    Trie *cur = t;
    for (size_t i = 0; word[i]; i++) {
        int idx = tolower((unsigned char)word[i]) - 'a';
        if (idx < 0 || idx >= ALPHABET) continue;
        if (!cur->child[idx]) cur->child[idx] = node();
        cur = cur->child[idx];
        cur->words++;
    }
    cur->end = 1;
}
int search_word(const Trie *t, const char *word) {
    const Trie *cur = t;
    for (size_t i = 0; word[i]; i++) {
        int idx = tolower((unsigned char)word[i]) - 'a';
        if (idx < 0 || idx >= ALPHABET) return 0;
        if (!cur->child[idx]) return 0;
        cur = cur->child[idx];
    }
    return cur->end;
}
int count_prefix(const Trie *t, const char *prefix) {
    const Trie *cur = t;
    if (!prefix[0]) return cur->words; /* root count is not maintained in this demo */
    for (size_t i = 0; prefix[i]; i++) {
        int idx = tolower((unsigned char)prefix[i]) - 'a';
        if (idx < 0 || idx >= ALPHABET || !cur->child[idx]) return 0;
        cur = cur->child[idx];
    }
    return cur->words;
}
void autocomplete(const Trie *cur, char *buffer, int depth) {
    if (!cur) return;
    if (cur->end) { buffer[depth] = '\0'; printf("%s ", buffer); }
    for (int i = 0; i < ALPHABET; i++) {
        if (cur->child[i]) {
            buffer[depth] = (char)('a' + i);
            autocomplete(cur->child[i], buffer, depth + 1);
        }
    }
}
const Trie *find_prefix(const Trie *t, const char *prefix) {
    const Trie *cur = t;
    for (size_t i = 0; prefix[i]; i++) {
        int idx = tolower((unsigned char)prefix[i]) - 'a';
        if (idx < 0 || idx >= ALPHABET || !cur->child[idx]) return NULL;
        cur = cur->child[idx];
    }
    return cur;
}
void free_trie(Trie *t) {
    if (!t) return;
    for (int i = 0; i < ALPHABET; i++) free_trie(t->child[i]);
    free(t);
}
int main(void) {
    const char *contacts[] = {"anand", "anitha", "anu", "arun", "bala", "anusuya"};
    const char *prefixes[] = {"a", "an", "anu", "b", "z"};
    Trie *root = node();
    for (size_t i = 0; i < sizeof contacts / sizeof contacts[0]; i++) insert(root, contacts[i]);

    for (size_t i = 0; i < sizeof prefixes / sizeof prefixes[0]; i++)
        printf("%s:%d%s", prefixes[i], count_prefix(root, prefixes[i]),
               i + 1 == sizeof prefixes / sizeof prefixes[0] ? "\n" : " ");

    printf("Search 'anand': %s\n", search_word(root, "anand") ? "FOUND" : "NOT FOUND");
    printf("Search 'ananya': %s\n", search_word(root, "ananya") ? "FOUND" : "NOT FOUND");
    const char *p = "an";
    const Trie *start = find_prefix(root, p);
    char buffer[256];
    if (start) {
        strcpy(buffer, p);
        printf("Autocomplete '%s': ", p);
        autocomplete(start, buffer, (int)strlen(p));
        puts("");
    }
    free_trie(root);
    return 0;
}
