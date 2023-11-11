class A {
   public:
    int x;
    A(int x = 1) : x(x) {}
};

class B {
   public:
    A a;
};

class C {
   public:
    A a;
    C(int y) : a(y) {}
};

class D {
   public:
    A a;
    D(int y) : a(y) {}

    // We did not learn the following "default" keyword in the lecture.
    // explicitly-defaulted function definition: as an explicit instruction
    // to the compiler to generate special member function for a class. (since C++11)
    D() = default;  // C++11, explicitly defaulted, calls A::A()
};

class E {
   public:
    int &ref;  // reference member
};

class F {
   public:
    const int c;  // const member
};

class G {
   public:
    const int c = 2;  // const member - this works with C++11
};

class H {
   public:
    // We did not learn the following "default" keyword in the lecture.
    // With this "delete" keyword (which is different than the delete we use)
    // the compiler is told not to create a default constuctor
    H() = delete;  // explicitly deleted default constructor, C++11
};

class I {
   public:
    I(int a = 1) {}
    I() {}
};

class J {
   public:
    H h;
};

int main() {
    A a;
    B b;
    C c;
    D d;
    E e;
    F f;
    G g;
    H h;
    I i;
    J j;
