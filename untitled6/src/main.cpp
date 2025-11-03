#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream file("data/graduates.csv");
    if (!file.is_open()) {
        cout << "Error file opening file" << endl;
        return 1;
    }
    ifstream file1("data/college_student_placement_dataset.csv");
    if (!file1.is_open()) {
        cout << "Error file1 opening file" << endl;
        return 1;
    }
    return 0;
}