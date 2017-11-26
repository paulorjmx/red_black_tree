#include <stdio.h>
#include <stdlib.h>
#include "inc/rbtree.h"

struct rbtree
{
    int n;
    struct rbtree *left, *right, *parent;
    char color; // BLACK: 0, RED: 1
};

RBTREE *rbtree_create(int n)
{
    RBTREE *new = NULL;
    new = (RBTREE *) malloc(sizeof(RBTREE));
    if(new == NULL)
    {
        printf("ERRO: NAO FOI POSSIVEL CRIAR A ARVORE!\n");
    }
    else
    {
        new->n = n;
        new->left = NULL;
        new->right = NULL;
        new->parent = NULL;
        new->color = '0';
    }

    return new;
}

RBTREE *rbtree_newnode(int n) // Utility function to create a new node
{
    RBTREE *new = NULL;
    new = (RBTREE *) malloc(sizeof(RBTREE));
    if(new == NULL)
    {
        printf("ERRO: NAO FOI POSSIVEL CRIAR A ARVORE!\n");
    }
    else
    {
        new->n = n;
        new->left = NULL;
        new->right = NULL;
        new->parent = NULL;
        new->color = '1'; // Create a new node with red color
    }

    return new;
}

void rbtree_insertbst(RBTREE **tree, int n)
{
    if((*tree) != NULL)
    {
        if(n < (*tree)->n)
        {
            if((*tree)->left != NULL)
            {
                (*tree)->left->parent = (*tree);
                rbtree_insertbst(&(*tree)->left, n);
            }
            else
            {
                (*tree)->left = rbtree_newnode(n);
                (*tree)->left->parent = (*tree);
            }
        }
        else
        {
            if((*tree)->right != NULL)
            {
                (*tree)->right->parent = (*tree);
                rbtree_insertbst(&(*tree)->right, n);
            }
            else
            {
                (*tree)->right = rbtree_newnode(n);
                (*tree)->right->parent = (*tree);
            }
        }
    }
    else
    {
        printf("ERRO: A ARVORE NAO EXISTE!\n");
    }
}

RBTREE *rbtree_search(RBTREE *tree, int n)
{
    if(tree != NULL)
    {
        if(n > tree->n)
        {
            return rbtree_search(tree->right, n);
        }
        else if(n < tree->n)
        {
            return rbtree_search(tree->left, n);
        }
        else
        {
            return tree;
        }
    }
}

RBTREE *rbtree_rotate_left(RBTREE *root)
{
    char tmp_color = -1;
    RBTREE *tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    tmp->parent = root->parent;
    root->parent = tmp;
    tmp_color = tmp->color;
    tmp->color = root->color;
    root->color = tmp_color;
    return tmp;
}

RBTREE *rbtree_rotate_right(RBTREE *root)
{
    char tmp_color = -1;
    RBTREE *tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    tmp->parent = root->parent;
    root->parent = tmp;
    tmp_color = tmp->color;
    tmp->color = root->color;
    root->color = tmp_color;
    return tmp;
}

