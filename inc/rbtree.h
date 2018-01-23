#ifndef RBTREE_H
    #define RBTREE_H
        typedef struct node RBTREE;

        RBTREE *rbtree_create(int value);
        void rbtree_insert(RBTREE **tree, int value);
        void rbtree_delete_node(RBTREE **tree, int value);
        int rbtree_minimum(RBTREE *tree);
        int rbtree_maximum(RBTREE *tree);
        int rbtree_predecessor(RBTREE *tree, int value);
        int rbtree_sucessor(RBTREE *tree, int value);
        void rbtree_print_preorder(RBTREE *tree);
        void rbtree_print_inorder(RBTREE *tree);
        void rbtree_print_postorder(RBTREE *tree);
        void rbtree_level_order(RBTREE *tree);
        void rbtree_delete(RBTREE **tree);
#endif
