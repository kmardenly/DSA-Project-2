#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "red-black.h"
using namespace std;

//node used for linked list in separte chaining implementation
struct HashNode {
    Major key; //major node containing all major attributes
    HashNode* next; //pointer to next node in linked list
    //constructor
    HashNode(Major k) : key(k), next(nullptr) {}
};


class HashTable {
  private:
    int TableSize = 50;
    int num_elements = 0;
    vector<HashNode*> table;
    float curr_load_factor = (float)num_elements / TableSize;
    float max_load_factor = 0.75;
    //hash function determines index of each major node
    int hash(Major node) {
      int hash_val = 0;
      string key = node.getName() + node.year;
      for (char c : key) { //uses the sum of ASCII char of major name and year
        hash_val += static_cast<int>(c);
      }
      int index = hash_val % TableSize;
      return index;
    }
   public:
     //constructor to create the table
     HashTable() : table(TableSize, nullptr), num_elements(0), curr_load_factor(0.0f), max_load_factor(0.75f) {}
     ~HashTable() {}
     void insert(Major key, HashNode* node) {}
     void remove(Major key, HashNode* node) {}
     float load_factor() {
       return curr_load_factor;
     }
     void search(Major key) {}
};
