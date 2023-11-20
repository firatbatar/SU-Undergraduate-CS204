/*
CS204 Fall 2023-2024 HW#4
Fırat Batar - 31125
*/

#include <iostream>
using namespace std;

class LinkedListSet {
   private:
    struct Node {
        int val;
        Node *next;
        Node(int vl = 0, Node *nt = nullptr) : val(vl), next(nt) {}
    };

    Node *head;

    // A general ordered instertion function
    void insertOrdered(int val) {
        if (!head) {
            head = new Node(val);  // If the set is empty, head is the new node pointing to nullptr
            return;
        }

        Node *currentNode = head;
        Node *prevNode = nullptr;
        // Find the place for the ordered insterion
        // Between prevNode and currentNode
        while (currentNode && currentNode->val < val) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        if (currentNode && currentNode->val == val) return;  // No doubles in the set

        Node *newNode = new Node(val, currentNode);  // New node is inserted before currentNode, so it points to it
        if (prevNode) {
            prevNode->next = newNode;  // prevNode points to newNode
        }
        else {
            // If it's being added to the front
            head = newNode;
        }
    }

    // A general removal function
    void remove(int val) {
        Node *currentNode = head;
        Node *prevNode = nullptr;
        while (currentNode) {
            if (currentNode->val == val) {
                if (prevNode) {
                    prevNode->next = currentNode->next;  // preNode points to removed's next
                }
                else {
                    head = currentNode->next;  // If prev doesn't exist then first node is removed
                }
                delete currentNode;
                return;
            }

            prevNode = currentNode;
            currentNode = currentNode->next;
        }
    }

    // Deep copy constructor
    LinkedListSet(const LinkedListSet &copy) {
        head = nullptr;  // Initial value must be nullptr for rest to work

        Node *currentNodeToCopy = copy.head;  // Copied node from the copy
        Node *lastAddedNode;                  // Keep the tail

        while (currentNodeToCopy) {
            if (!head) {
                head = new Node(currentNodeToCopy->val);
                lastAddedNode = head;
            }
            else {
                lastAddedNode->next = new Node(currentNodeToCopy->val);
                lastAddedNode = lastAddedNode->next;
            }
            currentNodeToCopy = currentNodeToCopy->next;
        }
    }

   public:
    // Default constructor
    LinkedListSet() { head = nullptr; }
    // Deconstructor
    ~LinkedListSet() {
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void display() {
        if (!head) return;

        cout << "LinkedListSet{";

        Node *currentNode = head;
        while (currentNode) {
            cout << currentNode->val << ", ";
            currentNode = currentNode->next;
        }

        cout << "}" << endl;
    }

    LinkedListSet &operator+(int rhs) {
        insertOrdered(rhs);
        return *this;  // Return itself for multiple additions
    }

    LinkedListSet &operator-(int rhs) {
        remove(rhs);
        return *this;  // Return itself for multiple removal
    }

    const LinkedListSet &operator+=(const LinkedListSet &rhs) {
        Node *currentNode = rhs.head;
        while (currentNode) {  // Add every element from rhs to lhs
                               // insertOrdered will automatically filter doubles and add elements sorted
            int valToAdd = currentNode->val;
            insertOrdered(valToAdd);
            currentNode = currentNode->next;
        }

        return *this;  // Return itself for multiple additions
    }

    const LinkedListSet &operator-=(const LinkedListSet &rhs) {
        Node *currentNode = rhs.head;
        while (currentNode) {  // Remove every element of rhs from lhs
                               // remove will automically filter non-existing values
            int valToAdd = currentNode->val;
            remove(valToAdd);
            currentNode = currentNode->next;
        }

        return *this;
    }

    const LinkedListSet &operator&=(const LinkedListSet &rhs) {
        // Intersection also can be expressed as A \ (A \ B)

        LinkedListSet lhsCopy(*this);  // Copy lhs (say lhs') to not change the original
        lhsCopy -= rhs;                // lhs' \ rhs
        *this -= lhsCopy;              // lhs \ (lhs' \ rhs) = lhs & rhs

        return *this;
    }
};

int main() {
    // Example usage
    LinkedListSet set1;

    set1 + 1 + 2 + 3 + 17;  // Insertion
    set1.display();

    set1 - 2;  // Deletion
    set1.display();

    LinkedListSet set2;
    set2 + 3 + 4 + 5;
    set2.display();

    set2 += set1 + 7 + 3 + 19;  // Insertion with multiple right-hand values
    set2.display();

    LinkedListSet set3;
    set3 + 3 + 4 + 7 + 17 + 41;
    set3.display();

    LinkedListSet set4;
    set4 + 41 + 37 + 7 + 19 + 41;
    set4.display();

    // Set Union
    set1 += set2;
    set1.display();

    // Set Difference
    set1 -= set3;
    set1.display();

    // Set Intersection
    set1 &= set4;
    set1.display();

    return 0;
}
