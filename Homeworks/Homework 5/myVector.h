#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <typename T_Value, typename T_Key>
struct KeyValPairStruct {
    // Struct for key-value pairs
    T_Value value;
    T_Key key;

    KeyValPairStruct(T_Value v, T_Key k) : value(v), key(k) {}
};

template <typename T1, typename T2>
class myVector {
   private:
    typedef KeyValPairStruct<T1, T2> keyValPair;  // Typedef Struct with given types for easier use

    string name;               // Name of the vector
    vector<keyValPair> nodes;  // Vector of key-value pairs

    friend class Iterator;  // Iterator class can access private members of myVector

   public:
    class Iterator {
       public:
        Iterator() {}  // Default constructor

        Iterator(vector<keyValPair> *p) : vec_p(p) {}  // Constructor with pointer to vector

        bool find(T2 oldKey, myVector<T1, T2> &v) {
            typename vector<keyValPair>::iterator iter = (*vec_p).begin();  // Reset iterator to beginning of vector
            for (; iter != (*vec_p).end(); iter++) {
                // If key is found, set iterator to that position and return true
                if (iter->key == oldKey) {
                    itr = iter;
                    return true;
                }
            }

            return false;
        }

        void replaceKey(T2 newKey) {
            // itr is setted to the found position in find() function
            // So we can just change the key of the node
            itr->key = newKey;
        }

        void printVector() {
            typename vector<keyValPair>::iterator iter = (*vec_p).begin();  // Reset iterator to beginning of vector
            for (; iter != (*vec_p).end(); iter++) {
                // Print value and key of each node
                cout << "Value: " << iter->value << ", Key: " << iter->key << endl;
            }
        }

       private:
        vector<keyValPair> *vec_p;                  // Pointer to vector
        typename vector<keyValPair>::iterator itr;  // Iterator to change key of node
    };

    // Default constructor
    myVector() {}

    // Copy constructor
    myVector(const myVector &v) : name(v.name), nodes(v.nodes) {}

    // Getter for nodes
    const vector<keyValPair> &getNodes() const { return nodes; }

    // Setter and getter for name
    void setName(string nm) { name = nm; }
    string getName() { return name; }

    void push_back(T1 value, T2 key) {
        keyValPair new_node(value, key);  // Create a new node
        nodes.push_back(new_node);        // Add new node to vector
    }

    void remove(T2 key) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].key == key) {           // Find the node with given key
                nodes.erase(nodes.begin() + i);  // Remove the node
                return;
            }
        }
    }

    T1 *operator[](T2 key) {
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].key == key) {   // Find the node with given key
                return &nodes[i].value;  // Return pointer to value of the node
                                         // Pointer returned for changing the value of the node
            }
        }

        return nullptr;  // If key is not found, return nullptr
    }

    myVector<T1, T2> &operator=(myVector<T1, T2> &v) {
        // Assignment operator copies the vector and the name
        name = v.name;
        nodes = v.nodes;
        return *this;
    }

    vector<keyValPair> *begin() {
        // Return pointer to beginning of vector for the Iterator class
        return &nodes;
    }

    bool isEmpty() { return nodes.size() == 0; }

    bool operator==(myVector<T1, T2> &v) {
        // If sizes are different, vectors are not equal
        if (nodes.size() != v.nodes.size()) {
            return false;
        }

        for (int i = 0; i < nodes.size(); i++) {
            // If any value or key is different, vectors are not equal
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

            // Count characters
            vector<int> char_counts(256, 0);  // Each index represents a character in ASCII table
            for (int i = 0; i < combined.length(); i++) {
                char_counts[(char)combined[i]]++;  // Increment count of character
            }
            // Find most frequent character
            char mostFrequentChar = 0;
            for (int i = 0; i < char_counts.size(); i++) {
                if (char_counts[i] > char_counts[mostFrequentChar]) {
                    mostFrequentChar = i;
                }
            }

            // Count words
            istringstream wordStream(combined);
            string word;
            myVector<int, string> wordCounts;  // Counts are stored in a vector with keys as words
            while (wordStream >> word) {
                if (wordCounts[word] == nullptr) {  // If word is not in vector, add it
                    wordCounts.push_back(1, word);
                }
                else {  // If word is in vector, increment its count
                    (*wordCounts[word])++;
                }
            }
            // Find most frequent word
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
                bool inserted = false;  // If the values vector is empty or value is greater than all values in vector,
                                        // value won't be inserted in the loop
                for (int j = 0; j < values.size(); j++) {
                    if (value < values[j]) {
                        values.insert(values.begin() + j, value);
                        inserted = true;
                        break;
                    }
                }
                if (!inserted) values.push_back(value);  // If not instered in the loop

                sum += value;  // Calculate sum at the same time
            }

            // Mean
            double mean = (double)sum / (double)values.size();

            // Median
            double median;
            if (values.size() % 2 == 0) {  // If size is even, median is the average of middle two values
                median = (values[values.size() / 2 - 1] + values[values.size() / 2]) / 2.0;
            }
            else {  // If size is odd, median is the middle value
                median = values[(values.size() - 1) / 2];
            }

            // Standard deviation
            double std_dev = 0;
            for (int i = 0; i < values.size(); i++) {
                std_dev += pow(values[i] - mean, 2);  // Sum of squared differences
            }
            std_dev = pow(std_dev / values.size(), 0.5);  // Square root of average of squared differences

            // Max
            T1 max = values[values.size() - 1];  // Last value is the max since values are sorted

            // Mode

            // Since values are sorted, we can count values in one loop
            T1 mode = values[0];
            int mode_count = 1;
            T1 current = values[0];
            int current_count = 1;
            for (int i = 1; i < values.size(); i++) {
                if (values[i] == current) {  // If value is same as previous value, increment current count
                    current_count++;
                }
                else {                                 // If value is different than previous value, we have a new value
                    if (current_count > mode_count) {  // If current value is more frequent than mode, update mode
                        mode = values[i - 1];
                        mode_count = current_count;
                    }
                    // Reset current value and count
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