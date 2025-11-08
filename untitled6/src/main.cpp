#include <fstream>
#include <iostream>
#include "Menu.h"
//#include "hash.h"
#include "red-black.h"
using namespace std;


int Student::id_tracker = 0;


int main() {
    //set up the loop to stay on the menu unless exited, starts off with no data loaded and no data structure chosen, terminal input, initializing tree, Hashtable has an error currently so commented out
    bool exited = false;
    bool dsrb = false;
    bool loaded = false;
    bool student_selected = false;
    Student* selected_student;
    int new_input = 0;
    RedBlack rbtree;
    // HashTable<string, int> hashtree(10000);

    while(!exited) {
        DisplayMenu(dsrb, loaded);
        string input;
        cin >> input;
        try{new_input = stoi(input);}
        catch(...){ cout << "Invalid Input" << endl; continue;}
        switch(new_input) {
            // different menu options are in Menu.cpp( AJ will keep working on different options)
            case 0:
                exited = true;
                break;
            case 1:
                LoadDataSet(rbtree, "data/college_student_placement_dataset.csv"); // hashtree,
                dsrb = true;
                loaded = true;
                break;
            case 2: {
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                string id;
                cout << "Enter ID:" << endl;
                cin >> id;
                student_selected = true;
                if (dsrb) {
                    //selected_student = rbtree.search(id); (We need to match up the student class and the node class in some way)
                    cout << "Student" << id << " found" << endl;
                }
                else {
                    //selected_student = hashtree.search(id); (We need to match up the student class and the node class in some way)
                    cout << "Student" << id << " found" << endl;
                }
                break;
            }
            case 3:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                if (!student_selected) {
                    cout << "Error: No Student Selected" << endl;
                }
                break;
            case 4:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 5:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 6:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 7:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 8:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 9:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 10:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 11:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                break;
            case 12:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                }
                dsrb = false;
                break;
        }
    }
}