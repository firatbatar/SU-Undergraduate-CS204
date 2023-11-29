#include <string>
#include <vector>
using namespace std;

template <typename T1, typename T2>
class myVector {
   private:
    struct KeyValuePair {
        T1 value;
        T2 key;

        KeyValuePair(T1 v, T2 k) : value(v), key(k){};
    };

    string name;
    vector<KeyValuePair> nodes;

    friend class Iterator;

   public:
    class Iterator {
       public:
        Iterator() {}

        Iterator(typename vector<KeyValuePair>::iterator it_p) : it(it_p) {}

        bool find(T2 oldKey, myVector<T1, T2> &v) {}

        void replaceKey(T2 newKey) {}

        void printVector() {}

       private:
        typename vector<KeyValuePair>::iterator it;
    };

    // Default constructor
    myVector() {}

    void setName(string nm) { name = nm; }
    string getName() { return name; }

    void push_back(T1 value, T2 key) {
        KeyValuePair new_node(value, key);
        nodes.push_back(new_node);
    }

    void remove(T2 key) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].key == key) {
                nodes.erase(nodes.begin() + i);
                return;
            }
        }
    }

    T1 *operator[](T2 key) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].key == key) {
                return &nodes[i].value;
            }
        }

        return nullptr;
    }

    typename vector<KeyValuePair>::iterator begin() { return nodes.begin(); }

    bool isEmpty() {}

    bool operator==(myVector<T1, T2> &v) {}

    void process_data() {}
};
