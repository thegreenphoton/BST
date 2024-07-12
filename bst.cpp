#include "bst.h"
#include <list>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

std::string to_string(const Pokemon& p) {
  return to_string(p.number) + ": " + p.name + " (" + p.type + ")";
}

BST::BST() {
  root = nullptr;
}

void BST::catchPokemon(const Pokemon& p) {

  BSTNode* poke = new BSTNode();
  poke->data = p;
  poke->key = p.number;
  poke->left = nullptr;
  poke->right = nullptr;
  poke->parent = nullptr;
  if(root == nullptr) {
    root = poke;
    return;
  }
  BSTNode* n = root;
  while(n!= nullptr) {
    if(poke->key < n->key) {
      if(n->left != nullptr) {
        n = n->left;
      }
      else {
        n->left = poke;
        poke->parent = n;
        return;
      }
    }
    else if (poke->key > n->key) {
      if (n->right != nullptr) {
        n = n->right;
      }
      else {
        n->right = poke;
        poke->parent = n;
        return;
      }
    }
    else {
      delete poke;
      return;
    }
  }
}

BST::BSTNode* BST::search(int key) const {
  BSTNode* n = root;

  while (n != nullptr) {
    if (key < n->key) {
      n = n->left;
    }
    else if (key > n->key) {
      n = n->right;
    }
    else {
      return n;
    }
  }
  return nullptr;
}

const Pokemon* BST::searchForPokemon(int key) const {
  BSTNode* n = search(key);
  if (n == nullptr) {
    return nullptr;
  }
  else {
    return &n->data;
  }
}

std::string BST::orderedListOfCaughtPokemon() const { return inOrder(root); }

std::string BST::inOrder(BSTNode* root) const {
  if (root == nullptr) {
    return "";
  }
  else {
    return inOrder(root->left) + to_string(root->data) + '\n' + inOrder(root->right);
  }
}

BST::BSTNode* BST::predecessor(BSTNode* n) const {
  if (n->lef != nullptr) {
    n = n->left;
    while (n->right != nullptr) {
      n = n->right;
    }
    return n;
  }
  else {
    int og = n->key;
    n = n->parent;
    while (n != nullptr && og < n->key) {
      n = n->parent;
    }
    if (n == nullptr) {
      return nullptr;
    }
    else {
      return n;
    }
  }
  return nullptr;
}

void BST::releasePokemon(int key) {
  if (!search(key)) {
  }
  else {
    remove(search(key));
  }
}

void BST::remove(BSTNode* n) {
  if (n->left == nullptr && n->right == nullptr) {
    if (n == root) {
      root = nullptr;
    }
    BSTNode* p = n->parent;
      if (n->key < p->key) {
        p->left = nullptr;
      }
      else {
        p->right = nullptr;
      }
    delete n;
  }
  else if ((n->left && !n->right) || (n->right && !n->left)) {
    if (n != root) {
      BSTNode* p = n->parent;
      if (n->left) {
        if (n == p->left) {
          p->left = n->left;
        }
        else {
          p->right = n->left;
        }
        n->left->parent = p;
      }
      else if (n->right) {
        if (n == p->left) {
          p->left = n->right;
        }
        else {
          p->right = n->right;
        }
        n->right->parent = p;
      }
      delete n;
    }
    else {
      if (n->left != nullptr) {
        root = n->right;
      }
      else if (n->right != nullptr) {
        root = n->right;
      }
    delete n;
    }
  }
  else {
    BSTNode* pred = predecessor(n); 
    Pokemon temp = pred->data;
    int tempkey = pred->key;
    remove(pred);
    n->data = temp;
    n->key = tempkey;
  }
}
  
