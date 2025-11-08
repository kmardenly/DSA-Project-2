#include <fstream>
#include <iostream>
#include "Menu.h"
#include "hash.h"
#include "red-black.h"
using namespace std;


int Student::id_tracker = 0;


int main() {
    //set up the loop to stay on the menu unless exited, starts off with no data loaded and no data structure chosen, terminal input, initializing tree, Hashtable has an error currently so commented out
    bool exited = false;
    bool dsrb = false;
    bool loaded = false;
    Student* selected_student = nullptr;
    int new_input = 0;
    RedBlack rbtree;
    HashTable<int, Student> hashtable(10000);

    while(!exited) {
        DisplayMenu(dsrb, loaded, selected_student);
        string input;
        cin >> input;
        try{new_input = stoi(input);}
        catch(...){ cout << "Invalid Input\n" << endl; continue;}
        switch(new_input) {
            // different menu options are in Menu.cpp( AJ will keep working on different options)
            case 0:
                exited = true;
                break;
            case 1:
                LoadDataSet(hashtable, rbtree, "data/college_student_placement_dataset.csv"); // hashtree,
                dsrb = true;
                loaded = true;
                break;
            case 2: {
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                string search_id;
                int id;
                cout << "Enter ID:" << endl;
                cin >> search_id;
                try{id = stoi(search_id);}
                catch(...){ cout << "Invalid ID\n" << endl; continue;}
                if (dsrb) {
                    TreeNode* node = rbtree.search(to_string(id));
                    if (node) {
                        selected_student = &(node->student);
                    }
                    else {
                        cout << "Error: Student Not Found" << endl;
                    }

                    cout << "Student " << id << " found" << endl;
                }
                else {
                    if (hashtable.if_contains(id)) {
                        cout << "Student " << id << " found" << endl;
                        selected_student = &(hashtable.get(id));
                    }
                    else {
                        cout << "Error: Student " << "not " << " found" << endl;
                    }

                }
                break;
            }
            case 3:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 4:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }

            case 5:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 6:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 7:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 8:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 9:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 10:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 11:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
            case 12:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                dsrb = false;
                break;
        }
    }
}