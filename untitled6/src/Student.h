//
// Created by ajohnson21 on 11/4/2025.
//
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <fstream>
#include "Menu.h"
// "hash.h"
#include "red-black.h"
using namespace std;

#ifndef STUDENT_H
#define STUDENT_H

//safely stores data items from the csv file
static int safe_stoi(const string& s, int defaultValue = 0) {
    try {
        return stoi(s);
    } catch (...) {
        return defaultValue;
    }
}

static float safe_stof(const string& s, float defaultValue = 0.0f) {
    try {
        return stof(s);
    } catch (...) {
        return defaultValue;
    }
}


//student class that acts as the node in both data structures
 struct Student {
     int id;
     static int id_tracker;
     string collegeid;
     int iq;
     float prevgpa;
     float gpa;
     int perf;
     int ec;
     int communication;
     bool intern;
     int proj;
     bool job;
    Student(string scollegeid, string siq, string sprevgpa, string sgpa, string sperf, string sec, string scommunication, string sintern, string sproj, string sjob) {
        id = id_tracker++;
        collegeid = scollegeid;
        iq = safe_stoi(siq);
        prevgpa = safe_stof(sprevgpa);
        gpa = safe_stof(sgpa);
        perf = safe_stoi(sperf);
        ec = safe_stoi(sec);
        communication = safe_stoi(scommunication);
        if (sintern == "No"){intern = false;} else {intern = true;}
        proj = safe_stoi(sproj);
        if (sjob == "No"){job = false;} else {job = true;}
    }
};

struct Major { //holds all of the information relevant to the major
    string year;
    int num_degrees;
    string name;
    float highSalary;
    float lowSalary;
    float avgSalary;
    string popularEmployerType;
    string popularReasonNotInField;
    string popularReasonNotWorking;
    string popularWorkActivity;
    float employedRate;
    float unemployRate;
    int unisWithMajor;

    Major(string a, int b, string w, float c, float d, float x, string e, string f, string g, string h, float i, float y, int z ) :
      year(a), num_degrees(b), name (w), highSalary(c), lowSalary(d), avgSalary(x), popularEmployerType(e),
      popularReasonNotInField(f), popularReasonNotWorking(g), popularWorkActivity(h), employedRate(i), unemployRate(y), unisWithMajor(z) {}
public:
    string getName() {
        return name;
    }
};

//a new helper function for input validation
//this is pulled verbatim from my (keira) avl project
static bool isAllDigits(const string& s) {
    if (s.empty()) return false;
    for (unsigned char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}
#endif //STUDENT_H

