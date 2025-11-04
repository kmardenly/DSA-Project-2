#include <fstream>
#include <iostream>
#include "Menu.h"
//#include "hash.h"
#include "red-black.h"
using namespace std;





int main(){
    //setup the loop to stay on the menu unless exited, starts off with no data loaded and no data structure chosen, terminal input, initializing tree, Hashtable has an error currently so commented out
    bool exited = false;
    bool dsrb = false;
    bool loaded = false;
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
                cout;
                break;
            case 2:
                cout;
                break;
            case 3:
                cout;
                break;
            case 4:
                cout;
                break;
            case 5:
                cout;
                break;
            case 6:
                cout;
                break;
            case 7:
                cout;
                break;
            case 8:
                cout;
                break;
            case 9:
                cout;
                break;
            case 10:
                cout;
                break;
            case 11:
                cout;
                break;
            case 12:
                dsrb = false;
                break;
        }
    }

}
