#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  // TODO: initialize struct if needed
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
  nil_node->color = RBTREE_BLACK;
  p->root = nil_node;
  p->nil = nil_node;
  return p;
}

void delete_node(node_t *n, rbtree *t){
  if (n == t->nil){
    return;
  }
  delete_node(n->left,t);
  delete_node(n->right,t);
  free(n);
  n = NULL;
  return;
}
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if (t == NULL){
    return;
  }

  delete_node(t->root,t);
  free(t->nil);
  t->nil = NULL;
  free(t);
  t = NULL;
  return;
}

void left_rotate(rbtree *t, node_t *x){ // 왼쪽으로 회전하는 함수. (회전을 할 때는 부분 노드만 떼서 그 부분만 회전함.)
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil){
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == t->nil){
    t->root = y;
  } else if (x == x->parent->left){
    x->parent->right = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
  return;
}

void right_rotate(rbtree *t, node_t *y){ // 오른쪽으로 회전하는 함수. (회전을 할 때는 부분 노드만 떼서 그 부분만 회전함.)
  node_t *x = y->left;
  y->left = x->right;
  if (x->right != t->nil){
    x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == t->nil){
    t->root = x;
  } else if (y == y->parent->left){
    y->parent->left = x;
  } else{
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
  return;
}

void rbtree_insert_fixup(rbtree *t, node_t *z){
  while (z->parent->color == RBTREE_RED){
    if (z->parent == z->parent->parent->left){
      node_t *y = calloc(1,sizeof(node_t));
      y = z->parent->parent->right;
      if (y->color == RBTREE_RED){
        y->color = RBTREE_BLACK;
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }else{
        if (z->parent->right == z){
          z = z->parent;
          left_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t,z->parent->parent);
      }
    }else{
      node_t *y = calloc(1,sizeof(node_t));
      y = z->parent->parent->left;
      if (y->color == RBTREE_RED){
        z->parent->parent->color = RBTREE_RED;
        y->color = RBTREE_BLACK;
        z->parent->color = RBTREE_BLACK;
        z = z->parent->parent;
      }else{
        if (z->parent->left == z){
          z = z->parent;
          right_rotate(t,z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        left_rotate(t,z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
  return;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  node_t *y = t->nil;
  node_t *x = t->root;
  while (x!= t->nil){
    y = x;
    if (key < x->key){
      x = x->left;
    }else{
      x = x->right;
    }
  }
  node_t *z = calloc(1,sizeof(node_t));
  z->parent = y;
  if (y == t->nil){
    t->root = z;
  }else if (z->key < y->key){
    y->left = z;
  }else{
    y->right = z;
  }
  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  rbtree_insert_fixup(t,z);
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
