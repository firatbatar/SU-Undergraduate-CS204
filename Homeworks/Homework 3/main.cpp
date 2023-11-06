#include <cctype>
#include <fstream>  // for ifstream
#include <iostream>
#include <sstream>  // std::stringstream
#include <string>
#include <vector>
using namespace std;

struct Command {
    string type;
    string parameter;
    Command *next;

    Command(){};

    Command(string ty, string pm, Command *nt = nullptr) : type(ty), parameter(pm), next(nt){};
};

struct Service {
    string name;
    Service *next;
    Command *commands;

    Service(){};

    Service(string nm, Service *nt = nullptr, Command *cm = nullptr) : name(nm), next(nt), commands(cm){};
};

struct User {
    string name;
    int ID;
    unsigned int debt;
    User *next;

    User(){};
    User(string nm, int id, User *nt = nullptr) : name(nm), ID(id), debt(0), next(nt){};
};

struct QueueNode {
    Service *servicePtr;
    User *requester;
    QueueNode *next;

    QueueNode(){};
    QueueNode(Service *s, User *rq, QueueNode *nt = nullptr) : servicePtr(s), requester(rq), next(nt){};
};

class Queue {
   private:
    QueueNode *head;
    QueueNode *rear;

   public:
    Queue() : head(nullptr), rear(nullptr) {}
    bool isEmpty() { return !head; }

    void enqueue(Service *&newService, User *&requester) {
        if (isEmpty()) {
            head = new QueueNode(newService, requester);
            rear = head;
        }
        else {
            rear->next = new QueueNode(newService, requester);
            rear = rear->next;
        }
    }

    bool dequeue(Service *&popped, User *&requester) {
        if (!isEmpty()) {
            QueueNode *temp = head;
            popped = head->servicePtr;
            requester = head->requester;
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
    Command *commandPtr;
    Service *callerPtr;
    StackNode *next;

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
            StackNode *temp = head;
            popped = temp->commandPtr;
            caller = temp->callerPtr;
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
            Stack reverseStack;
            while (!isEmpty()) {
                Command *popped;
                Service *caller;
                pop(popped, caller);
                reverseStack.push(popped, caller);
            }

            while (!reverseStack.isEmpty()) {
                Command *popped;
                Service *caller;
                reverseStack.pop(popped, caller);
                push(popped, caller);
                cout << caller->name << " " << popped->type << " " << popped->parameter << endl;
            }
        }
    }

    void clearService(Service *&service) {
        while (!isEmpty() && head->callerPtr == service) {
            Command *dummyCommand;
            Service *dummyCaller;
            pop(dummyCommand, dummyCaller);
        }
    }
};

void printStack(Stack &stack, string from) {
    cout << "Executing print stack; command from " << from << endl << "PRINTING THE STACK TRACE" << endl;
    stack.print();
}

void processWorkload(Queue &instructorsQueue, Queue &studentsQueue) {
    static Stack commmonStack;
    static int instructorRequestCount = 0;

    Service *currJob;
    User *requester;
    if (!instructorsQueue.isEmpty() && instructorRequestCount != 10) {
        instructorRequestCount++;
        cout << "Processing instructors queue..." << endl;

        instructorsQueue.dequeue(currJob, requester);
        cout << "Processing Prof. " << requester->name << "'s request (with ID " << requester->ID << ") of service (function):\n" << currJob->name << endl;
    }
    else if (!studentsQueue.isEmpty()) {
        instructorRequestCount = 0;
        // cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
        // cout << "10 instructors are served. Taking 1 student from the queue..." << endl;

        studentsQueue.dequeue(currJob, requester);
        cout << "Processing " << requester->name << "'s request (with ID " << requester->ID << ") of service (function):\n" << currJob->name << endl;

        // cout << "-------------------------------------------------------" << endl;
    }
    else {
        cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
        return;
    }

    Command *currCommand = currJob->commands;
    while (currCommand) {
        string commandType = currCommand->type;

        if (commandType == "define") {
            commmonStack.push(currCommand, currJob);
        }
        else if (commandType == "print") {
            printStack(commmonStack, currJob->name);
        }
        else if (commandType == "call") {
            Service *funcToCall;
            // processWorkload(instructorsQueue, studentsQueue, funcToCall)
        }

        currCommand = currCommand->next;
    }

    // Finish the service call
    cout << currJob->name << " is finished. Clearing the stack from it's data..." << endl;
    commmonStack.clearService(currJob);

    cout << "GOING BACK TO MAIN MENU" << endl;
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

        // Create the commands list
        Command *commands = nullptr;
        string commandLine;
        Command *prev = nullptr;
        while (getline(file, commandLine)) {
            string commandName, commandParam;
            stringstream commandLineStream(commandLine);

            commandLineStream >> commandName;
            commandLineStream >> commandParam;

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
        while (currentCommand) {
            cout << currentCommand->type << " " << currentCommand->parameter << ", ";
            currentCommand = currentCommand->next;
        }
        cout << "." << endl << endl;
        currentService = currentService->next;
    }
}

