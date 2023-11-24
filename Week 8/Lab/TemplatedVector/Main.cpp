/* Author: Zeynep Dogmus
 * Date: April 2013
 * Templated Vector Example
 */
#include <iostream>
#include <string>
#include "MyVector.h"
#include "User.h"

using namespace std;

int main() {
    // String example

    MyVector<string> myStringVector(4, "Apple");
    User<string> user1(myStringVector, "Ali");
    User<string> user2(myStringVector, "Veli");

    myStringVector.display();
    user1.displayVector();
    user2.displayVector();

    user2.add("Orange");
    cout << "After adding orange" << endl << endl;
    myStringVector.display();
    user1.displayVector();
    user2.displayVector();

    myStringVector.increaseElements("Cherry");
    cout << "After adding cherry" << endl << endl;
    myStringVector.display();
    user1.displayVector();
    user2.displayVector();

    cout << "*****************************************************" << endl << endl;

    // Integer example

    MyVector<int> myIntVector(5, 10);
    User<int> user3(myIntVector, "Ayse");
    User<int> user4(myIntVector, "Fatma");

    myIntVector.display();
    user3.displayVector();
    user4.displayVector();

    myIntVector.increaseElements(5);
    cout << "After adding 5" << endl << endl;
    myIntVector.display();
    user3.displayVector();
    user4.displayVector();

    user4.add(300);
    cout << "After adding 300" << endl << endl;
    myIntVector.display();
    user3.displayVector();
    user4.displayVector();

    return 0;
}
