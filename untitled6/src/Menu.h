//
// Created by ajohnson21 on 11/3/2025.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "hash.h"
#include "student.h"
#include "red-black.h"
using namespace std;


void DisplayMenu(bool dsrb, bool loaded, Student* selected_student);
void Setup();
void LoadDataSet(HashTable<int, Student> hashtable, RedBlack& rbtree, const string& file); //RedBlack rbtree, HashTable<string, int> hashtable,

#endif //MENU_H
