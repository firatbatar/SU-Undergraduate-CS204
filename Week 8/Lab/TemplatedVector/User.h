/* Author: Zeynep Dogmus
 * Date: April 2013
 * Templated Vector Example
 */
#ifndef USER_H_
#define USER_H_
using namespace std;
template <class itemType>
class User {
   public:
    User();
    User(MyVector<itemType> &vec, string n) : sharedVector(vec), userName(n){};

    // Adds the given vector to the shared vector
    void add(itemType value) { sharedVector.increaseElements(value); }

    // Displays the elements of the shared vector
    void displayVector() { sharedVector.display(); }

   private:
    // TODO: what is wrong with the shared object definition below
    // Fix it by considering object sharing logic.
    MyVector<itemType> &sharedVector;  // shared object
    string userName;
};

#endif
