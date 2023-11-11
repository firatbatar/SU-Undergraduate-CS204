#include <iostream>

struct A {
    int i;
    A(int i) : i(i) {}
    ~A() { std::cout << "~a" << i << std::endl; }
};

// TODO: What is the output of the following program?
// Can you find without running it?
int main() {
    A a1(1);
    A *p;

    {  // nested scope
        std::cout << "in brackets " << std::endl;
        A a2(2);
        p = new A(3);
    }  // a2 out of scope
    std::cout << "out brackets " << std::endl;

    std::cout << "deleting p " << std::endl;
    delete p;  // calls the destructor of a3
    std::cout << "deleted " << std::endl;
}
