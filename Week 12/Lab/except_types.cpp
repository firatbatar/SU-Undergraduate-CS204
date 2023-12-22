#include <iostream>
#include <vector>
#include <exception>

using namespace std;

int main() {
    try {
        throw 5;  // TODO: try with '5', 5.0, 5.0f, (short)5, 5u, 5l, 5ll, 5ul, 5
    } catch (char c) {
        cout << "char caught " << endl;
    } catch (double d) {
        cout << "double caught " << endl;
    } catch (float f) {
        cout << "float caught " << endl;
    } catch (short int si) {
        cout << "short caught " << endl;
    } catch (unsigned int i) {
        cout << "unsigned int caught " << endl;
    } catch (long i) {
        cout << "long caught " << endl;
    } catch (long long i) {
        cout << "long long caught " << endl;
    } catch (unsigned long i) {
        cout << "unsigned long caught " << endl;
    } catch (int i) {
        cout << "int caught " << endl;
    }

    try {
        cout << "Creating a vector of size 5... \n";
        vector<int> v(5);
        cout << "Accessing the 11th element of the vector...\n";
        cout << v.at(11) << endl;
    } catch (exception &e) {
        cout << " a standard exception was caught, with message '" << e.what() << "'\n";
    }

    return 0;
}
