#include <cctype>
#include <fstream>  // for ifstream
#include <iostream>
#include <sstream>  // std::stringstream
#include <string>
#include <vector>
using namespace std;

struct Command {
    string type;       // 'define', 'print', or 'call'
    string parameter;  // Parameter of the command
    Command *next;

    Command(){};

    Command(string ty, string pm, Command *nt = nullptr) : type(ty), parameter(pm), next(nt){};
};

struct Service {
    string name;  // Name of the service (function_1, function_2, etc.)
    Service *next;
    Command *commands;

    Service(){};

    Service(string nm, Service *nt = nullptr, Command *cm = nullptr) : name(nm), next(nt), commands(cm){};
};

struct User {
    string name;
    int ID;
    unsigned int debt;  // Total cost of the user's requests
    User *next;         // Users are kept in a linked list structure

    User(){};
    User(string nm, int id, User *nt = nullptr) : name(nm), ID(id), debt(0), next(nt){};
};

struct QueueNode {
    // A special node struct for instructor and student request queues

    Service *servicePtr;  // Each node is a requested service (function)
    User *requester;      // Each node has a requester (user that requests the service)
    QueueNode *next;      // Queue is implemented in a linked list structure

    QueueNode(){};
    QueueNode(Service *s, User *rq, QueueNode *nt = nullptr) : servicePtr(s), requester(rq), next(nt){};
};

class Queue {
   private:
    QueueNode *head;
    QueueNode *rear;

   public:
    Queue() : head(nullptr), rear(nullptr) {}
    ~Queue() {
        // In the case when the program is exited before processing all the requests queues might be not-empty
        // Deconstructor will ensure that the memory allocated is given back when the program finishes
        while (!isEmpty()) {
            Service *dummyCommand;
            User *dummyUser;
            dequeue(dummyCommand, dummyUser);
        }
    }
    bool isEmpty() { return !head; }

    void enqueue(Service *&newService, User *&requester) {
        if (isEmpty()) {
            // If the queue is empty head and rear points to the only element
            head = new QueueNode(newService, requester);
            rear = head;
        }
        else {
            // If the queue is not empty, then add the new request to the end of the queue
            rear->next = new QueueNode(newService, requester);
            rear = rear->next;
        }
    }

    bool dequeue(Service *&popped, User *&requester) {
        if (!isEmpty()) {
            // The head node (the first added request) is popped and assigned to reference variables
            QueueNode *temp = head;
            popped = head->servicePtr;    // Service that has been requested
            requester = head->requester;  // Requester user of that service
            head = head->next;
            delete temp;
            return true;
        }
        else {
            cout << "Queue is empty!" << endl;
            return false;
        }
    }
};

struct StackNode {
    // A special node struct for processing services and commands

    Command *commandPtr;  // Command that has been added to the stack
    Service *callerPtr;   // The service that executes that command
    StackNode *next;      // Stack is impleted as a linked list structure

    StackNode(){};
    StackNode(Command *cm, Service *cl, StackNode *nt = nullptr) : commandPtr(cm), callerPtr(cl), next(nt){};
};

class Stack {
   private:
    StackNode *head;

   public:
    Stack() : head(nullptr){};

    bool isEmpty() { return !head; };

    void push(Command *&newCommand, Service *&caller) {
        // Add a new node to the beginning of the list
        if (isEmpty()) {
            head = new StackNode(newCommand, caller);
        }
        else {
            StackNode *temp = new StackNode(newCommand, caller, head);
            head = temp;
        }
    }

    bool pop(Command *&popped, Service *&caller) {
        if (!isEmpty()) {
            // The head node (the last added command) is popped and assigned to reference variables
            StackNode *temp = head;
            popped = temp->commandPtr;  // The command that has been executed
            caller = temp->callerPtr;   // The sercive that executed that command
            head = head->next;
            delete temp;
            return true;
        }
        else {
            cout << "Stack is empty!" << endl;
            return false;
        }
    }

    void print() {
        if (isEmpty()) {
            cout << "The stack is empty" << endl;
        }
        else {
            // Stack needs to be printed in reverse and it must keep its nodes after printing

            // First reverse the stack into a new stack
            Stack reverseStack;
            while (!isEmpty()) {
                Command *popped;
                Service *caller;
                pop(popped, caller);
                reverseStack.push(popped, caller);
            }

            // Then reverse the reversedStack back to the original stack while printing that reversed order
            while (!reverseStack.isEmpty()) {
                Command *popped;
                Service *caller;
                reverseStack.pop(popped, caller);
                push(popped, caller);
                cout << caller->name << ": " << popped->type << " " << popped->parameter << ";" << endl;
            }
        }
    }

    void clearService(Service *&service) {
        // Clear the commands of a given service from the stack
        while (!isEmpty() && head->callerPtr == service) {  // Each node keeps it executer service pointer
            Command *dummyCommand;
            Service *dummyCaller;
            pop(dummyCommand, dummyCaller);
        }
    }
};

