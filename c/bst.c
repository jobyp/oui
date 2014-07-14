#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

/*
  1. Insert at root.
  2. Right rotate
  3. Left rotate
  4. Delete node
  5. Balance BST
  6. Copy a BST (recursive & iterative)
  7. Join BSTs
 */


typedef struct Bst {
	unsigned key;
	struct Bst *left;
	struct Bst *right;
	struct Bst *p;
	
} bst_t;

typedef void (*tree_walk_func_t)(bst_t *t);

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

void free_tree(bst_t *root)
{
	if (root == NULL)
		return;
	free_tree( root->left);
	free_tree( root->right);
	free( root);
}

bst_t* populate_tree() 
{
	bst_t* root = NULL;
	char *line = NULL;
	size_t sz;
	unsigned n;

	while (getline( &line, &sz, stdin) > 0)
		
		if (isdigit( line[0])) {
			n = (unsigned) atoi( line);
			root = insert_tree( root,  alloc_node( n));
		}
	
	if (line != NULL)
		free( line);
	
	return root;
}

bst_t* maximum(bst_t *t)
{
	if (t->right)
		return maximum( t->right);
	else
		return t;
}

bst_t* minimum(bst_t *t)
{
	if (t->left)
		return minimum( t->left);
	else
		return t;
}

bst_t* successor(bst_t *t)
{
	if (t->right)
		return minimum( t->right);
	
	bst_t *x = t->p;
	while( x != NULL && x->right == t) {
		
		t = x;
		x = x->p;
	}
	return x;
}

void iterative_inorder_walk(bst_t* root)
{
	for( bst_t* n = minimum( root); n != NULL; n = successor( n))
		printf("%u ", n->key);
	return;
}


void print_tree(bst_t *root, tree_walk_func_t walk_fn)
{
	if (root) {
		walk_fn( root);
		printf("\n");
	}
}


void print_max(bst_t *root)
{
	if (root)
		printf("%u\n", maximum( root)->key);
}

void print_min(bst_t *root)
{
	if (root)
		printf("%u\n", minimum( root)->key);
}

int main()
{
	bst_t *root = populate_tree();

	print_tree( root, inorder_walk);
	print_tree( root, iterative_inorder_walk);
	print_min( root);
	print_max( root);
	free_tree( root);
	return 0;
}
