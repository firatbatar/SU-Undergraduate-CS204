/* Author: Zeynep Dogmus
 * Date: April 2013
 * Templated Vector Example
 */
#ifndef MYVECTOR_H_
#define MYVECTOR_H_

template <class itemType>
class MyVector {
   public:
    MyVector();
    MyVector(int, itemType);
    ~MyVector();

    void display();
    void increaseElements(itemType);

   private:
    itemType *myVector;
    int size;
};

// TODO: Do you need to include something?
// Please think a little bit and understand why...
#include "MyVector.cpp"
#endif
