#include <iostream>
#include <string>
using namespace std;

// This is the behaviour of the throw standalone statement in the standard (i.e., "throw;")
//[C++11: 15.1/8]: A throw-expression with no operand rethrows the currently handled exception (15.3).
// The exception is reactivated with the existing temporary; no new temporary exception object is created. [..]

// MAIN TODO: the desired output is

/*Exception++ 1 is constructed (out of 1)
DerivedException obj is constructed
foo1 catches
test derived
foo catches
test derived
main catches
test derived
DerivedException obj is destructed
Exception-- 1 is deleted (0 remains)*/

// That is we want an object is thrown at some point and caught in the main function without any temporary object created

class ExceptionCounter {
   public:
    ExceptionCounter() {
        exceptionId = ++noExceptions;
        cout << "Exception++ " << exceptionId << " is constructed (out of " << noExceptions << ")" << endl;
    }

    ExceptionCounter(const ExceptionCounter &e) {
        exceptionId = ++noExceptions;
        cout << "Exception++ " << exceptionId << " is copy constructed (out of " << noExceptions << ")" << endl;
    }

    virtual ~ExceptionCounter() {
        --noExceptions;
        cout << "Exception-- " << exceptionId << " is deleted (" << noExceptions << " remains)" << endl;
    }

    virtual void test() { cout << "test base" << endl; }

   private:
    static int noExceptions;
    int exceptionId;
};
int ExceptionCounter::noExceptions = 0;

class DerivedException : public ExceptionCounter {
   public:
    DerivedException() : ExceptionCounter() { cout << "DerivedException obj is constructed" << endl; }

    DerivedException(const DerivedException &e) : ExceptionCounter() { cout << "Derivedxxception obj is copy constructed" << endl; }

    ~DerivedException() { cout << "DerivedException obj is destructed" << endl; }

    void test() { cout << "test derived" << endl; }
};

void foo2() {
    throw DerivedException();  // Level 0 throw: we want to keep the type of the exception as derived
                               // remember polymorphism.
}

void foo1() {
    try {
        foo2();
    } catch (ExceptionCounter &e) {  // TODO: Do we have a problem here?
        cout << "foo1 catches" << endl;
        e.test();
        throw;  // rethrow, remember what happens when we throw an exception (copy construction)
                  // remember what is slicing and what it was doing. now read the behaviour of "throw" above.
                  // TODO: see the output and observe that we cant keep the type as derived.
                  //       how can we fix this and keep the type derived?
    }
}

void foo() {
    try {
        foo1();
    } catch (ExceptionCounter &e) {
        cout << "foo catches" << endl;
        e.test();
        throw;  // rethrow
    }
}

int main(void) {
    try {
        foo();
    } catch (ExceptionCounter &e) {
        cout << "main catches" << endl;
        e.test();
    }
    return 1;
}
