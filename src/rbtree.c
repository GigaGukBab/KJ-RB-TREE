#include "rbtree.h"
#include <stdlib.h>

void _delete_node(rbtree *t, node_t *node);
node_t *_insert(rbtree *t, const key_t key);
node_t *_insert_fixup(rbtree *t, node_t *new_node);
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

void _delete_node(rbtree *t, node_t *node)
{
  // Base condition: if current node is NIL,
  //                 then it means we are at leaf node.
  if (node == t->nil)
  {
    return;
  }

  // post-order traversal (left->right->root)
  _delete_node(t, node->left);
  _delete_node(t, node->right);

  free(node);
}
void delete_rbtree(rbtree *t)
{
  // we don't need to call _delete_node when root node is NIL node
  // becase it means that root has no node for now.
  if (t->root != t->nil)
  {
    _delete_node(t, t->root);
  }

  // so we just free NIL node and rbtree memory.
  free(t->nil);
  free(t);
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
node_t *_insert(rbtree *t, const key_t key)
{
  // STEP1: initialize new node
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->color = RBTREE_RED;
  new_node->key = key;
  new_node->parent = t->nil;
  new_node->left = t->nil;
  new_node->right = t->nil;

  node_t *current = t->root;           // current comparsion node
  node_t *parent_of_new_node = t->nil; // current's parent candidate

  // STEP2: find location to insert node
  while (current != t->nil)
  {
    parent_of_new_node = current; // update parent candidate to current node
    if (new_node->key < current->key)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  new_node->parent = parent_of_new_node; // link new node's parent

  // STEP3: this procedure does bi-directional connection
  if (parent_of_new_node == t->nil) // if tree is empty,
  {
    t->root = new_node; // make new node to root.
  }
  else if (new_node->key < parent_of_new_node->key)
  {
    parent_of_new_node->left = new_node;
  }
  else
  {
    parent_of_new_node->right = new_node;
  }

  return new_node;
}

// CASE 1: 내 부모도 레드고, 내 삼촌도 레드야
//         내 부모의 색깔을 black으로 칠해
//         내 uncle의 색깔을 black으로 칠해
//         내 조상을 red로 칠해
//         내 조상으로 올라가서 다시 봐
// CASE 2: 내 조상 노드를 기준으로 내 부모 노드가 어디 있는지 확인했을 때, 그것을 기준으로 또 나는 내 부모 노드 기준으로 어디 있는가를 확인해줘

node_t *_insert_fixup(rbtree *t, node_t *new_node)
{
  node_t *current = new_node;

  // NOTE: loop should be running until new_node's parent's color isn't red.
  while (current->parent->color == RBTREE_RED) // check's current parent's node color here
  {
    // NOTE: Pre required job before check each cases: check current parent node's location
    if (current->parent == current->parent->parent->left) // if my parent's location is left of my ancestor,
    {
      node_t *current_uncle = current->parent->parent->right; // we can set my uncle's location to my ancestor's right.

      if (current_uncle->color == RBTREE_RED) // if my uncle node's color is RED, we check case 1.
      {
        current->parent->color = RBTREE_BLACK;
        current_uncle = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        current = current->parent->parent;
      }
      else // if my uncle node's color isn't RED, then we check case 2 -> 3 level.
      {
        if (current == current->parent->right)
        {
          current = current->parent;
          _rotate_left(t, current->parent);
        }
        current->parent->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        _rotate_right(t, current->parent->parent);
      }
    }
    else // if my parent's location is right of my ancestor,
    {
      node_t *current_uncle = current->parent->parent->left; // we can set my uncle's location to my ancestor's left.

      if (current_uncle->color == RBTREE_RED) // if my uncle node's color is RED, we check case 1.
      {
        current->parent->color = RBTREE_BLACK;
        current_uncle = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        current = current->parent->parent;
      }
      else // if my uncle node's color isn't RED, then we check case 2 -> 3 level.
      {
        if (current == current->parent->left)
        {
          current = current->parent;
          _rotate_right(t, current->parent);
        }
        current->parent->color = RBTREE_BLACK;
        current->parent->parent->color = RBTREE_RED;
        _rotate_left(t, current->parent->parent);
      }
    }
  }

  // color root node to black
  t->root->color = RBTREE_BLACK;

  return t->root;
}
node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // STEP: insert node
  node_t *new_node = _insert(t, key);

  // STEP: fix to Red-Black tree structure
  node_t *root = _insert_fixup(t, new_node);

  return root;
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
