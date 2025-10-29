#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

/*basic functions to implement:
 * core: search, insert, delete
 * balancing: rotations, color flips
 * recoloring happens after insert or delete so i need some functions to help fix that
 */


// hi! i (keira) will heavily reference the logic and structure of my AVL tree project code because
// the trees are both very similar. i'll do my best to make clear where i reference everything
// but i'm also just adding this preface :3

struct Major { //holds all of the information relevant to the major
    string name;
    float avgSalary;
    float unemployRate;
    int unisWithMajor;

    Major(string w, float x, float y, int z ): name (w), avgSalary(x),  unemployRate(y), unisWithMajor(z) {}
    public:
      string getName() {
        return name;
      }
};

struct TreeNode { //this is essentially the same node struct i use in my AVL tree
    Major major;
    string majorName; //putting this in the treenode too just to make life easier
    int color; //adding the color of the node, 0 indicates black, 1 indicates red
    TreeNode* parent;
    TreeNode* left; //left and right are the left and right children
    TreeNode* right;

    TreeNode(Major x, TreeNode* dad, TreeNode* nullLeaf) : major(x), majorName(x.getName()), color(0), parent(dad), left(nullLeaf), right(nullLeaf) {}
};

//setting up some helper functions here:

//i'm sorting the nodes alphabetically by major name so these helpers just normalize the strings and compare them
static string norm(const string& name) { //makes the names all lower case
    string normName = "";
    for (unsigned char c : name) {
      normName.push_back(tolower(c));
    }
    return normName;
}

static bool compareName(const Major& a, const Major& b) { //compares two strings alphabetically
    //1 indicates that a comes before b alphabetically
    //-1 indicates that a comes after b alphabetically
    //0 indicates that a and b are identical names with identical salaries, unemployment rates, etc

    string aName = norm(a.name);
    string bName = norm(b.name);

    if (aName < bName) {
      return 1;
    }
    if (aName > bName) {
      return  -1;
    }

    // edging cases for ordering by name
    // using these when/if major names are identical (which they shouldn't be but yk)
    if (a.avgSalary < b.avgSalary) {
      return 1;
    }
    if (a.avgSalary > b.avgSalary) {
      return -1;
    }
    if (a.unemployRate < b.unemployRate) {
      return 1;
    }
    if (a.unemployRate > b.unemployRate) {
      return -1;
    }
    if (a.unisWithMajor < b.unisWithMajor) {
      return 1;
    }
    if (a.unisWithMajor > b.unisWithMajor) {
      return -1;
    }
    return 0;
}

class RedBlack {
  TreeNode* root = nullptr;
  TreeNode* nullLeaf = nullptr; //the null black leaves on the tree

  //some helper functions related to color
  void swapColors(TreeNode* a, TreeNode* b) { //util that just swaps colors
    if (!a || !b) {
      return;
      }
    int temp = a->color;
    a->color = b->color;
    b->color = temp;
  }

  void newColor(TreeNode* newTop, TreeNode* pushedDown) {
    if (!newTop || !pushedDown) return;
    newTop->color     = pushedDown->color;  // usually parent's old color
    pushedDown->color = 1;                  // red
  }

  //the rotate functions are pulled from my AVL project
  static TreeNode* rotateRight(TreeNode* parent) { //this should be O(1)
    TreeNode* child = parent->left; //i'm naming these based on how the nodes are originally arranged
    TreeNode* gChild = child->right; //this is just og grandchild

    parent->left = gChild;
    child->right = parent;
    child->parent = parent->parent;
    parent->parent = child;

    if (gChild != nullptr) {
      gChild->parent = parent;
    }

    return child;
  }

  static TreeNode* rotateLeft(TreeNode* parent) {
    TreeNode* child = parent->right;
    TreeNode* gChild = child->left;

    child->left = parent;
    parent->right = gChild;
    child->parent = parent->parent;
    parent->parent = child;

    if (gChild != nullptr) {
      gChild->parent = parent;
    }

    return child;
  }
//i'm setting up some functions to recolor and rotate the nodes after insertion/deletion
// here's a source i referenced to set up the recoloring and rotation cases:
// https://pages.cs.wisc.edu/~cs400/readings/Red-Black-Trees/
//remember red is 1 and black is 0
//the inserted node (i will call iNode) is always red

  void fixInsertHelper(TreeNode* iNode, bool left, TreeNode* (*a)(TreeNode*), TreeNode* (*b)(TreeNode*)) {
    //referencing this for passing functions as parameters:
    // https://www.geeksforgeeks.org/cpp/passing-a-function-as-a-parameter-in-cpp/
    // basically i'm making this function so i don't have to write out what is essentially the same code for when
    // the parent of iNode is a right or left subchild
    //when parent is left, pass rotate left as a, rotate right as b

    /* insert cases from https://pages.cs.wisc.edu/~cs400/readings/Red-Black-Trees/
  case 1: iNode's parent is black -> there is nothing to adjust
  case 2: iNode's parent is red -> go to 2 different subcases
  case 2a: iNode's uncle is black or null
  case 2b: iNode's uncle is red

 */
    TreeNode* papa = iNode->parent; // parent of iNode
    TreeNode* gpa = papa->parent; // grandparent
    TreeNode* uncle = gpa->left; //uncle
    if (left) {
      TreeNode* uncle = gpa->right; // uncle
    }
    if (uncle->color == 1) { //case 2b
      papa->color = 0;
      uncle->color = 0;
      if (gpa != root) {
        gpa->color = 1;
      }
      iNode = gpa;
    }
    else { //case 2a
      if ((left and iNode == papa->right) or (!left and iNode == gpa->left)) {
        iNode = papa;
        a(iNode);
        //these 2 lines just verify the identities of papa and gpa (in case i mess them up anywhere in my code)
        papa = iNode->parent;
        gpa = papa->parent;
      }
      papa->color = 0; //this will end the while loop bc papa isn't red anymore
      gpa->color = 1;
      b(gpa);
    }
  }

  void fixInsert(TreeNode* iNode) {
    while (iNode->parent->color == 1) { //while the color is parent is red (this handles case a)
      if (iNode->parent == iNode->parent->parent->left) { //figuring out if parent of iNode is a left child or right child
        //here parent is left child
        fixInsertHelper(iNode, true, &rotateLeft, &rotateRight);
      }
      else {
        //here parent is right child
        fixInsertHelper(iNode, false, &rotateRight, &rotateLeft);
      }
    }
    root->color = 0;  //just making sure
  }
    public:


};
