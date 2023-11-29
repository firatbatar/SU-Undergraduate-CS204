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

        Iterator(vector<KeyValuePair> *it_p) : it(it_p) {}

        bool find(T2 oldKey, myVector<T1, T2> &v) {
            typename vector<KeyValuePair>::iterator iter = (*it).begin();
            for (; iter != (*it).end(); iter++) {
                if (iter->key == oldKey) {
                    itr = iter;
                    return true;
                }
            }

            return false;
        }

        void replaceKey(T2 newKey) { itr->key = newKey; }

        void printVector() {
            typename vector<KeyValuePair>::iterator iter = (*it).begin();
            for (; iter != (*it).end(); iter++) {
                cout << "Value: " << iter->value << ", Key: " << iter->key << endl;
            }
        }

       private:
        vector<KeyValuePair> *it;
        typename vector<KeyValuePair>::iterator itr;
    };

    // Default constructor
    myVector() {}

    // Copy constructor
    myVector(const myVector &v) : name(v.name), nodes(v.nodes) {}

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

    myVector<T1, T2> &operator=(myVector<T1, T2> &v) {
        name = v.name;
        nodes = v.nodes;
        return *this;
    }

    vector<KeyValuePair> *begin() { return &nodes; }

    bool isEmpty() { return nodes.size() == 0; }

    bool operator==(myVector<T1, T2> &v) {
        if (nodes.size() != v.nodes.size()) {
            return false;
        }

        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].value != v.nodes[i].value || nodes[i].key != v.nodes[i].key) {
                return false;
            }
        }

        return true;
    }

    void process_data() {}
};
