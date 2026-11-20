# Representative Output Notes

Output ordering can vary only if you change the keys or implementation. The following are representative outputs for the supplied sample inputs.

## Q1 – BST
The final inorder after deleting 20, 30 and 50 should be:
```text
40 60 65 70 80
```
The program also prints traversals, edge-based height, saves the tree to `bst_preorder.txt`, then rebuilds it.

## Q2 – AVL
For insertion sequence `10, 20, 30, 40, 50, 25`:
```text
Inorder: 10 20 25 30 40 50
Preorder: 30 20 10 25 40 50
Height (nodes): 3
Root: 30
```

## Q3 – B-Tree
Inorder should be:
```text
5 6 7 10 12 17 20 30
```
The program prints the keys by level as well.

## Q4 – Red-Black Tree
Inorder with colours should be sorted by key and each node is printed as `key(R)` or `key(B)`. The root is black.

## Q5 – Splay Tree
The inorder traversal remains:
```text
3 5 7 9 10 12 15 18
```
After accessing an existing key, that key should become the root.

## Q6 – Trie
The prefix-count line should be:
```text
a:6 an:4 anu:2 b:1 z:0
```
Note: the assignment text says `a:5`, but the supplied six contacts include five contacts beginning with `a`? Recount before submission: `anand`, `anitha`, `anu`, `arun`, and `anusuya` begin with `a`, so the expected count is `a:5`. The executable should therefore print:
```text
a:5 an:4 anu:2 b:1 z:0
```
Autocomplete for `an` should include `anand anitha anu anusuya` in alphabetical order.

## Q7 – Dictionary demo
The program shows exact lookup, autocomplete for `app` and `ban`, and a lexical range query. The demo dictionary is intentionally small; replace it with the complete dictionary if you implement the full project.
