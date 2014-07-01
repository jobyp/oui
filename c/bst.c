#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bst {
	unsigned key;
	struct Bst *left;
	struct Bst *right;
	struct Bst *p;
	
} bst_t;


void inorder_walk(bst_t *t)
{
	if ( t == NULL)
		return;

	inorder_walk( t->left);
	printf( "%u ", t->key);
	inorder_walk( t->right);
}

bst_t* alloc_node(unsigned key)
{
	bst_t *n = malloc( sizeof( bst_t));
	if (n == NULL)
		return NULL;

	memset( n, 0, sizeof( bst_t));
	n->key = key;
	return n;
}

bst_t* insert_tree(bst_t *root, bst_t *n)
{
	if (root == NULL)
		return n;

	if (root->key < n->key) {   /* n is larger than current node */

		if (root->right)
			insert_tree( root->right, n);
		else {
			root->right = n;
			n->p = root;
		}
	}
	else { /* n is less than or equal to current node */
		if (root->left)
			insert_tree( root->left, n);
		else {
			root->left = n;
			n->p = root;
		}
	}
	
	return root;
}

bst_t* populate_tree() 
{
	return NULL;
}

int main()
{
	/* bst_t *root = NULL; */

	return 0;
}
