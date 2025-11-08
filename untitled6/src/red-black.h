#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Student.h"
using namespace std;

// hi! i (keira) will heavily reference the logic and structure of my AVL tree project code because
// the trees are both very similar. i'll do my best to make clear where i reference everything
// but i'm also just adding this preface :3

//also i noticed that a lot of my sources cited CLRS which i looked into and CLRS is apparently an influential CS textbook
//so i figured i would mention that a lot of the information i'm getting on red-black trees is coming from here

struct TreeNode { //this is essentially the same node struct i use in my AVL tree
    Major major;
    Student student; //adding student object to treenode
    int studentID;
    string majorName; //putting this in the treenode too just to make life easier
    int color; //adding the color of the node, 0 indicates black, 1 indicates red
    TreeNode* parent;
    TreeNode* left; //left and right are the left and right children
    TreeNode* right;

    TreeNode(Major x, Student y, TreeNode* dad, TreeNode* nullLeaf) : major(x), student(y), studentID(student.id), majorName(x.getName()), color(0), parent(dad), left(nullLeaf), right(nullLeaf) {}
};

class RedBlack {
  TreeNode* root = nullptr;
  TreeNode* nullLeaf = nullptr; //the null black leaves on the tree

  //the rotate functions are mostly pulled from my AVL project
  TreeNode* rotateRight(TreeNode* node) {
    if (node->left == nullLeaf) {
      return node;
    }
    TreeNode* subtree = node->left;
    TreeNode* child = subtree->right;
    //rotating
    subtree->right = node;
    node->left = child;
    subtree->parent = node->parent;
    node->parent = subtree;

    if (child != nullLeaf) {
      child->parent = node;
    }
    //relinking children here
    if (subtree->parent == nullLeaf) {
      root = subtree;
    }
    else if (subtree->parent->left == node) {
      subtree->parent->left = subtree;
    }
    else {
      subtree->parent->right = subtree;
    }
    return subtree;
  }

  TreeNode* rotateLeft(TreeNode* node) {
    if (node->right == nullLeaf) {
      return node;
    }
    TreeNode* subtree = node->right;
    TreeNode* child = subtree->left;

    subtree->left = node;
    node->right = child;
    subtree->parent = node->parent;
    node->parent = subtree;

    if (child != nullLeaf) {
      child->parent = node;
    }
    if (subtree->parent == nullLeaf) {
      root = subtree;
    } else if (subtree->parent->left == node) {
      subtree->parent->left = subtree;
    } else {
      subtree->parent->right = subtree;
    }
    return subtree;
  }

  // basically i'm making the insert/deleteRotateRecolor functions so i don't have to write out mirrored code
  void insertRotateRecolor(TreeNode*& iNode, bool left) {
    //remember red is 1 and black is 0
    // insert cases from https://pages.cs.wisc.edu/~cs400/readings/Red-Black-Trees/ are 1, 2a, 2b
    // also i referenced the code provided on slide 141 of the balanced trees slides from class :3
    TreeNode* papa = iNode->parent; // parent of iNode
    TreeNode* gpa = papa->parent; // grandparent
    TreeNode* uncle = gpa->left; //uncle
    if (left) {
      uncle = gpa->right;
    }
    if (uncle->color == 1) { //case 2b -> uncle is red
      papa->color = 0;
      uncle->color = 0;
      if (gpa != root) {
        gpa->color = 1;
      }
      iNode = gpa;
    }
    else { //case 2a -> uncle is black
      if ((left and iNode == papa->right) or (!left and iNode == papa->left)) { //mirrored logic done here
        iNode = papa;
        if (left) {
          rotateLeft(iNode);
        }
        else {
          rotateRight(iNode);
        }
        //these 2 lines just verify the identities of papa and gpa (in case i mess them up anywhere in my code)
        papa = iNode->parent;
        gpa = papa->parent;
      }
      papa->color = 0; //this will end the while loop bc papa isn't red anymore
      gpa->color = 1;
      if (left) {
        rotateRight(gpa);
      }
      else {
        rotateLeft(gpa);
      }
    }
  }

