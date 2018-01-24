#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/rbtree.h"

void rbtree_rotate_left(RBTREE **node, RBTREE **tree);
void rbtree_rotate_right(RBTREE **node, RBTREE **tree);

struct node
{
    int n;
    char color;
    struct node *parent, *left, *right;
};

RBTREE *rbtree_create(int value)
{
    RBTREE *new = NULL;
    new = (RBTREE *) malloc(sizeof(RBTREE));
    if(new != NULL)
    {
        new->n = value;
        new->color = '0';
        new->parent = NULL;
        new->left = NULL;
        new->right = NULL;
    }
    else
    {
        printf("ERROR: Could not possible create the binary search tree data structure.\n");
    }
    return new;
}

RBTREE *rbtree_create_node(int value)
{
    RBTREE *new = NULL;
    new = (RBTREE *) malloc(sizeof(RBTREE));
    if(new != NULL)
    {
        new->n = value;
        new->color = '1';
        new->left = NULL;
        new->right = NULL;
        new->parent = NULL;
    }
    else
    {
        printf("ERROR: Could not possible create the node.\n");
    }
    return new;
}

void rbtree_rotate_left(RBTREE **node, RBTREE **tree)
{
    RBTREE *ptr = (*node)->right;
    (*node)->right = ptr->left;
    if(ptr->left != NULL)
    {
        ptr->left->parent = (*node);
    }
    ptr->parent = (*node)->parent;
    if((*node) == (*tree))
    {
        (*tree) = ptr;
    }
    else if((*node)->n == (*node)->parent->left->n)
    {
        (*node)->parent->left = ptr;
    }
    else
    {
        (*node)->parent->right = ptr;
    }
    (*node)->parent = ptr;
    ptr->left = (*node);
    // (*node) = ptr;
}

void rbtree_rotate_right(RBTREE **node, RBTREE **tree)
{
    RBTREE *ptr = (*node)->left;
    (*node)->left = ptr->right;
    if(ptr->right != NULL)
    {
        ptr->right->parent = (*node);
    }
    ptr->parent = (*node)->parent;
    if((*node) == (*tree))
    {
        (*tree) = ptr;
    }
    else if((*node)->n == (*node)->parent->left->n)
    {
        (*node)->parent->left = ptr;
        ptr->parent = (*node)->parent;
    }
    else
    {
        (*node)->parent->right = ptr;
        ptr->parent = (*node)->parent;
    }
    (*node)->parent = ptr;
    ptr->right = (*node);
    // (*node) = ptr;
}

void rbtree_insert(RBTREE **tree, int value)
{
    if((*tree) != NULL)
    {
        RBTREE *ptr = NULL, *pnt = NULL, *uncle = NULL, *grandparent = NULL;
        ptr = (*tree);
        while(ptr != NULL)
        {
            pnt = ptr;
            if(value < ptr->n)
            {
                ptr = ptr->left;
            }
            else
            {
                ptr = ptr->right;
            }
        }
        if(value < pnt->n)
        {
            pnt->left = rbtree_create_node(value);
            pnt->left->parent = pnt;
            ptr = pnt->left;
        }
        else
        {
            pnt->right = rbtree_create_node(value);
            pnt->right->parent = pnt;
            ptr = pnt->right;
        }
        // Perform the fix
        while(ptr->parent != NULL && ptr->parent->color == '1' && 
        ptr->color != '0')
        {
            pnt = ptr->parent;
            grandparent = ptr->parent->parent;
            if(ptr->parent->parent->left != NULL && (ptr->parent->n == ptr->parent->parent->left->n))
            {
                uncle = ptr->parent->parent->right;
                if(uncle != NULL && uncle->color == '1')
                {
                    ptr->parent->parent->color = '1';
                    ptr->parent->color = '0';
                    uncle->color = '0';
                    ptr = grandparent;
                }
                else
                {
                    if(ptr->parent->right != NULL && ptr->n == ptr->parent->right->n)
                    {
                        rbtree_rotate_left(&pnt, tree);
                    }
                    rbtree_rotate_right(&grandparent, tree);
                    grandparent->parent->color = '0';
                    grandparent->color = '1';
                }
            }
            else
            {
                uncle = ptr->parent->parent->left;
                if(uncle != NULL && uncle->color == '1')
                {
                    ptr->parent->parent->color = '1';
                    ptr->parent->color = '0';
                    uncle->color = '0';
                    ptr = grandparent;
                }
                else
                {
                    if(ptr->parent->left != NULL && ptr->n == ptr->parent->left->n)
                    {
                        rbtree_rotate_right(&pnt, tree);
                    }
                    rbtree_rotate_left(&grandparent, tree);
                    grandparent->parent->color = '0';
                    grandparent->color = '1';
                }
            }
        }
        (*tree)->color = '0';
    }
    else
    {
        printf("ERROR: The tree is empty.\n");
    }
}

int rbtree_minimum(RBTREE *tree)
{
    if(tree != NULL)
    {
        RBTREE *ptr = tree;
        while(ptr->left != NULL)
        {
            ptr = ptr->left;
        }
        return ptr->n;
    }
    else
    {
        printf("ERROR: The data structure is empty.\n");
        return -1;
    }
}

