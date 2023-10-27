#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct flight {
    string from;
    string to;
    int hour;
    int min;
    int price;
    int ID;

    flight *next;
    flight *prev;

    // TO DO: implement constructor
    // Hint: You may need to implement multiple constructors
    flight() {}

    flight(const string &f, const string &t, int h, int m, int p)
        : from(f), to(t), hour(h), min(m), price(p), next(nullptr), prev(nullptr), ID(0) {}

    flight(flight *f)
        : from(f->from), to(f->to), hour(f->hour), min(f->min), price(f->price), next(f->next), prev(f->next), ID(0) {}
};

struct airline {
    string name;
    int ID;
    airline *next;
    flight *flights;

    // TO DO: implement constructor
    // Hint: You may need to implement multiple constructors
    airline() {}

    airline(const string &n, int id, airline *nt, flight *f) : name(n), ID(id), next(nt), flights(f) {}
};

pair<vector<string>, vector<vector<flight>>> read_files(bool input_done) {
    /// READ FLIGHTS///
    vector<string> airlines;
    vector<vector<flight>> flights(100);  // start with a previously sized vector or you get seg fault (for sure)

    while (not input_done) {
        string airline_name;
        string filename;
        cout << "Enter the name of airline: ";
        cin >> airline_name;
        cout << "Enter the name of airline file: ";
        cin >> filename;
        ifstream input(filename);

        if (filename == "done") {
            input_done = true;
            return make_pair(airlines, flights);
        }

        while (input.fail()) {
            cout << "Could not open file: " << filename << endl;
            cout << "Enter the name of airline: ";
            cin >> airline_name;
            cout << "Enter the name of airline file: ";
            cin >> filename;
            input.open(filename);

            if (filename == "done") {
                input_done = true;
                return make_pair(airlines, flights);
            }
        }

        airlines.push_back(airline_name);

        cout << "Processing input file: " << filename << endl;

        int line_no = 0;
        vector<string> lines;
        string line;
        int vector_location = airlines.size() - 1;
        while (getline(input, line)) {
            lines.push_back(line);
            line_no += 1;
            if (line_no % 5 == 0) {
                flight a_flight(lines[line_no - 5], lines[line_no - 4], stoi(lines[line_no - 3]),
                                stoi(lines[line_no - 2]), stoi(lines[line_no - 1]));
                flights[vector_location].push_back(a_flight);
            }
        }
    }
    if (input_done) {
        cout << "Input files are already read, however you can do manual changes.." << endl;
    }

    return make_pair(airlines, flights);
}

void add_flight_to_list(flight *&currF, flight *&fToAdd) {
    static int currentID = 0;  // Keep track of the current id for the flights
    fToAdd->ID = currentID;    // Assign the current id

    if (!currF) {        // If flights list is empty
        currF = fToAdd;  // Make the current flight head
    }
    else {
        int fToAddTime = 60 * fToAdd->hour + fToAdd->min;  // Time of the flight to add the list
        int currTime = 60 * currF->hour + currF->min;      // Time of the current flight pointer from the list
        while (currF->next && fToAddTime >= currTime) {    // While the flight to add is later than the current
                                                           // flight, move current flight forward
            currF = currF->next;
            currTime = 60 * currF->hour + currF->min;
        }

        while (currF->prev && fToAddTime <= currTime) {  // While the flight to add is earlier than the current
                                                         // flight, move current flight backward
            currF = currF->prev;
            currTime = 60 * currF->hour + currF->min;
        }

        if (fToAddTime > currTime) {  // If flight to add must come later
            // Add new flight in between of currF and its next (temp)
            flight *temp = currF->next;
            currF->next = fToAdd;
            fToAdd->prev = currF;

            if (temp) {
                fToAdd->next = temp;
                temp->prev = fToAdd;
            }
        }
        else {  // If flight to add must come earlier
            // Add new flight in between of currF and its previous (temp)
            flight *temp = currF->prev;
            currF->prev = fToAdd;
            fToAdd->next = currF;

            if (temp) {
                fToAdd->prev = temp;
                temp->next = fToAdd;
            }
        }
    }

    // Make sure currF points to head of the flight list
    while (currF->prev) {
        currF = currF->prev;
    }

    currentID++;  // Increment the current id after each addition
}

void add_flight_with_input(airline *&head) {
    // Take the inputs
    string a, f, t;
    int h, m, p;
    cout << "Adding manuel entry:" << endl;

    cout << "Airline: ";
    cin >> a;
    cout << "FROM: ";
    cin >> f;
    cout << "TO: ";
    cin >> t;
    cout << "HOUR: ";
    cin >> h;
    cout << "MIN: ";
    cin >> m;
    cout << "PRICE: ";
    cin >> p;

    // Find the airline
    airline *currAirline = head;
    while (currAirline && currAirline->name != a) {
        currAirline = currAirline->next;
    }

    if (!currAirline) {  // Airline does not exits
        // Create a new airline
        int newAirlineID = 1;        // Start from one since while loop won't count the last element
        currAirline = head;          // Go back to head airline
        while (currAirline->next) {  // Count the airlines for a new ID
            currAirline = currAirline->next;
            newAirlineID++;
        }

        airline *newAirline = new airline(a, newAirlineID, nullptr, nullptr);
        currAirline->next = newAirline;   // currAirline is already at last element
        currAirline = currAirline->next;  // Move currAirline to the new airline
    }

    // Create the flight
    flight *new_flight = new flight(f, t, h, m, p);

    // Add the flight to the list
    add_flight_to_list(currAirline->flights, new_flight);
}