  void removeRotateRecolor(TreeNode* rNode) {
    //referencing this duke thingy:
    // https://users.cs.duke.edu/~reif/courses/alglectures/arge.lectures/Notes-RedBlackTrees.pdf
      bool left = (rNode == rNode->parent->left); //i had to update the value inside the function instead of passing it
      //as a parameter since this value will change as i work upwards
      TreeNode* sibling = rNode->parent->left;
      if (left) {
        sibling = rNode->parent->right;
      }
      if (sibling->color == 1) { //sibling is red
        sibling->color = 0;
        rNode->parent->color = 1;
        if (left) {
          rotateLeft(rNode->parent);
          sibling = rNode->parent->right;
        }
        else {
          rotateRight(rNode->parent);
          sibling = rNode->parent->left;
        }
      }
      if (sibling->left->color == 0 and sibling->right->color == 0) { //2 null children
        sibling->color = 1;
        rNode = rNode->parent;
      }
      else {
        if ((left and sibling->right->color == 0 and sibling->left->color == 1) or (!left and sibling->left->color == 0 and sibling->right->color == 1)) { //1 null child
          if (left) {
            sibling->left->color = 0;
          }
          else {
            sibling->right->color = 0;
          }
          sibling->color = 1;
          if (left) {
            rotateRight(sibling);
            sibling = rNode->parent->right;
          }
          else {
            rotateLeft(sibling);
            sibling = rNode->parent->left;
          }
        }
        sibling->color = rNode->parent->color;
        rNode->parent->color = 0;
        if (left) {
          sibling->right->color = 0;
          rotateLeft(rNode->parent);
        }
        else {
          sibling->left->color = 0;
          rotateRight(rNode->parent);
        }
        rNode = root; //it becomes the root (according to the duke reference)
      }
  }

  //another helper for the remove function, moves subtrees (duh)
  //just replaces the the deleted subtree with the other subtree parameter
  void subtreeManager(TreeNode* deleted, TreeNode* subtree) {
    //a and b are the roots of the subtrees to be managed
    if (deleted->parent == nullLeaf) {
      root = subtree;
    }
    else if (deleted->parent->left == deleted) { //if it's left subchild
      deleted->parent->left = subtree;
    }
    else {
      deleted->parent->right = subtree;
    }
    subtree->parent = deleted->parent;
  }

  //i need the inorder successor when deleting with 2 children
  //https://users.cs.duke.edu/~reif/courses/alglectures/arge.lectures/Notes-RedBlackTrees.pdf
  TreeNode* minimum(TreeNode* node) {
    while (node->left != nullLeaf) {
      node = node->left;
    }
    return node;
  }

    public:
      //public has the core functions: search, insert, remove (and an inorder traversal for funsies)
      RedBlack() {
        nullLeaf = new TreeNode(
            Major("", 0, "", 0.0, 0.0, 0.0, "", "", "", "", 0.0, 0.0, 0),
            Student("", "", "", "", "", "", "", "", "", ""),
            nullptr, nullptr
        );
        nullLeaf->color  = 0;
        nullLeaf->left   = nullLeaf;
        nullLeaf->right  = nullLeaf;
        nullLeaf->parent = nullLeaf;
        nullLeaf->majorName = "";

        root = nullLeaf;
      }

      //bc dynamically allocated memory :3
      ~RedBlack() {
            destroyTree(root);
            delete nullLeaf;
      }

      void destroyTree(TreeNode* node) {
            if (node == nullLeaf) {
              return;
            }
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
      }

    TreeNode* getRoot() {
        return root; //just a quick helper i used when testing out my code :3
      }