int rbtree_maximum(RBTREE *tree)
{
    if(tree != NULL)
    {
        RBTREE *ptr = tree;
        while(ptr->right != NULL)
        {
            ptr = ptr->right;
        }
        return ptr->n;
    }
    else
    {
        printf("ERROR: The data structure is empty.\n");
        return -1;
    }
}

void rbtree_delete_node(RBTREE **tree, int value)
{
    if((*tree) != NULL)
    {
        RBTREE **ptr = tree;
        while((*ptr)->left != NULL || (*ptr)->right != NULL)
        {
            if(value < (*ptr)->n)
            {
                ptr = &(*ptr)->left;
            }
            else if(value > (*ptr)->n)
            {
                ptr = &(*ptr)->right;
            }
            else
            {
                break;
            }
        }
        if((*ptr) != NULL)
        {
            if((*ptr)->left == NULL && (*ptr)->right == NULL)
            {
                free((*ptr));
                (*ptr) = NULL;
            }
            else
            {
                if((*ptr)->left == NULL)
                {
                    (*ptr)->n = (*ptr)->right->n;
                    free((*ptr)->right);
                    (*ptr)->right = NULL;
                }
                else if((*ptr)->right == NULL)
                {
                    (*ptr)->n = (*ptr)->left->n;
                    free((*ptr)->left);
                    (*ptr)->left = NULL;
                }
                else
                {
                    (*ptr)->n = rbtree_minimum((*ptr)->right);
                    rbtree_delete_node(&((*ptr)->right), (*ptr)->n);
                }
            }
        }
        else
        {
            printf("ERROR: The value %d doesn't exists.\n", value);
        }
    }
    else
    {
        printf("ERROR: The data structure doesn't exists.\n");
    }
}

int rbtree_predecessor(RBTREE *tree, int value)
{
    int pred = -1;
    if(tree != NULL)
    {
        RBTREE *ptr = tree;
        while(ptr->left != NULL || ptr->right != NULL)
        {
            if(value < ptr->n)
            {
                ptr = ptr->left;
            }
            else if(value > ptr->n)
            {
                ptr = ptr->right;
            }
            else
            {
                break;
            }
        }
        if(ptr != NULL)
        {
            if(ptr->left != NULL)
            {
                pred = rbtree_maximum(ptr->left);
            }
            else
            {
                pred = ptr->n;
                while(ptr->parent != NULL && ptr->parent->n > ptr->n)
                {
                    ptr = ptr->parent;
                }
                if(ptr->parent != NULL && ptr->parent->n < pred)
                {
                    pred = ptr->parent->n;
                }
                else
                {
                    pred = -1;
                }
            }
        }
        else
        {
            printf("ERROR: The value %d is not on the tree.\n", value);
        }
    }
    return pred;
}

int rbtree_sucessor(RBTREE *tree, int value)
{
    int suc = -1;
    if(tree != NULL)
    {
        RBTREE *ptr = tree;
        while(ptr->left != NULL || ptr->right != NULL)
        {
            if(value < ptr->n)
            {
                ptr = ptr->left;
            }
            else if(value > ptr->n)
            {
                ptr = ptr->right;
            }
            else
            {
                break;
            }
        }
        if(ptr != NULL)
        {
            if(ptr->right != NULL)
            {
                suc = rbtree_minimum(ptr->right);
            }
            else
            {
                suc = ptr->n;
                while(ptr->parent != NULL && ptr->parent->n < ptr->n)
                {
                    ptr = ptr->parent;
                }
                if(ptr->parent != NULL && ptr->parent->n > suc)
                {
                    suc = ptr->parent->n;
                }
                else
                {
                    suc = -1;
                }
            }
        }
        else
        {
            printf("ERROR: The value %d is not on the tree.\n", value);
        }
    }
    return suc;
}

void rbtree_print_preorder(RBTREE *tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->n, tree->color);
        rbtree_print_preorder(tree->left);
        rbtree_print_preorder(tree->right);
    }
}

void rbtree_print_inorder(RBTREE *tree)
{
    if(tree != NULL)
    {
        rbtree_print_inorder(tree->left);
        printf("%d ", tree->n);
        rbtree_print_inorder(tree->right);
    }
}

void rbtree_print_postorder(RBTREE *tree)
{
    if(tree != NULL)
    {
        rbtree_print_postorder(tree->left);
        rbtree_print_postorder(tree->right);
        printf("%d ", tree->n);
    }
}

void rbtree_delete(RBTREE **tree)
{
    if((*tree) != NULL)
    {
        rbtree_delete(&(*tree)->left);
        rbtree_delete(&(*tree)->right);
        free((*tree));
        (*tree) = NULL;
    }
}

void rbtree_level_order(RBTREE *tree)
{
    if(tree != NULL)
    {
        int i = 0, j = 0;
        RBTREE *queue[10000];
        memset(queue, 0, sizeof(queue));
        queue[j] = tree;
        while(queue[i] != 0)
        {
            printf("%d ", queue[i]->n);
            if(queue[i]->left != NULL)
            {
                queue[++j] = queue[i]->left;
            }
            if(queue[i]->right != NULL)
            {
                queue[++j] = queue[i]->right;
            }
            i++;
        }
    }
    else
    {
        printf("ERROR: The data structure doesn't exists.\n");
    }
}
