#include <string>
#include <vector>
using namespace std;

template <typename T1, typename T2>
class myVector {
   public:
    class Iterator {
       public:
        Iterator(){};

        Iterator(typename vector<T1>::iterator it_p) : it(it_p){};

        bool find(T2 oldKey, myVector<T1, T2> &v){};

        void replaceKey(T2 newKey){};

        void printVector(){};

       private:
        typename vector<T1>::iterator it;
    };

    // Default constructor
    myVector(){};

    void setName(string nm) { name = nm; }
    string getName() { return name; }

    void push_back(T1 value, T2 key) {
        values.push_back(value);
        keys.push_back(key);
    };

    void remove(T2 key) {
        for (int i = 0; i < keys.size(); i++) {
            if (keys[i] == key) {
                keys.erase(keys.begin() + i);
                values.erase(values.begin() + i);
            }
        }
    }

    T1 *operator[](T2 key) {
        for (int i = 0; i < keys.size(); i++) {
            if (keys[i] == key) {
                return &values[i];
            }
        }

        return nullptr;
    }

    typename vector<T1>::iterator begin() { return values.begin(); }

    bool isEmpty(){};

    bool operator==(myVector<T1, T2> &v){};

    void process_data(){};

   private:
    string name;
    vector<T1> values;
    vector<T2> keys;
};