Service *findService(Service *&serviceHead, string serviceName) {
    // Search for the given service name
    Service *currentService = serviceHead;
    while (currentService && currentService->name != serviceName) {
        currentService = currentService->next;
    }

    // If service is not found, return a null pointer
    if (!currentService || currentService->name != serviceName) {
        return nullptr;
    }

    return currentService;
}

void processWorkload(Service *&serviceHead, Queue &instructorsQueue, Queue &studentsQueue, Service *funcToCall = nullptr, User *requesterToCall = nullptr) {
    static Stack commmonStack;  // Common stack to keep the commands executed
    static int instructorRequestCount = 0;

    Service *currJob;  // The service that needs to be called
    User *requester;   // The user that requested it

    if (funcToCall) {  // If the service (function) is called recursivly from another service call
        currJob = funcToCall;
        requester = requesterToCall;
    }
    else if (!instructorsQueue.isEmpty() && instructorRequestCount != 10) {  // If a new request is being proccessed for a instructor (not recursively)
        instructorRequestCount++;
        cout << "Processing instructors queue..." << endl;

        // Get the service to be called from the instructor queue
        instructorsQueue.dequeue(currJob, requester);

        cout << "Processing Prof. " << requester->name << "'s request (with ID " << requester->ID << ") of service (function):\n" << currJob->name << endl;
        cout << "-------------------------------------------------------" << endl;
    }
    else if (!studentsQueue.isEmpty()) {  // If a new request is being proccessed for a student (not recursively)
        if (instructorRequestCount != 10) {
            cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
        }
        else {
            cout << "10 instructors are served. Taking 1 student from the queue..." << endl;
            instructorRequestCount = 0;  // Reset the insturctor request count
        }

        // Get the service to be called from the student queue
        studentsQueue.dequeue(currJob, requester);

        cout << "Processing " << requester->name << "'s request (with ID " << requester->ID << ") of service (function):\n" << currJob->name << endl;
        cout << "-------------------------------------------------------" << endl;
    }
    else {  // No request is waiting in the queues
        cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
        return;
    }

    // Process and call the requested (or recursively called) service
    Command *currCommand = currJob->commands;
    while (currCommand) {
        string commandType = currCommand->type;

        if (commandType == "define") {
            // 'define' command is added to the stack
            commmonStack.push(currCommand, currJob);
            requester->debt += 1;
        }
        else if (commandType == "print") {
            // 'print' command prints the current stack
            cout << "Executing print stack; command from " << currJob->name << endl << "PRINTING THE STACK TRACE:" << endl;
            commmonStack.print();
            requester->debt += 2;
        }
        else if (commandType == "call") {
            // 'call' command calls a function that it takes the name as a parameter

            string funcToCallName = currCommand->parameter;                  // The name of the service
            Service *funcToCall = findService(serviceHead, funcToCallName);  // Find the service with that name
            requester->debt += 5;

            cout << "Calling " << funcToCallName << " from " << currJob->name << endl;

            // If that function exists in the available services, then call it recursively
            if (funcToCall) {
                processWorkload(serviceHead, instructorsQueue, studentsQueue, funcToCall, requester);
            }
        }

        currCommand = currCommand->next;  // Move the to next command
    }

    // Finish the call of the current service
    cout << currJob->name << " is finished. Clearing the stack from it's data..." << endl;
    commmonStack.clearService(currJob);  // Clear the stack

    // If this calls is not done recursively, then it's the original call which returns to the main menu
    if (!funcToCall) {
        cout << "GOING BACK TO MAIN MENU" << endl;
    }
}

bool createServicesFromFiles(Service *&serviceHead) {
    Service *current = nullptr;

    char c = 'y';
    cout << "If you want to open a service (function) defining file,\nthen press (Y/y) for 'yes', otherwise press any single key" << endl;
    cin >> c;
    while (c == 'Y' || c == 'y') {
        string filename;
        cout << "Enter the input file name: ";
        cin >> filename;

        ifstream file(filename);

        if (file.fail()) {
            cout << "Could not open file " << filename << endl;
            return false;
        }

        // Create the list
        string functionName;
        getline(file, functionName);
        functionName = functionName.substr(0, functionName.size() - 1);  // Remove the ':' from the end

        // Create the commands list
        Command *commands = nullptr;
        string commandLine;
        Command *prev = nullptr;
        while (getline(file, commandLine)) {
            string commandName, commandParam;
            stringstream commandLineStream(commandLine);

            commandLineStream >> commandName;
            commandLineStream >> commandParam;
            commandParam = commandParam.substr(0, commandParam.size() - 1);  // Remove the ';' from the end

            if (!commands) {
                commands = new Command(commandName, commandParam);
                prev = commands;
            }
            else {
                Command *newCommand = new Command(commandName, commandParam);
                prev->next = newCommand;
                prev = newCommand;
            }
        }

        // Create the function
        Service *newService = new Service(functionName, nullptr, commands);

        if (!serviceHead) {
            serviceHead = newService;
            current = serviceHead;
        }
        else {
            current->next = newService;
            current = newService;
        }

        // Next file read
        cout << "Do you want to open another service defining file?\nPress (Y/y) for 'yes', otherwise press any key" << endl;
        cin >> c;
    }

    return true;
}

