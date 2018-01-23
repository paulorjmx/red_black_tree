#include <stdio.h>
#include <stdlib.h>
#include "inc/rbtree.h"

int main(int argc, char *argv[])
{
	int opt = 0, data = 0, n_op = 0, i = 0, result = 0;
	// RBTREE *t = rbtree_create(5);
	// rbtree_insert(&t, 4);
	// rbtree_insert(&t, 3);
	// rbtree_insert(&t, 2);
	// rbtree_insert(&t, 1);
	// printf("%d\n", rbtree_predecessor(t, 1));
	// printf("%d\n", rbtree_sucessor(t, 1));
	// printf("%d\n", rbtree_max(t));
	// printf("%d\n", rbtree_min(t));
	// rbtree_inorder(t);
	// rbtree_preorder(t);
	// printf("\n",);
	// printf("%d\n", rbtree_predecessor(t, 1));
	RBTREE *t = NULL;
	scanf("%d", &n_op);
	for(i = 0; i < n_op; i++)
	{
		scanf("%d", &opt);
		if(opt == 1)
		{
			scanf("%d", &data);
			if(i == 0)
			{
				t = rbtree_create(data);
			}
			else
			{
				rbtree_insert(&t, data);
			}
		}
		else if(opt == 2)
		{
			scanf("%d", &data);
			result = rbtree_sucessor(t, data);
			if(result != -1)
			{
				printf("%d\n", result);
			}
			else
			{
				printf("erro\n");
			}
		}
		else if(opt == 3)
		{
			scanf("%d", &data);
			result = rbtree_predecessor(t, data);
			if(result != -1)
			{
				printf("%d\n", result);
			}
			else
			{
				printf("erro\n");
			}
		}
		else if(opt == 4)
		{
			printf("%d\n", rbtree_maximum(t));
		}
		else if(opt == 5)
		{
			printf("%d\n", rbtree_minimum(t));
		}
		else if(opt == 6)
		{
			rbtree_print_preorder(t);
			printf("\n");
		}
		else if(opt == 7)
		{
			rbtree_print_inorder(t);
			printf("\n");
		}
		else
		{
			rbtree_print_postorder(t);
			printf("\n");
		}
	}
	rbtree_delete(&t);
	return 0;
}
