#include <iostream>
using namespace std;

int main() {
    // Define the array
    int arr[] = {4, 7, 2, 8, 5, 3};  // the elements can be arbitrary
    int size = sizeof(arr) / sizeof(arr[0]);

    // Initial assumption: the first element is the maximum
    int* addrOfTheMax = &arr[0];

    // Iterate through the array to find the index of the maximum element
    for (int i = 1; i < size; i++) {
        if (arr[i] > *addrOfTheMax) {
            // addrOfTheMax = &arr[i];
            addrOfTheMax = arr + i;  // Move the pointer to ith element
        }
    }

    // Print the address of the maximum element
    cout << "Address of the maximum element: " << addrOfTheMax << endl;

    return 0;
}
