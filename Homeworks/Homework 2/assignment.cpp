#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
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

int add_flight_to_list(flight *&currF, flight *&fToAdd) {
    // Add a given flight to a given flights list

    static int currentID = 0;  // Keep track of the current id for the flights as static in this function
                               // So it assigns the next id every time time function is called
    fToAdd->ID = currentID;    // Assign the current id

    if (!currF) {        // If flights list is empty
        currF = fToAdd;  // Make the current flight head
    }
    else {
        int fToAddTime = 60 * fToAdd->hour + fToAdd->min;  // Time of the flight-to-add
        int currTime = 60 * currF->hour + currF->min;      // Time of the current flight pointer from the list
        while (currF->next && fToAddTime >= currTime) {    // While the flight-to-add is later than
                                                           // the current flight, move current flight forward
            currF = currF->next;
            currTime = 60 * currF->hour + currF->min;  // Update current flight's time
        }

        while (currF->prev && fToAddTime <= currTime) {  // While the flight to add is earlier than
                                                         //  the current flight, move current flight backward
            currF = currF->prev;
            currTime = 60 * currF->hour + currF->min;  // Update current flight's time
        }

        if (fToAddTime > currTime) {  // If flight-to-add must come later
            // Add new flight in between of currF and its next (temp)
            flight *temp = currF->next;
            currF->next = fToAdd;
            fToAdd->prev = currF;

            if (temp) {               // If temp is not a null pointer
                fToAdd->next = temp;  // flight-to-add's next points to temp
                temp->prev = fToAdd;  // temp's prev also points to the new flight
            }
        }
        else {  // If flight-to-add must come earlier
            // Add new flight in between of currF and its previous (temp)
            flight *temp = currF->prev;
            currF->prev = fToAdd;
            fToAdd->next = currF;

            if (temp) {               // If temp is not a null pointer
                fToAdd->prev = temp;  // flight-to-add's prev points to temp
                temp->next = fToAdd;  // temp's next also points to the new flight
            }
        }
    }

    // Make sure currF points to head of the flight list
    while (currF->prev) {
        currF = currF->prev;
    }

    currentID++;           // Increment the current id after each addition
    return currentID - 1;  // Return the new id generated
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
                                     // This also moves current airline to the last element to add the new
            currAirline = currAirline->next;
            newAirlineID++;
        }

        airline *newAirline = new airline(a, newAirlineID, nullptr, nullptr);
        currAirline->next = newAirline;   // Add the new airline after the current one
        currAirline = currAirline->next;  // Move currAirline to the new airline
    }

    // Create the flight
    flight *new_flight = new flight(f, t, h, m, p);

    // Add the flight to the list
    int id = add_flight_to_list(currAirline->flights, new_flight);

    cout << "Flight ID " << id << " is added to the list.." << endl;
}

flight *create_flight_list(vector<flight> &flights) {
    // Create a linked list of flights that are ordered by time from a given flights vector

    flight *currF = nullptr;  // Pointer to current flight from the list
    for (int i = 0; i < flights.size(); i++) {
        flight *fToAdd = new flight(&flights[i]);  // Convert the flight from the vector into dynamic variable

        add_flight_to_list(currF, fToAdd);  // Add the new flight
    }

    // Go back to the head of the flights
    while (currF->prev) currF = currF->prev;

    return currF;  // Return the head
}

airline *make_linked_list_structure(vector<string> &airlines, vector<vector<flight>> &flights) {
    airline *head = nullptr;     // Head of the list to return
    airline *current = nullptr;  // Current airline to keep the list order
    for (int i = 0; i < airlines.size(); i++) {
        // Get the flights first
        flight *fHead = create_flight_list(flights[i]);

        airline *temp = new airline(airlines[i], i, nullptr, fHead);  // Create a new airline that points to a nullptr
        if (!head) {  // If the list is empty, the new airline is the head
            head = temp;
            current = temp;
        }
        else {                     // If it's not
            current->next = temp;  // Add the new to the end
            current = temp;        // Move the current
        }
    }

    return head;
}

pair<unsigned int, vector<int>> pathfinder(airline *&head, string startLoc, string stopLoc, int tranferCount) {
    // Best price and path found from the search
    unsigned int bestPrice = UINT_MAX;  // Set to max possible
    vector<int> bestPath;               // An empty vector that keeps the id of the used flights for that travel

    airline *currAirline = head;
    while (currAirline) {  // Go over every airline to find matching flights
        flight *currFlight = currAirline->flights;
        while (currFlight) {                // Go over each flight
            vector<int> path;               // Vector to keep track of the path
            unsigned int price = UINT_MAX;  // Cost of the travel from this flight to the stop location
                                            // Also start from max to ignore flights that don't match at all

            if (currFlight->from != startLoc) {  // If flight origin does not match start location, skip that flight
                currFlight = currFlight->next;
                continue;
            }

            if (currFlight->to == stopLoc) {     // If flight target matches the target stop location,
                                                 // then we found a feasible travel
                price = currFlight->price;       // Only price is this flight's price
                path.push_back(currFlight->ID);  // Only flight taken is this flight
            }
            else {  // If flight target doesn't match
                if (tranferCount > 0) {
                    // If there are available transfers, make a new search from this flight
                    pair<int, vector<int>> transferFlight = pathfinder(head, currFlight->to, stopLoc, tranferCount - 1);

                    if (transferFlight.second.size() > 0) {  // If there is a valid transfer continuation
                        // Price will be this flight's price + transfers' price
                        price = currFlight->price + transferFlight.first;
                        path.push_back(currFlight->ID);  // Path will start from this flight
                                                         // will continue with the path after the transfer
                        path.insert(path.end(), transferFlight.second.begin(), transferFlight.second.end());
                    }
                }
            }

            if (price < bestPrice) {  // If the new price is better
                bestPrice = price;    // make this price the new bestPrice
                bestPath = path;      // Make this path the new bestPath
            }

            currFlight = currFlight->next;
        }

        currAirline = currAirline->next;
    }

    // Return the minimum price and corresponding path(flights' ids) found for given locations
    return make_pair(bestPrice, bestPath);
}