void rbtree_insert(RBTREE **tree, int n)
{
    if((*tree) != NULL)
    {
        // char tmp_color = '0';
        RBTREE *ptr = NULL;
        rbtree_insertbst(tree, n);
        ptr = rbtree_search((*tree), n);
        while((ptr->parent != NULL) && (ptr->parent->color == '1') && (ptr->color != '0'))
        {
            if((ptr->parent->parent->left != NULL) && (ptr->parent->n == ptr->parent->parent->left->n)) // If parent of ptr is the left child of grandparent
            {
                // Case 1
                if(ptr->parent->parent->right != NULL && ptr->parent->parent->right->color == '1') // If uncle of ptr is red, change the color of parent, grandparent and uncle
                {
                    ptr->parent->color = '0'; // Parent color
                    ptr->parent->parent->right->color = '0'; // Uncle Color
                    ptr->parent->parent->color = '1'; // Grandparent Color;
                    ptr = ptr->parent->parent; // Up to the grandparent
                }
                // Case 2
                else if(ptr->parent->left != NULL && (ptr->parent->left->n == ptr->n)) // 'n' is the left child of his parent
                {
                    if(ptr->parent->parent == (*tree))
                        (*tree) = rbtree_rotate_right(ptr->parent->parent);
                    else
                        ptr->parent->parent->parent->left = rbtree_rotate_right(ptr->parent->parent);
                    ptr = ptr->parent;
                }
                else
                {
                    ptr->parent->parent->left = rbtree_rotate_left(ptr->parent);
                    ptr->parent->parent->left = rbtree_rotate_right(ptr->parent);
                    ptr = ptr->parent;
                }
            }
            else // 'n' if the right child of his parent
            {
                // Case 1
                if(ptr->parent->parent->left != NULL && ptr->parent->parent->left->color == '1') // If uncle of ptr is red, change the color of parent, grandparent and uncle
                {
                    ptr->parent->color = '0'; // Parent color
                    ptr->parent->parent->left->color = '0'; // Uncle Color
                    ptr->parent->parent->color = '1'; // Grandparent Color;
                    ptr = ptr->parent->parent; // Up to the grandparent
                }
                // Case 2
                else if(ptr->parent->right != NULL && (ptr->parent->right->n == ptr->n)) // 'n' is the right child of his parent
                {
                    if(ptr->parent->parent == (*tree))
                        (*tree) = rbtree_rotate_right(ptr->parent->parent);
                    else
                        ptr->parent->parent->parent->right = rbtree_rotate_left(ptr->parent->parent);
                    ptr = ptr->parent;
                }
                else // 'n' if the left child of his parent
                {
                    ptr->parent->parent->right = rbtree_rotate_right(ptr->parent);
                    ptr->parent->parent->right = rbtree_rotate_left(ptr->parent);
                    ptr = ptr->parent;
                }
            }
        }
        (*tree)->color = '0'; // Keep black color on root
    }
}

void rbtree_inorder(RBTREE *tree)
{
    if(tree != NULL)
    {
        rbtree_inorder(tree->left);
        printf("%d ", tree->n);
        rbtree_inorder(tree->right);
    }
}
void rbtree_preorder(RBTREE *tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->n);
        rbtree_preorder(tree->left);
        rbtree_preorder(tree->right);
    }
}

void rbtree_postorder(RBTREE *tree)
{
    if(tree != NULL)
    {
        rbtree_postorder(tree->left);
        rbtree_postorder(tree->right);
        printf("%d ", tree->n);
    }
}

int rbtree_predecessor(RBTREE *tree, int n)
{
    if(tree != NULL)
    {
        RBTREE *node = rbtree_search(tree, n), *tmp = NULL;
        if(node->left != NULL)
        {
            return rbtree_max(node->left);
        }
        else
        {
            tmp = node->parent;
            while(tmp != NULL && tmp->parent->n < node->n)
            {
                tmp = tmp->parent;
            }
            if(tmp != NULL)
            {
                return tmp->n;
            }
            else
            {
                return -1;
            }
        }
    }
    else
    {
        return -1;
    }
}

int rbtree_sucessor(RBTREE *tree, int n)
{
    if(tree != NULL)
    {
        RBTREE *node = rbtree_search(tree, n), *tmp = NULL;
        if(node->right != NULL)
        {
            return rbtree_min(node->right);
        }
        else
        {
            tmp = node->parent;
            while(tmp != NULL && tmp->n > node->n)
            {
                tmp = tmp->parent;
            }
            if(tmp != NULL)
            {
                return tmp->n;
            }
            else
            {
                return -1;
            }
        }
    }
    else
    {
        return -1;
    }
}

int rbtree_min(RBTREE *tree)
{
    if(tree != NULL)
    {
        if(tree->left != NULL)
        {
            rbtree_min(tree->left);
        }
        else
        {
            return tree->n;
        }
    }
    else
    {
        return 0;
    }
}

int rbtree_max(RBTREE *tree)
{
    if(tree != NULL)
    {
        if(tree->right != NULL)
        {
            rbtree_max(tree->right);
        }
        else
        {
            return tree->n;
        }
    }
    else
    {
        return 0;
    }
}

void rbtree_delete(RBTREE **tree)
{
    if((*tree) != NULL)
    {
        if((*tree)->left == NULL && (*tree)->right == NULL)
        {
            free((*tree));
            (*tree) = NULL;
        }
        else
        {
            rbtree_delete(&((*tree)->left));
            rbtree_delete(&((*tree)->right));
            free((*tree));
            (*tree) = NULL;
        }
    }
}
