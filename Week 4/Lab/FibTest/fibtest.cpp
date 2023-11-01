#include <iostream>
#include <vector>

#include "ctimer.h"
#include "prompt.h"
#include "stdlib.h"

using namespace std;

// Illustrates "bad" recursion for computing Fibonacci numbers
// also illustrates how to fix this efficiency problem

// Recursive
int RecFib(int n)
// precondition: 0 <= n
// postcondition: returns the n-th Fibonacci number
{
    // TODO: Implement this simple RECURSIVE function (no memoization is allowed - so function can be expensive)
    if (n == 0 || n == 1) {
        return 1;
    }

    return RecFib(n - 1) + RecFib(n - 2);
}

// TODO: Fix this. There is something missing here (one word).
int RecFibFixed(int n)
// precondition: 0 <= n <= 30
// postcondition: returns the n-th Fibonacci number
{
    static vector<int> mem(31, 0);

    if (mem[n] != 0) {
        return mem[n];
    }

    if (n == 0 || n == 1) {
        mem[0] = 1;
        mem[1] = 1;
        return 1;
    }

    int val = RecFibFixed(n - 1) + RecFibFixed(n - 2);
    mem[n] = val;
    return val;
}

// iterative
int Fib(int n)
// precondition: 0 <= n
// postcondition: returns the n-th Fibonacci number
{
    int first = 1, second = 1, temp;
    int k;
    for (k = 0; k < n; k++) {
        temp = first;
        first = second;
        second = temp + second;
    }
    return first;
}

// TODO: Observe how the execution time grows when the number increases with expensive and cheap recursive
// implementations
int main() {
    CTimer btimer, rtimer, itimer;
    int j;
    int k;
    int ival, rval, bval;
    int iters = PromptRange("enter # of iterations", 1, 1000000);
    int limit = PromptRange("how many Fibonacci numbes to be calculated?", 1, 30);

    for (k = 0; k < iters; k++) {
        for (j = 0; j <= limit; j++) {
            btimer.Start();
            bval = RecFibFixed(j);
            btimer.Stop();
            rtimer.Start();
            rval = RecFib(j);
            rtimer.Stop();
            itimer.Start();
            ival = Fib(j);
            itimer.Stop();
        }
    }

    cout << iters << " good/fixed recursive trials " << btimer.CumulativeTime() << endl;
    cout << iters << " bad recursive trials " << rtimer.CumulativeTime() << endl;
    cout << iters << " iterative trials " << itimer.CumulativeTime() << endl;
    return 0;
}