// Create a linked list of flights that are ordered by time from a given flights vector
flight *create_flight_list(vector<flight> &flights) {
    flight *currF = nullptr;  // Pointer to current flight from the list
    for (int i = 0; i < flights.size(); i++) {
        flight *fToAdd = new flight(&flights[i]);  // Convert the flight from the vector into dynamic variable

        add_flight_to_list(currF, fToAdd);
    }

    // Go until the start of the list
    while (currF->prev) {
        currF = currF->prev;
    }

    return currF;
}

airline *make_linked_list_structure(vector<string> &airlines, vector<vector<flight>> &flights) {
    // TO DO: Implement
    airline *head = nullptr;
    for (int i = airlines.size() - 1; i >= 0; i--) {
        // Get the flights first
        flight *fHead = create_flight_list(flights[i]);

        head = new airline(airlines[i], i, head, fHead);  // Create a new head that points to previous head
    }

    return head;
}

int pathfinder(airline *head) {
    // TO DO: Implement
    // Hint: A recursive search seems like the best solution.
    // Hint: You don't have to use doubly linked list features
    return 0;
}

void delete_linked_list(airline *&head) {
    // TO DO: Implement
    while (head) {
        // Make the head next airline before deleting the head
        airline *temp = head;
        head = head->next;

        // Delete the flights
        flight *flights = temp->flights;
        flight *tempFlight;
        while (flights) {
            tempFlight = flights;
            flights = flights->next;
            delete tempFlight;
        }
        // Delete the airline
        delete temp;
    }
}

void remove_flight_with_input(airline *&head) {
    // Get the id
    int id;
    cout << "Flight id to remove: ";
    cin >> id;

    // Search the flight
    airline *currAirline = head;
    while (currAirline) {  // Go over airlines
        flight *currFlight = currAirline->flights;

        while (currFlight) {             // Go over flights of that airline
            if (currFlight->ID == id) {  // Found the flight
                cout << "Romeving flight id: " << id << endl;

                flight *prev = currFlight->prev;
                flight *next = currFlight->next;
                delete currFlight;

                if (prev) {
                    prev->next = next;
                }

                if (next) {
                    next->prev = prev;
                }

                return;
            }
            currFlight = currFlight->next;
        }
    }

    cout << "There is no flight with id " << id;
}

void print_all(airline *head) {
    while (head) {
        cout << "###################################" << endl;
        // Airline information
        cout << "### AIRLINE ID: " << head->ID << " ###" << endl;
        cout << "NAME: " << head->name << endl;

        // Flights' informations
        flight *fTemp = head->flights;
        cout << "FLIGHTS: ";
        while (fTemp) {
            cout << "#[";
            cout << fTemp->ID << "|";
            cout << fTemp->from << "->" << fTemp->to << "|";
            cout << fTemp->hour << ":" << fTemp->min << "|";
            cout << fTemp->price << "TRY";
            cout << "]#";

            fTemp = fTemp->next;  // Move to next flight
        }
        cout << endl;

        head = head->next;  // Move to next airline
    }
}

void printMainMenu() {
    cout << endl;
    cout << "I***********************************************I" << endl
         << "I               0 - DELETE DATA                 I" << endl
         << "I               1 - READ FILES                  I" << endl
         << "I               2 - PRINT ALL FLIGHTS           I" << endl
         << "I               3 - ADD FLIGHT                  I" << endl
         << "I               4 - REMOVE FLIGHT               I" << endl
         << "I               5 - PATH FINDER                 I" << endl
         << "I               6 - EXIT                        I" << endl
         << "I***********************************************I" << endl
         << ">>";
    cout << endl;
}

void processMainMenu() {
    pair<vector<string>, vector<vector<flight>>> lines_flights;
    airline *head = nullptr;

    char input;
    bool input_done = false;
    do {
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        switch (input) {
            case '0':
                // cout << "Commented out functionalities are going to be implemented" << endl;
                delete_linked_list(head);
                cout << "Data is deleted!" << endl;
                input_done = false;
                break;
            case '1':
                if (not input_done) {
                    lines_flights = read_files(input_done);
                    head = make_linked_list_structure(lines_flights.first, lines_flights.second);
                    cout << "Files are read.." << endl;
                }
                else {
                    cout << "Files are already read.." << endl;
                }
                input_done = true;
                break;
            case '2':
                // cout << "Commented out functionalities are going to be implemented" << endl;
                print_all(head);
                break;
            case '3':
                // cout << "Commented out functionalities are going to be implemented" << endl;
                add_flight_with_input(head);
                break;
            case '4':
                cout << "Commented out functionalities are going to be implemented" << endl;
                // remove_flight_with_input(head);
                break;
            case '5':
                cout << "Commented out functionalities are going to be implemented" << endl;
                // pathfinder(head);
                break;
            case '6':
                cout << "Exiting.." << endl;
                exit(0);
            default:
                cout << "Invalid option: please enter again" << endl;
        }
    } while (true);
}
//

int main() {
    processMainMenu();
    // Comply with the provided structs and specified linked list structure for a seamless grading

    return 0;
}
