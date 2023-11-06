#include <cctype>
#include <fstream>  // for ifstream
#include <iostream>
#include <sstream>  // std::stringstream
#include <string>
#include <vector>
using namespace std;

struct command {
    string type;
    string parameter;
    command *next;

    command(){};

    command(string ty, string pm, command *nt = nullptr) : type(ty), parameter(pm), next(nt){};
};

struct service {
    string name;
    service *next;
    command *commands;

    service(){};

    service(string nm, service *nt = nullptr, command *cm = nullptr) : name(nm), next(nt), commands(cm){};
};

struct QueueNode {
    service *service_p;
    QueueNode *next;

    QueueNode(){};
    QueueNode(service *s, QueueNode *nt = nullptr) : service_p(s), next(nt){};
};

class Queue {
   private:
    QueueNode *head;

   public:
    Queue() : head(nullptr) {}
    bool isEmpty() { return !head; }

    void push(service *&new_service) {
        if (isEmpty()) {
            head = new QueueNode(new_service);
        }
        else {
            QueueNode *temp = new QueueNode(new_service);
            temp->next = head;
            head = temp;
        }
    }

    bool pop(service *&popped) {
        if (!isEmpty()) {
            QueueNode *temp = head;
            head = head->next;
            popped = temp->service_p;
            delete temp;
            return true;
        }
        else {
            cout << "Queue is empty!" << endl;
            return false;
        }
    }
};

// TODO: Modify this part to make sure to impelement the logic for 10 requests for instructors and 1 request for students
/*
void processWorkload() {
    if (!instructorsQueue.isEmpty()) {
        cout << "Processing instructors queue..." << endl;

        cout << "Processing "
             << "JOB NAME"
             << "'s request (with ID "
             << "JOB ID"
             << ") of service (function):\n"
             << "FUNCTION NAME" <
            endl;
        // You need to implement the processWorkload --> you can modify inputs
        // processWorkload(...);

        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    else if (!studentsQueue.isEmpty()) {
        // TODO: This should print when you implemented 10 requests for instructors and 1 request for students logic
        // cout<<"10 instructors are served. Taking 1 student from the queue..."<<endl;

        cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
        cout << "Processing "
             << "JOB NAME"
             << "'s request (with ID "
             << "JOB ID"
             << ") of service (function):\n"
             << "FUNCTION NAME" << endl;
        cout << "-------------------------------------------------------" << endl;

        // You need to implement the processWorkload --> you can modify inputs
        // processWorkload(...);

        cout << "GOING BACK TO MAIN MENU" << endl;
    }
    else {
        cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
    }
}
*/
bool createServicesFromFiles(service *&f_head) {
    service *current = nullptr;

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
        string function_name;
        getline(file, function_name);

        // Create the commands list
        command *commands = nullptr;
        string command_line;
        command *prev = nullptr;
        while (getline(file, command_line)) {
            string command_name, command_param;
            stringstream command_l(command_line);

            command_l >> command_name;
            command_l >> command_param;

            if (!commands) {
                commands = new command(command_name, command_param);
                prev = commands;
            }
            else {
                command *new_command = new command(command_name, command_param);
                prev->next = new_command;
                prev = new_command;
            }
        }

        // Create the function
        service *new_function = new service(function_name, nullptr, commands);

        if (!f_head) {
            f_head = new_function;
            current = f_head;
        }
        else {
            current->next = new_function;
            current = new_function;
        }

        // Next file read
        cout << "Do you want to open another service defining file?\nPress (Y/y) for 'yes', otherwise press any key" << endl;
        cin >> c;
    }

    return true;
}

void printServices(service *f_head) {
    cout << "-------------------------------------------------------------------" << endl
         << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl
         << "-------------------------------------------------------------------" << endl
         << endl
         << endl;

    service *current_func = f_head;
    while (current_func) {
        cout << current_func->name << ":" << endl;

        command *curr_command = current_func->commands;
        while (curr_command) {
            cout << curr_command->type << " " << curr_command->parameter << ", ";
            curr_command = curr_command->next;
        }
        cout << "." << endl << endl;
        current_func = current_func->next;
    }
}

void addInstructorWorkload(service *f_head, Queue &instructorsQueue) {
    string service_name;
    cout << "Add a service (function) that the instructor wants to use:" << endl;
    cin >> service_name;
    service_name += ":";

    // Search for the given service name
    service *current_service = f_head;
    while (current_service && current_service->name != service_name) {
        current_service = current_service->next;
    }

    if (!current_service || current_service->name != service_name) {
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO THE MAIN MENU" << endl;
        return;
    }

    string instructor_name;
    int instructor_id;
    // Found the requested service
    cout << "Give instructor's name: ";
    cin >> instructor_name;
    cout << "Give insturctor's ID (an int): ";
    cin >> instructor_id;

    instructorsQueue.push(current_service);
    cout << "Prof. " << instructor_name << "'s service request of " << service_name << " has been put in the instructor's queue." << endl
         << "Waiting to be served..." << endl;
}

void addStudentWorkload(service *f_head, Queue &studentsQueue) {
    string service_name;
    cout << "Add a service (function) that the student wants to use:" << endl;
    cin >> service_name;
    service_name += ":";

    // Search for the given service name
    service *current_service = f_head;
    while (current_service && current_service->name != service_name) {
        current_service = current_service->next;
    }

    if (!current_service || current_service->name != service_name) {
        cout << "The requested service (function) does not exist." << endl << "GOING BACK TO THE MAIN MENU" << endl;
        return;
    }

    string student_name;
    int student_id;
    // Found the requested service
    cout << "Give student's name: ";
    cin >> student_name;
    cout << "Give student's ID (an int): ";
    cin >> student_id;

    studentsQueue.push(current_service);
    cout << student_name << "'s service request of " << service_name << " has been put in the student's queue." << endl << "Waiting to be served..." << endl;
}

int main() {
    service *f_head = nullptr;
    bool isFileReadSuccessful = createServicesFromFiles(f_head);
    if (!isFileReadSuccessful) return 0;

    printServices(f_head);

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
                addInstructorWorkload(f_head, instructorsQueue);
                break;
            case 2:
                addStudentWorkload(f_head, studentsQueue);
                break;
            case 3:
                // processWorkload();
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