  //the search functions just use standard bst logic. nothing fancy here :)
      TreeNode* search(string id) {
        if (!isAllDigits(id)) {
          return nullLeaf;
        }
        int intID = stoi(id);
        TreeNode* traverse = root;
        while (traverse != nullLeaf and intID != traverse->studentID) {
            if (traverse->studentID > intID) {
                traverse = traverse->left;
            }
            else {
                traverse = traverse->right;
            }
        }
        return traverse;
      }

      TreeNode* search(Student student) {
        TreeNode* traverse = root;
        while (traverse != nullLeaf and student.id != traverse->studentID) {
          if (traverse->studentID > student.id) {
            traverse = traverse->left;
          }
          else {
            traverse = traverse->right;
          }
        }
        return traverse;
      }

      void inorder(const TreeNode* node, vector<string>& storeOrder) const {
        //this is pulled from my avl tree project
        if (node == nullLeaf) {
          return;
        }
          inorder(node->left, storeOrder);
          storeOrder.push_back((node->majorName));
          inorder(node->right, storeOrder);
      }

      //this is mostly pulled from my avl project (with relevant tweaks) because it just follows standard bst logic
      //the insertRotateRecolor function handles all of the red-black specific stuff
      void insert(Major major, Student student) {
        TreeNode* iNode = new TreeNode(major, student, nullLeaf, nullLeaf);
        iNode->color = 1;
        TreeNode* traverse = root; //start traversing at the root
        TreeNode* temp = nullLeaf; // provisional "parent" of iNode before i insert it
        while (traverse != nullLeaf) {
          temp = traverse;
          if (traverse->studentID > student.id) { //if root > iNode
            traverse = traverse->left;
          }
          else {
            traverse = traverse->right;
          }
        }
        iNode->parent = temp;
        if (temp == nullLeaf) {
          root = iNode;
        }
        else if (temp->studentID > student.id) { //if tempB > iNode
          temp->left = iNode;
        }
        else {
          temp->right = iNode;
        }
        while (iNode->parent->color == 1) { //while the color is parent is red (this handles case 1)
          if (iNode->parent == iNode->parent->parent->left) { //figuring out if parent of iNode is a left child or right child
            //here parent is left child
            insertRotateRecolor(iNode, true);
          }
          else {
            //here parent is right child
            insertRotateRecolor(iNode, false);
          }
        }
        root->color = 0;  //just making sure
      }

      void remove(Student student) {
        //referencing this: https://users.cs.duke.edu/~reif/courses/alglectures/arge.lectures/Notes-RedBlackTrees.pdf
        TreeNode* rNode = search(student);
        if (rNode == nullLeaf) {
          return; //node to be deleted does not exist
        }
        TreeNode* temp = rNode; //
        int saveTempColor = temp->color; //i use this to fix when both children are black
        TreeNode* replace; // child that moves into y's old position

        // borrowing a lot of bst delete logic from my avl tree project
        if (rNode->left == nullLeaf) { //one right subchild (or no children)
          replace = rNode->right;
          subtreeManager(rNode, rNode->right); //rNode->right is null when there's no children so the case is handled
        }
        else if (rNode->right == nullLeaf) { //one left subchild
          replace = rNode->left;
          subtreeManager(rNode, rNode->left);
        }
        else { //rNode has 2 children
          temp = minimum(rNode->right); //replacing with the inorder successor
          saveTempColor = temp->color;
          replace = temp->right;
          if (temp->parent == rNode) {
            replace->parent = temp;
          }
          else {
            subtreeManager(temp, temp->right);
            temp->right = rNode->right;
            temp->right->parent = temp;
          }
          subtreeManager(rNode, temp);
          temp->left = rNode->left;
          temp->left->parent = temp;
          temp->color = rNode->color;
        }
        delete rNode;

        if (saveTempColor == 0) {
          while (replace != root and replace->color == 0) {
            removeRotateRecolor(replace); //doing the red-black fixing stuff here
          }
        replace->color = 0; //just making sure i don't mess this value up anywhere
        }
      }
};
