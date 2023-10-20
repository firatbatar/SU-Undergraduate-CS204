/*****************************************************
 *
 * This program demonstrates different ways of passing
 * pointers to functions and their effects.
 * Author: Albert Levi
 * Date: March 6, 2012
 *
 *****************************************************/

#include <iostream>
#include <string>
using namespace std;

// TODO: please fill in the types of the variables
// dp is a double pointer
// ip is an integer pointer
// sp is a string pointer
// irp is a reference variable, integer pointer
void dothis(double* dp, int* ip, string* sp, int*& irp) {
    cout << "dothis begin: " << *dp << " " << ip[0] << " " << ip[1] << " " << *sp << " " << *irp << endl << endl;
    dp = new double;
    *dp = 5.4;

    ip[0] = 100;
    *sp = *sp + " is easy";

    irp = new int;
    *irp = 200;
    cout << "dothis end: " << *dp << " " << ip[0] << " " << ip[1] << " " << *sp << " " << *irp << endl << endl;
}

int main() {
    string s = "CS204";
    double* dptr = new double;
    int* iptr1 = new int[2];
    int* iptr2 = new int;
    int* iptr3 = iptr2;

    *dptr = 3.14;
    iptr1[0] = 10;
    iptr1[1] = 20;
    *iptr2 = 2;
    dothis(dptr, iptr1, &s, iptr2);
    cout << "main end: " << *dptr << " " << iptr1[0] << " " << iptr1[1] << " " << s << " " << *iptr2 << " " << *iptr3
         << endl
         << endl;

    delete dptr;
    delete[] iptr1;
    delete iptr2;
    // TODO: answer this: are there any dynamic memory locations allocated but not deleted? If so which one
    // The function dothis allocates two new dynamic memory locations but dp is not deleted
    // irp is deleted since it's a reference parameter

    // system("pause");
    return 0;
}
