//
// Created by AriannaA on 10/28/2025.
//

#ifndef MAJOR_H
#define MAJOR_H
#include <iostream>
using namespace std;


class Major {
  private:
    //attributes for each major from dataset
    string name;
    int high_salary;
    int low_salary;
    int mean_salary;
    int num_employed;
    int num_unemployed;
    string work_activity;
    string reason_not_working;
    string employer_type;
    //for linked list in hash table
    Major* next;
    //for red-black tree
    Major* left;
    Major* right;
    Major* parent;
    bool color;
  public:
    Major(string n, int h, int l, int m, int e, int un, string w, string r, string t)
      : name(n), high_salary(h), low_salary(l), mean_salary(m), num_employed(e), num_unemployed(un),
        work_activity(w), reason_not_working(r), employer_type(t), next(nullptr), left(nullptr), right(nullptr),
        parent(nullptr), color(false) {}
    string get_name() {
      return name;
    }
    int get_high_salary() {
      return high_salary;
    }
    int get_low_salary() {
      return low_salary;
    }
    int get_mean_salary() {
      return mean_salary;
    }
    int get_num_employed() {
      return num_employed;
    }
    int get_num_unemployed() {
      return num_unemployed;
    }
    string get_work_activity() {
      return work_activity;
    }
    string get_reason_not_working() {
      return reason_not_working;
    }
    string get_employer_type() {
      return employer_type;
    }

};



#endif //MAJOR_H
