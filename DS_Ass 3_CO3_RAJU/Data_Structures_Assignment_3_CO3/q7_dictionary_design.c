/*
 * Q7: Small demonstration of the proposed dictionary design:
 * hash table for exact lookup + sorted array for prefix/range queries.
 * This is a teaching demo with a fixed sample dictionary, not a production
 * implementation for 200,000+ words.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDS 10
#define TABLE_SIZE 31
#define MAX_WORD 64

static const char *dictionary[WORDS] = {
    "apple", "apply", "apt", "banana", "band", "bandage",
    "cat", "catalog", "cater", "dog"
};
static const char *hash_table[TABLE_SIZE];

unsigned long hash_word(const char *s) {
    unsigned long h = 5381;
    while (*s) h = ((h << 5) + h) + (unsigned char)*s++;
    return h % TABLE_SIZE;
}
void hash_insert(const char *word) {
    unsigned long i = hash_word(word);
    while (hash_table[i] && strcmp(hash_table[i], word) != 0)
        i = (i + 1) % TABLE_SIZE;
    hash_table[i] = word;
}
int hash_search(const char *word) {
    unsigned long i = hash_word(word), start = i;
    while (hash_table[i]) {
        if (strcmp(hash_table[i], word) == 0) return 1;
        i = (i + 1) % TABLE_SIZE;
        if (i == start) break;
    }
    return 0;
}
int lower_bound(const char *key) {
    int lo = 0, hi = WORDS;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (strcmp(dictionary[mid], key) < 0) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
void prefix_search(const char *prefix) {
    size_t len = strlen(prefix);
    int i = lower_bound(prefix), found = 0;
    printf("Autocomplete '%s': ", prefix);
    while (i < WORDS && strncmp(dictionary[i], prefix, len) == 0) {
        printf("%s ", dictionary[i++]); found = 1;
    }
    if (!found) printf("(no matches)");
    puts("");
}
void range_search(const char *low, const char *high) {
    int i = lower_bound(low), found = 0;
    printf("Range [%s, %s]: ", low, high);
    while (i < WORDS && strcmp(dictionary[i], high) <= 0) {
        printf("%s ", dictionary[i++]); found = 1;
    }
    if (!found) printf("(empty)");
    puts("");
}
int main(void) {
    for (int i = 0; i < WORDS; i++) hash_insert(dictionary[i]);
    printf("Exact lookup 'catalog': %s\n", hash_search("catalog") ? "FOUND" : "NOT FOUND");
    printf("Exact lookup 'car': %s\n", hash_search("car") ? "FOUND" : "NOT FOUND");
    prefix_search("app");
    prefix_search("ban");
    range_search("band", "cat");
    return 0;
}
