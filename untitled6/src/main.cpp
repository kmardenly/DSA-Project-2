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
    bool delete_rb = false;
    bool delete_hashtable = false;
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
                if (dsrb && delete_rb) {
                    RedBlack rbtree;
                    delete_rb = false;
                }
                if (!dsrb && delete_hashtable) {
                    HashTable<int, Student> hashtable(10000);
                    delete_rb = true;
                }
                LoadDataSet(hashtable, rbtree, "data/college_student_placement_dataset.csv", dsrb); // hashtree,
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
                cout << "Did Student have an Internship: " << selected_student->intern << endl;
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
                cout << "Did Student Get a Job: " << selected_student->job << endl;
                break;
            case 12:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                    if (dsrb) {
                        selected_student = nullptr;
                        rbtree.~RedBlack();
                        delete_rb = true;
                    }
                    else {
                        selected_student = nullptr;
                        hashtable.~HashTable();
                        delete_hashtable = true;
                    }

                dsrb = !dsrb;
                break;
            case 13:
                if (!loaded) {
                    cout << "Error: Load Data First" << endl;
                    break;
                }
                float IQ, prevgpa, cgpa, perf, ec, comm, proj, job, internship;
                for (int id = 0; id<10000; id++) {
                    if (dsrb) {
                        TreeNode* node = rbtree.search(to_string(id));
                        selected_student = &(node->student);
                    }
                    else {
                        selected_student = &(hashtable.get(id));
                    }
                    IQ += selected_student->iq;
                    prevgpa += selected_student->prevgpa;
                    cgpa += selected_student->gpa;
                    perf += selected_student->perf;
                    ec += selected_student->ec;
                    comm += selected_student->communication;
                    proj += selected_student->proj;
                    if (selected_student->job == true) {
                        job += 1;
                    }
                    if (selected_student->intern == true) {
                        internship += 1;
                    }
                }
                cout << "Average IQ: " << (IQ/10000) << endl;
                cout << "Average Previous Semester GPA: " << (prevgpa/10000) << endl;
                cout << "Average GPA: " << cgpa << endl;
                cout << "Average Academic Performance: " << (perf/10000) << endl;
                cout << "Average Extracurricular Amount: " << (ec/10000) << endl;
                cout << "Average Communication Skills: " << (comm/10000) << endl;
                cout << "Percent with Internship: " << (internship/10000) << endl;
                cout << "Percent Landing a Job: " << (job/10000) << endl;
        }

    }
}