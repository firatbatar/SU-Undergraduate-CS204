#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <typename TV, typename TK>
struct KeyValPairStruct {
    TV value;
    TK key;

    KeyValPairStruct(TV v, TK k) : value(v), key(k){};
};

template <typename T1, typename T2>
class myVector {
   private:
    typedef KeyValPairStruct<T1, T2> keyValPair;

    string name;
    vector<keyValPair> nodes;

    friend class Iterator;

   public:
    class Iterator {
       public:
        Iterator() {}

        Iterator(vector<keyValPair> *it_p) : it(it_p) {}

        bool find(T2 oldKey, myVector<T1, T2> &v) {
            typename vector<keyValPair>::iterator iter = (*it).begin();
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
            typename vector<keyValPair>::iterator iter = (*it).begin();
            for (; iter != (*it).end(); iter++) {
                cout << "Value: " << iter->value << ", Key: " << iter->key << endl;
            }
        }

       private:
        vector<keyValPair> *it;
        typename vector<keyValPair>::iterator itr;
    };

    // Default constructor
    myVector() {}

    // Copy constructor
    myVector(const myVector &v) : name(v.name), nodes(v.nodes) {}

    // Getter for nodes
    const vector<keyValPair> &getNodes() const { return nodes; }

    void setName(string nm) { name = nm; }
    string getName() { return name; }

    void push_back(T1 value, T2 key) {
        keyValPair new_node(value, key);
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

    vector<keyValPair> *begin() { return &nodes; }

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

    void process_data() {
        // Chek if value type is string
        if constexpr (is_same<T1, string>::value) {
            // Combine all values into one string
            string combined = "";
            for (int i = 0; i < nodes.size(); i++) {
                combined += " " + nodes[i].value;
            }

            // Find most frequent character
            vector<int> char_counts(256, 0);
            for (int i = 0; i < combined.length(); i++) {
                char_counts[(char)combined[i]]++;
            }
            char mostFrequentChar = 0;
            for (int i = 0; i < char_counts.size(); i++) {
                if (char_counts[i] > char_counts[mostFrequentChar]) {
                    mostFrequentChar = i;
                }
            }

            // Find most frequent word
            istringstream wordStream(combined);
            string word;
            myVector<int, string> wordCounts;

            while (wordStream >> word) {
                if (wordCounts[word] == nullptr) {
                    wordCounts.push_back(1, word);
                }
                else {
                    (*wordCounts[word])++;
                }
            }

            const vector<KeyValPairStruct<int, string>> &wordCountsNodes = wordCounts.getNodes();
            string mostFrequentWord = wordCountsNodes[0].key;
            for (int i = 0; i < wordCountsNodes.size(); i++) {
                if (wordCountsNodes[i].value > *wordCounts[mostFrequentWord]) {
                    mostFrequentWord = wordCountsNodes[i].key;
                }
            }

            // Print results
            cout << "Most frequent character: '" << mostFrequentChar << "' (Frequency: " << char_counts[mostFrequentChar] << ")" << endl;
            cout << "Most frequent word: \"" << mostFrequentWord << "\" (Frequency: " << *wordCounts[mostFrequentWord] << ")" << endl;
        }

        // Chek if value type is arithmetic
        if constexpr (is_arithmetic<T1>::value) {
            // Find  mean, median, standard deviation, max and mode
            vector<T1> values;
            T1 sum = 0;

            // Add all values to vector as sorted
            for (int i = 0; i < nodes.size(); i++) {
                T1 value = nodes[i].value;
                bool inserted = false;
                for (int j = 0; j < values.size(); j++) {
                    if (value < values[j]) {
                        values.insert(values.begin() + j, value);
                        inserted = true;
                        break;
                    }
                }
                if (!inserted) values.push_back(value);

                sum += value;  // Calculate sum at the same time
            }

            // Mean
            double mean = (double)sum / (double)values.size();

            // Median
            double median;
            if (values.size() % 2 == 0) {
                median = (values[values.size() / 2 - 1] + values[values.size() / 2]) / 2.0;
            }
            else {
                median = values[(values.size() - 1) / 2];
            }

            // Standard deviation
            double std_dev = 0;
            for (int i = 0; i < values.size(); i++) {
                std_dev += pow(values[i] - mean, 2);
            }
            std_dev = pow(std_dev / values.size(), 0.5);

            // Max
            T1 max = values[values.size() - 1];

            // Mode
            T1 mode = values[0];
            int mode_count = 1;
            T1 current = values[0];
            int current_count = 1;
            for (int i = 1; i < values.size(); i++) {
                if (values[i] == current) {
                    current_count++;
                }
                else {
                    if (current_count > mode_count) {
                        mode = values[i - 1];
                        mode_count = current_count;
                    }
                    current = values[i];
                    current_count = 1;
                }
            }

            // Print results
            cout << "Mean: " << mean << endl;
            cout << "Median: " << median << endl;
            cout << "Standard deviation: " << std_dev << endl;
            cout << "Max: " << max << endl;
            cout << "Mode: " << mode << endl;
        }
    }
};