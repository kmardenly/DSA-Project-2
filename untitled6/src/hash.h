#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;


template<typename K, typename V>
class HashTable {
  private:
    int TableSize ;
    int num_elements;
    vector<list<pair<K, V>>> table; //each bucket in vector its own linked list with key and value
    float curr_load_factor;
    float max_load_factor = 0.75;
    //computes the current load factor
    float load_factor() {
      curr_load_factor = (float)num_elements / TableSize;
      return curr_load_factor;
    }
    //hash function determines index of each key value pair
    int hash(K key) const{
      double num = 0.6180339887;
      double diff = key * num - int(key * num);
      int index = int(TableSize * diff); //computes for index
      return index;
    }
    //function that doubles TableSize and rehashes all key, value pairs
    void rehash() {
      int old_size = TableSize;
      TableSize *= 2; //doubles tablesize
      vector<list<pair<K, V>>> new_table(TableSize); //creates new table with the doubled size
      for (int i = 0; i < old_size; i++) {
        for (auto& node : table[i]) { //goes through all key value pairs
          K& k = node.first;
          V& v = node.second;
          int new_index = hash(k); //hashes for the new index using doubles tablesize
          new_table[new_index].push_back(make_pair(k, v)); //pushes pairs for each new_index
        }
      }
      table = new_table; //sets new table as current table

    }
   public:
     //constructor to create the table
     explicit HashTable(int size) : TableSize(size), num_elements(0), table(TableSize), curr_load_factor(0.0f) {}
     ~HashTable() = default; //destructor set to default
     //inserts a pair of key and node into the hashtable
     void insert(const K& key, const V& node) {
       int index = hash(key); //uses hash function to determine index in vector
       for (auto& p : table[index]) { //updates pair if it has the same key
         if (p.first == key) {
           p.second = node; //updates value if key is found
           return;
         }
       }
       table[index].push_back(make_pair(key, node)); //inputs pair using index when key is unique
       num_elements++; //keeps count of elements
       curr_load_factor = load_factor(); //updates curr load factor
       if (curr_load_factor >= max_load_factor) { //rehashes when curr load size is greater or equal to max
         rehash();
       }
     }
     //function when called will remove a particular key from the hashtable
     void remove(const K& key) {
       int index = hash(key); //gets index using hash function
       auto iter = table[index].begin();
       while (iter != table[index].end()) { //iterates through hashtable
         if (iter->first == key) { //when it finds the key it erases that key value pair
           iter = table[index].erase(iter);
           --num_elements; //decreases num of elements when deleted
           curr_load_factor = load_factor(); // updates current load factor when num_elements changes
           return;
         }
         else {
           ++iter;
         }
       }
     }
    //function that returns the value in the key value pair when given the key
     V& get(const K& key) {
       int index = hash(key);
       for (auto& p : table[index]) {
         if (p.first == key) {
           return p.second;
         }
       }
       throw std::out_of_range("Key not found");
     }
    //this functions checks if the key is in the hashtable
    bool if_contains(const K& key) {
       try {
         get(key);
         return true;
       }
       catch (const runtime_error) {
         return false;
       }
     }
    int getNum_elements() const {
       return num_elements;
     }
    int get_TableSize() const {
       return TableSize;
     }
    void clear() {
     for (auto& list : table) {
         list.clear();
     }
     num_elements = 0;
     curr_load_factor = 0.0f;
     }
};
