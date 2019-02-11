
#include <iostream>
#include <string>
#include "Cell.h"
using namespace std;
int main(int count, char *args[]) {
    auto start = high_resolution_clock::now(); 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start);
    cout <<endl<< "Running time in microseconds: "<<duration.count() << endl;
    return 0;
}