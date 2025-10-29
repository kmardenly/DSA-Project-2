#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream file("data/graduates.csv");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    return 0;
}