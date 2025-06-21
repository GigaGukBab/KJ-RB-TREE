#include "rbtree.h"
#include <stdlib.h>

void _delete_node(rbtree *t, node_t *node);
void _rotate_left(rbtree *t, node_t *x);
void _rotate_right(rbtree *t, node_t *x);

rbtree *new_rbtree(void)
{
  // initalize rbtree structure
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));

  // initalize NIL node
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil->color = RBTREE_BLACK;
  nil->key = 0;
  nil->parent = NULL;
  nil->left = NULL;
  nil->right = NULL;

  t->nil = nil;
  t->root = nil;

  return t;
}

void _rotate_left(rbtree *t, node_t *x)
{
  node_t *y = x->right;
  node_t *beta = y->left;

  x->right = beta;

  if (beta != t->nil) // if y's left node is NIL node, then we don't have to update NIL node's parent.
  {
    y->left->parent = x; // Beta's parent is not conneted, so we update Beta's parent to x.
  }
  y->parent = x->parent;

  if (x->parent == t->nil) // if current x parent node is nil node, we just make y to root.
  {
    t->root = y;
  }
  else if (x->parent->left == x)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

void _rotate_right(rbtree *t, node_t *y)
{
  node_t *x = y->left;
  node_t *beta = x->right;

  y->left = beta;

  if (beta != t->nil)
  {
    beta->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == t->nil)
  {
    t->root = x;
  }
  else if (y->parent->left == y)
  {
    y->parent->left = x;
  }
  else
  {
    y->parent->right = x;
  }

  x->right = y;
  y->parent = x;
}

void _delete_node(rbtree *t, node_t *node)
{
  // Base condition: if node is NIL node, then return.
  if (node == t->nil)
  {
    return;
  }

  _delete_node(t, node->left);
  _delete_node(t, node->right);

  free(node);
}

void delete_rbtree(rbtree *t)
{
  _delete_node(t, t->root);
  t->root = NULL;
  free(t->root);
  free(t->nil);
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