void delete_linked_list(airline *&head) {
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

void remove_airline(airline *&head, int id) {
    // If we are trying to delete the head
    if (head->ID == id) {
        airline *temp = head;
        head = temp->next;
        delete temp;
        return;
    }

    airline *currAirline = head;
    while (currAirline->next) {  // We need the previous airline too
        if (currAirline->next->ID == id) {
            airline *temp = currAirline;
            currAirline->next = temp->next;  // Previous' next is deleted one's next
            delete temp;                     // Delete
            return;
        }
        currAirline = currAirline->next;
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
                flight *prev = currFlight->prev;
                flight *next = currFlight->next;
                delete currFlight;

                if (prev) {  // If previous exits, make previous' next 'next'
                    prev->next = next;
                }
                else {
                    // If previous does not exits, then we deleted the head node of the flights of current airline
                    currAirline->flights = next;  // Update it
                }

                if (next) {  // If next exits, make next's previous 'prev'
                    next->prev = prev;
                }

                if (!currAirline->flights) {  // If we deleted all flights from an airline
                    // Delete the airline
                    remove_airline(head, currAirline->ID);
                }

                cout << "Flight ID " << id << " is removed from the list.." << endl;
                return;
            }
            currFlight = currFlight->next;
        }
        currAirline = currAirline->next;
    }

    cout << "There is no flight with id " << id;
}

void print_flight(flight *flight) {
    // Print the flight information in the form
    // "[ID|FROM->TO|HOUR:MINUTE|PRICE]"
    cout << "[";
    cout << flight->ID << "|";
    cout << flight->from << "->" << flight->to << "|";
    cout << flight->hour << ":" << flight->min << "|";
    cout << flight->price << "TRY";
    cout << "]";
}

void print_all(airline *head) {
    // Print all the airlines their flights
    while (head) {
        cout << "###################################" << endl;
        // Airline information
        cout << "### AIRLINE ID: " << head->ID << " ###" << endl;
        cout << "NAME: " << head->name << endl;

        // Flights' informations
        flight *fTemp = head->flights;
        cout << "FLIGHTS: ";
        while (fTemp) {
            cout << "#";
            print_flight(fTemp);
            cout << "#";
            fTemp = fTemp->next;  // Move to next flight
        }
        cout << endl;

        head = head->next;  // Move to next airline
    }
}

void traverse_path(airline *&head, vector<int> &path) {
    // Traverse the path and print the flights
    for (int i = 0; i < path.size(); i++) {
        int id = path[i];

        // Search the id
        airline *currAirline = head;
        bool found = false;
        while (currAirline) {  // Go over airlines
            flight *currFlight = currAirline->flights;
            while (currFlight) {  // Go over flights
                if (currFlight->ID == id) {
                    print_flight(currFlight);  // Print the flight that matches
                    found = true;
                    break;
                }
                currFlight = currFlight->next;
            }

            if (found) break;                 // If found, stop
            currAirline = currAirline->next;  // If not, continue
        }

        // Print an arrow in between, but not after the last one
        if (i != path.size() - 1) cout << "->";
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

    string startLoc, stopLoc;  // Locations for the pathfinder
    int transferCount;         // Maximum number of transfers for the pathfinder
    pair<int, vector<int>> foundPath;

    char input;
    bool input_done = false;
    do {
        printMainMenu();
        cout << "Please enter your option " << endl;
        cin >> input;
        switch (input) {
            case '0':
                delete_linked_list(head);
                cout << "Data is is destroyed.." << endl;
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
                if (head) {
                    print_all(head);
                }
                else {
                    cout << "List is empty.." << endl;
                }
                break;
            case '3':
                add_flight_with_input(head);
                break;
            case '4':
                remove_flight_with_input(head);

                // If we deleted the head, then list is now empty
                if (!head) input_done = false;
                break;
            case '5':
                cout << "Where are you now?" << endl;
                cin >> startLoc;
                cout << "Where do you want to go?" << endl;
                cin >> stopLoc;
                cout << "Maximum number of transfers:" << endl;
                cin >> transferCount;

                foundPath = pathfinder(head, startLoc, stopLoc, transferCount);
                if (foundPath.second.size() == 0) {  // No path was found
                    cout << "No path found between " << startLoc << " and " << stopLoc << endl;
                }
                else {
                    cout << "##Best price path##" << endl;
                    traverse_path(head, foundPath.second);
                    cout << " $TOTAL PRICE: " << foundPath.first << endl;
                }
                break;
            case '6':
                cout << "Exiting.." << endl;
                exit(0);
            default:
                cout << "Invalid option: please enter again" << endl;
        }
    } while (true);
}

int main() {
    processMainMenu();
    return 0;
}
