# Data Structures – Assignment 3 (CO3)
## Optimized Data Storage and Retrieval Using Tree-Based Structures

This folder contains standalone C programs for Q1–Q7, compile/run instructions, and expected-output notes.

## Files

| File | Question | Contents |
|---|---|---|
| `q1_bst.c` | Q1 | BST insert/search/traversals/delete/height/save and rebuild |
| `q2_avl.c` | Q2 | AVL insertion, rotations, traversals and height |
| `q3_btree.c` | Q3 | B-tree insertion (minimum degree 2), splits and traversal |
| `q4_red_black_tree.c` | Q4 | Red-black tree insertion and balancing |
| `q5_splay_tree.c` | Q5 | Splay rotations and access of keys 3 and 9 |
| `q6_trie.c` | Q6 | Trie insertion, exact search, prefix count and autocomplete |
| `q7_dictionary_design.c` | Q7 | Small demonstration of hash lookup + sorted-array prefix/range lookup |
| `EXPECTED_OUTPUTS.md` | All | Representative output and notes |
| `SUBMISSION_CHECKLIST.md` | All | Items to complete before submission |

## Compile and run

Use GCC or another C11-compatible compiler. Open a terminal in this folder.

### Windows (MinGW GCC)
```bash
gcc -std=c11 -Wall -Wextra q1_bst.c -o q1_bst.exe
q1_bst.exe
```

Repeat with the filename you want to run, for example:
```bash
gcc -std=c11 -Wall -Wextra q2_avl.c -o q2_avl.exe
q2_avl.exe
```

### Linux / macOS
```bash
gcc -std=c11 -Wall -Wextra q1_bst.c -o q1_bst
./q1_bst
```

Compile each file separately because every file has its own `main()` function.

## Important notes
- These are educational reference implementations, not production database libraries.
- `q1_bst.c` writes `bst_preorder.txt` into the current working directory when it runs.
- The BST height convention is edge-based: empty tree = -1 and leaf = 0.
- The AVL height convention is node-based: empty tree = 0 and leaf = 1.
- The exact starting tree for Q5 was not included in the supplied assignment text, so the Splay Tree program uses a documented sample tree.
- Q7 uses a small fixed dictionary to demonstrate the approach. For the assignment's full 200,000-word case, measure memory/time on the target device and document actual results.
- Timings, memory measurements and screenshots must be captured by running these programs on your computer. Do not report illustrative estimates as measured results.
