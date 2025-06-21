#include "rbtree.h"
#include <stdlib.h>

void _delete_node(rbtree *t, node_t *node);

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
