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

 struct Student {
     int id;
     int id_tracker = 1;
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
        id = id_tracker;
        id_tracker += 1;
        collegeid = scollegeid;
        iq = stoi(siq);
        prevgpa = stof(sprevgpa);
        gpa = stof(sgpa);
        perf = stoi(sperf);
        ec = stoi(sec);
        communication = stoi(scommunication);
        if (sintern == "No"){intern = false;} else {intern = true;}
        proj = stoi(sproj);
        if (sjob == "No"){job = false;} else {job = true;}




    }
};
#endif //STUDENT_H
