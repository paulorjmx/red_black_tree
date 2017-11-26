#ifndef RBTREE_H
    #define RBTREE_H
        typedef struct rbtree RBTREE; // struct that holds data

        RBTREE *rbtree_create(int n); // Create the red-black tree with root
        void rbtree_insert(RBTREE **tree, int n); // Insert new node with value "n" in the red-black tree
        void rbtree_delete(RBTREE **tree); // Delete all tree
        void rbtree_inorder(RBTREE *tree); // In order traversal
        void rbtree_preorder(RBTREE *tree); // Pre order traversal
        void rbtree_postorder(RBTREE *tree); // Post order traversal
        int rbtree_max(RBTREE *tree); // Get the max value on the tree
        int rbtree_min(RBTREE *tree); // Get the min value on the tree
        int rbtree_sucessor(RBTREE *tree, int n); // Get the greater next node of "n"
        int rbtree_predecessor(RBTREE *tree, int n); // Get the minor next node of "n"
#endif
