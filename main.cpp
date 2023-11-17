#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

class MessManagementSystem {
private:
    unordered_map<int, int> enrollmentToCounter;  // Map to store enrollment to counter mapping
    queue<int> studentQueue;  // Queue to store incoming students
    stack<int> emptyCounters;  // Stack to keep track of empty counters

public:
    MessManagementSystem(int numCounters, const unordered_map<int, int>& predefinedAssignments) {
        // Initialize counters and enrollment to counter mapping
        for (int i = 1; i <= numCounters; ++i) {
            emptyCounters.push(i);
        }

        // Assign predefined counters to enrollment numbers
        for (const auto& entry : predefinedAssignments) {
            int enrollmentNumber = entry.first;
            int counter = entry.second;

            if (counter > 0 && counter <= numCounters && emptyCounters.size() > 0) {
                enrollmentToCounter[enrollmentNumber] = counter;
                emptyCounters.pop();
            }
        }
    }

    void enrollStudent(int enrollmentNumber) {
        // Check if there are empty counters
        if (emptyCounters.empty()) {
            cout << "Sorry, all counters are currently occupied. Please wait.\n";
            return;
        }

        // Assign a counter to the student
        int counter = emptyCounters.top();
        emptyCounters.pop();
        enrollmentToCounter[enrollmentNumber] = counter;
        studentQueue.push(enrollmentNumber);

        cout << "Student with enrollment number " << enrollmentNumber << " assigned to counter " << counter << ".\n";
    }

    void serveNextStudent() {
        // Check if there are students in the queue
        if (studentQueue.empty()) {
            cout << "No students in the queue.\n";
            return;
        }

        // Get the next student in the queue
        int enrollmentNumber = studentQueue.front();
        studentQueue.pop();

        // Return the counter to the stack
        int counter = enrollmentToCounter[enrollmentNumber];
        emptyCounters.push(counter);

        cout << "Student with enrollment number " << enrollmentNumber << " served from counter " << counter << ".\n";
    }

    void automaticServing(int numStudents) {
        // Simulate automatic serving for a specified number of students
        for (int i = 0; i < numStudents; ++i) {
            serveNextStudent();
        }
    }
};

int main() {
    // Assume there are 16 counters in the mess
    unordered_map<int, int> predefinedAssignments = {
        {1001, 1},
        {1502, 2},
        {1803, 3}
        // Add more predefined assignments as needed
    };

    MessManagementSystem messSystem(16, predefinedAssignments);

    int choice;
    int enrollmentNumber;

    do {
        cout << "\n1. Enroll a student\n2. Serve the next student\n3. Automatic serving\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter enrollment number: ";
                cin >> enrollmentNumber;
                messSystem.enrollStudent(enrollmentNumber);
                break;
            case 2:
                messSystem.serveNextStudent();
                break;
            case 3:
                int numStudents;
                cout << "Enter the number of students to automatically serve: ";
                cin >> numStudents;
                messSystem.automaticServing(numStudents);
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
