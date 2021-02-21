#include <iostream>
#include "Storerecord.h"
#include <cstring>
using namespace std;

int main() {
    string line;
    initialize();
    while(getline(cin,line)){
        try {
            run_program(line);
        } catch (...) {
            printf("Invalid\n");
        }
    }
}
