#include <fstream>
#include <iostream>
#include "Menu.h"
#include "hash.h"
#include "red-black.h"
#include <chrono>
using namespace std;

//sets the id tracker to 0 so we can enumerate all 10,000 students with 10 attributes each
int Student::id_tracker = 0;

//Our project has 100,000 data points spread across 10,000 student objects stored within a hash map and red black tree, the rdtree is in the .h file and the same for the hash map
//the menu and the code for loading the data into the structures is found in menu.h
//we use the chrono to differientiate the times between loading the data and also retrieving a node in milliseconds and microseconds respectively

int main() {
    //set up the loop to stay on the menu unless exited, starts off with no data loaded and no data structure chosen, terminal input, initializing tree, Hashtable has an error currently so commented out
    bool exited = false;
    bool dsrb = true;
    bool loaded = false;
    int switches = 0;
    Student* selected_student = nullptr;
    int new_input = 0;
    RedBlack rbtree;
    HashTable<int, Student> hashtable(10000);

    //loop of the menu, takes an input and turns it to one of the options
    while(!exited) {
        DisplayMenu(dsrb, loaded, selected_student);
        string input;
        cin >> input;
        try{new_input = stoi(input);}
        catch(...){ cout << "Invalid Input\n" << endl; continue;}
        if (new_input < 0 || new_input > 14) {
            cout << "Invalid Option" << endl;
            continue;
        }
        switch(new_input) {
            // different menu options are in Menu.cpp
            case 0:
                exited = true;
                break;
            case 1:
                //switches protects it from reloading the data everytime you switch data structures
                if (switches < 2) {
                    LoadDataSet(hashtable, rbtree, "data/college_student_placement_dataset.csv", dsrb); //Menu.cpp
                }
                loaded = true;
                break;
                //searches for id in both data structures depending on which is toggled, tracks the time to location
            case 2: {
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                string search_id;
                int id;
                cout << "Enter ID:" << endl;
                cin >> search_id;
                try{id = stoi(search_id);}
                catch(...){ cout << "Invalid ID\n" << endl; continue;}
                if (dsrb) {
                    auto start = chrono::high_resolution_clock::now();
                    TreeNode* node = rbtree.search(to_string(id));
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    cout << "Student located in " << duration.count() << " microseconds" << endl << endl;
                    if (node) {
                        selected_student = &(node->student);
                    }
                    else {

                        cout << "Error: Student Not Found" << endl;
                        break;
                    }
                    cout << "Student " << id << " found" << endl;
                }
                else {
                    auto start = chrono::high_resolution_clock::now();
                    if (hashtable.if_contains(id)) {
                        selected_student = &(hashtable.get(id));
                        auto end = chrono::high_resolution_clock::now();
                        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                        cout << "Student located in " << duration.count() << " microseconds" << endl << endl;
                        cout << "Student " << id << " found" << endl;
                    }
                    else {
                        cout << "Error: Student " << "not " << " found" << endl;
                    }

                }
                break;
            }

                //cases 3 through 12 return individual student's statistics, the selected student object was searched through on the data structure of case 2, unless changed
            case 3:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Student IQ: " << selected_student->iq << endl;
                break;
            case 4:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Student Last Semester GPA: " << selected_student->prevgpa << endl;
                break;
            case 5:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Cumulative Student GPA: " << selected_student->gpa << endl;
                break;
            case 6:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Student Academic Performance: " << selected_student->perf << endl;
                break;
            case 7:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Student Extracurriculars: " << selected_student->ec << endl;
                break;
            case 8:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Student Communication Skills: " << selected_student->communication << endl;
                break;
            case 9:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Did Student have an Internship: " << (selected_student->intern ? "Yes" : "No") << endl;
                break;
            case 10:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Student Project Amount: " << selected_student->proj << endl;
                break;
            case 11:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Did Student Get a Job: " << (selected_student->job ? "Yes" : "No") << endl;
                break;
            case 12:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                if (selected_student == nullptr) {
                    cout << "Error: No Student Selected" << endl;
                    break;
                }
                cout << "Student's College ID: " << selected_student->collegeid << endl;
                break;

                //switches data structure, if you try to switch three times it wont reload anything
            case 13:
                switches += 1;
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                selected_student = nullptr;
                if (switches < 2) {
                    loaded = false;
                }
                dsrb = !dsrb;
                break;

        }
    }
}