void printServices(Service *serviceHead) {
    cout << "-------------------------------------------------------------------" << endl
         << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl
         << "-------------------------------------------------------------------" << endl
         << endl
         << endl;

    Service *currentService = serviceHead;
    while (currentService) {
        cout << currentService->name << ":" << endl;

        Command *currentCommand = currentService->commands;
        while (currentCommand && currentCommand->next) {
            cout << currentCommand->type << " " << currentCommand->parameter << ";, ";
            currentCommand = currentCommand->next;
        }
        cout << currentCommand->type << " " << currentCommand->parameter << "." << endl << endl;
        currentService = currentService->next;
    }
}

User *findUser(User *&users, string name, int id) {
    // Find an existing user with given unique (name, id) pair
    if (users) {
        User *currUser = users;
        while (currUser) {
            if (currUser->name == name && currUser->ID == id) {
                return currUser;
            }

            currUser = currUser->next;
        }
    }

    // If user is not found, create a new one and add it to the users list
    User *newUser = new User(name, id, users);
    users = newUser;
    return newUser;
}

void addInstructorWorkload(Service *serviceHead, Queue &instructorsQueue, User *&users) {
    string serviceName;
    cout << "Add a service (function) that the instructor wants to use:" << endl;
    cin >> serviceName;

    // Search for the given service name
    Service *serviceToAdd = findService(serviceHead, serviceName);
    if (!serviceToAdd) {
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO THE MAIN MENU" << endl;
        return;
    }

    // Get the requester info
    string instructorName;
    int instructorID;
    cout << "Give instructor's name: ";
    cin >> instructorName;
    cout << "Give insturctor's ID (an int): ";
    cin >> instructorID;

    User *requester = findUser(users, instructorName, instructorID);  // Find (or create) the user struct
    instructorsQueue.enqueue(serviceToAdd, requester);                // Add the new request to the instructor queue
    cout << "Prof. " << instructorName << "'s service request of " << serviceName << endl
         << "has been put in the instructor's queue." << endl
         << "Waiting to be served..." << endl;
}

void addStudentWorkload(Service *serviceHead, Queue &studentsQueue, User *&users) {
    string serviceName;
    cout << "Add a service (function) that the student wants to use:" << endl;
    cin >> serviceName;

    // Search for the given service name
    Service *serviceToAdd = findService(serviceHead, serviceName);
    if (!serviceToAdd) {
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO THE MAIN MENU" << endl;
        return;
    }

    // Get the requester info
    string studentName;
    int studentID;
    cout << "Give student's name: ";
    cin >> studentName;
    cout << "Give student's ID (an int): ";
    cin >> studentID;

    User *requester = findUser(users, studentName, studentID);  // Find (or create) the user struct
    studentsQueue.enqueue(serviceToAdd, requester);             // Add the new request to the student queue
    cout << studentName << "'s service request of " << serviceName << " has been put in the student's queue." << endl << "Waiting to be served..." << endl;
}

void displayUsers(User *&users) {
    User *currentUser = users;
    while (currentUser) {
        cout << "Name: " << currentUser->name << " ID: " << currentUser->ID << " " << currentUser->debt << " TRY" << endl;
        currentUser = currentUser->next;
    }
}

int main() {
    Service *serviceHead = nullptr;
    bool isFileReadSuccessful = createServicesFromFiles(serviceHead);
    if (!isFileReadSuccessful) return 0;

    printServices(serviceHead);

    User *users = nullptr;

    Queue instructorsQueue;
    Queue studentsQueue;
    while (true) {
        cout << endl;
        cout << "**********************************************************************" << endl
             << "**************** 0 - EXIT PROGRAM                        *************" << endl
             << "**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************" << endl
             << "**************** 2 - ADD A STUDENT SERVICE REQUEST       *************" << endl
             << "**************** 3 - SERVE (PROCESS) A REQUEST           *************" << endl
             << "**************** 4 - DISPLAY USER PAYMENTS               *************" << endl
             << "**********************************************************************" << endl;
        cout << endl;
        int option;
        cout << "Pick an option from above (int number from 0 to 3): ";
        cin >> option;
        switch (option) {
            case 0:
                cout << "PROGRAM EXITING ... " << endl;

                // Give back the memory allacoted for Users and Services lists
                while (users) {
                    User *temp = users;
                    users = users->next;
                    delete temp;
                }

                while (serviceHead) {
                    Service *temp = serviceHead;
                    serviceHead = serviceHead->next;
                    delete temp;
                }

                exit(0);
            case 1:
                addInstructorWorkload(serviceHead, instructorsQueue, users);
                break;
            case 2:
                addStudentWorkload(serviceHead, studentsQueue, users);
                break;
            case 3:
                processWorkload(serviceHead, instructorsQueue, studentsQueue);
                break;
            case 4:
                displayUsers(users);
                break;
            default:
                cout << "INVALID OPTION!!! Try again" << endl;
        }
    }
    return 0;
}