User *findUser(string name, int id) {
    static User *users = nullptr;

    if (users) {
        User *currUser = users;
        while (currUser) {
            if (currUser->name == name && currUser->ID == id) {
                return currUser;
            }

            currUser = currUser->next;
        }
    }

    // Not found
    User *newUser = new User(name, id, users);
    users = newUser;
    return newUser;
}

void addInstructorWorkload(Service *serviceHead, Queue &instructorsQueue) {
    string serviceName;
    cout << "Add a service (function) that the instructor wants to use:" << endl;
    cin >> serviceName;
    serviceName += ":";

    // Search for the given service name
    Service *currentService = serviceHead;
    while (currentService && currentService->name != serviceName) {
        currentService = currentService->next;
    }

    if (!currentService || currentService->name != serviceName) {
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO THE MAIN MENU" << endl;
        return;
    }

    string instructorName;
    int instructorID;
    // Found the requested service
    cout << "Give instructor's name: ";
    cin >> instructorName;
    cout << "Give insturctor's ID (an int): ";
    cin >> instructorID;

    User *requester = findUser(instructorName, instructorID);
    instructorsQueue.enqueue(currentService, requester);
    cout << "Prof. " << instructorName << "'s service request of " << serviceName << " has been put in the instructor's queue." << endl
         << "Waiting to be served..." << endl;
}

void addStudentWorkload(Service *serviceHead, Queue &studentsQueue) {
    string serviceName;
    cout << "Add a service (function) that the student wants to use:" << endl;
    cin >> serviceName;
    serviceName += ":";

    // Search for the given service name
    Service *currentService = serviceHead;
    while (currentService && currentService->name != serviceName) {
        currentService = currentService->next;
    }

    if (!currentService || currentService->name != serviceName) {
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO THE MAIN MENU" << endl;
        return;
    }

    string studentName;
    int studentID;
    // Found the requested service
    cout << "Give student's name: ";
    cin >> studentName;
    cout << "Give student's ID (an int): ";
    cin >> studentID;

    User *requester = findUser(studentName, studentID);
    studentsQueue.enqueue(currentService, requester);
    cout << studentName << "'s service request of " << serviceName << " has been put in the student's queue." << endl << "Waiting to be served..." << endl;
}

int main() {
    Service *serviceHead = nullptr;
    bool isFileReadSuccessful = createServicesFromFiles(serviceHead);
    if (!isFileReadSuccessful) return 0;

    printServices(serviceHead);

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
                exit(0);
            case 1:
                addInstructorWorkload(serviceHead, instructorsQueue);
                break;
            case 2:
                addStudentWorkload(serviceHead, studentsQueue);
                break;
            case 3:
                processWorkload(instructorsQueue, studentsQueue);
                break;
            case 4:
                // displayUsers();
                break;
            default:
                cout << "INVALID OPTION!!! Try again" << endl;
        }
    }
    return 0;
}