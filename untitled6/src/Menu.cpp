//
// Created by ajohnson21 on 11/3/2025.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Menu.h"
#include "hash.h"
#include "red-black.h"
#include "Student.h"
using namespace std;



void DisplayMenu(bool dsrb, bool loaded, Student* selected_student) {
    cout << "=================================\n Job Placement Analysis System \n=================================" << endl;
    cout << "Active Data Structure: ";
    if (loaded) {
        if (dsrb) {
            cout << "Red-Black Tree" << endl;
        }
        else {
            cout << "Hash Map" << endl;
        }
    }
    else{ cout << "N/A" << endl; }
    cout << "Student Selected: ";
    if (selected_student!= nullptr) {
        cout << selected_student->id<< endl << endl;
    }
    else {
        cout << "N/A" << endl << endl;
    }

    cout << "Choose an option below:" << endl << endl;
    cout << "1. Load Placement Dataset" << endl;
    cout << "2. Select Student by ID(1-1000)" << endl; //this can also be select student
    cout << "3. Calculate Average IQ" << endl;
    cout << "4. Last Semester GPA" << endl;
    cout << "5. Cumulative GPA" << endl;
    cout << "6. Academic Performance(1-10)" << endl;
    cout << "7. EC Involvement(1-10)" << endl;
    cout << "8 Communication Skills(1-10)" << endl;
    cout << "9. {something to do with interships} either percentage of students landing one or like yes or no for this student" << endl;
    cout << "10. Projects Completed" << endl;
    cout << "11. Job Placement {Either Percent Placement or Individual Placement}" << endl;;
    cout << "12. Toggle Data Structure (RBT <-> Hash Map)" << endl;
    cout << "13. Job Placement Statistics" << endl;
    cout << "0. Exit\n" << endl;
}

void Setup() {

}

void LoadDataSet(HashTable<int, Student> hashtable, RedBlack& rbtree, const string& file, bool dsrb) { //, HashTable<string, int>& hashtable,
    ifstream fin(file);
    string line;
    getline(fin, line);

    while (getline(fin, line)) {
        stringstream ss(line);
        string collegeid, iq, prevgpa, gpa, performance, extra_curriculars, communication, intern, projects, job;
        getline(ss, collegeid, ',');
        getline(ss, iq, ',');
        getline(ss, prevgpa, ',');
        getline(ss, gpa, ',');
        getline(ss, performance, ',');
        getline(ss, extra_curriculars, ',');
        getline(ss, communication, ',');
        getline(ss, intern, ',');
        getline(ss, projects, ',');
        getline(ss, job, ',');
        const Student s(collegeid, iq, prevgpa, gpa, performance, extra_curriculars, communication, intern, projects, job);
        //cout << collegeid << ", " << iq << ", " << prevgpa << ", " << gpa << ", " << performance << ", " << extra_curriculars << ", " <<  communication << ", " << intern << ", " << projects << ", " << job << endl;
        if (!dsrb) {
            hashtable.insert(s.id, s);
        }
        else {
            rbtree.insert(s);
        }
    }
}