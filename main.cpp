#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
#include <vector>
using namespace std;

// STUDENT RECORD MANAGEMENT SYSTEM

// Part 1 - Student records (linked list)
// Part 2 - Searching (linear search and binary search)
// Part 3 - Sorting (insertion sort and selection sort)
// Part 4 - Stack (Recently Deleted Students)
// Part 5 - Queue (Student Service Queue)
// Part 6 - Recursion

// STUDENT STRUCTURE

struct Student
{
    int id;
    string firstName;
    string lastName;
    float gpa;
};

// LINKED LIST NODE

struct Node
{
    Student data;
    Node *next;
};

// PART 4 - STACK CLASS (RECENTLY DELETED STUDENTS)
// Kept as-is: Delete Student (option 5) depends on this class.
// PART 5 - QUEUE CLASS (STUDENT SERVICE QUEUE)

class StudentQueue
{
private:
    struct QueueNode
    {
        Student data;
        QueueNode *next;
    };

    QueueNode *front;
    QueueNode *rear;

public:
    StudentQueue() : front(nullptr), rear(nullptr) {}

    ~StudentQueue()
    {
        clear();
    }

    StudentQueue(const StudentQueue &) = delete;
    StudentQueue &operator=(const StudentQueue &) = delete;

    void enqueue(const Student &student)
    {
        QueueNode *newNode = new QueueNode;

        newNode->data = student;

        newNode->next = nullptr;

        if (rear == nullptr)
        {
            front = newNode;
            rear = newNode;
        }
        else
        {
            rear->next = newNode;

            rear = newNode;
        }
    }

    Student dequeue()
    {
        Student emptyStudent = {-1, "", "", 0};

        if (front == nullptr)
        {
            cout << "Queue is empty.\n";
            return emptyStudent;
        }

        QueueNode *temp = front;

        Student student = temp->data;

        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete temp;

        return student;
    }

    Student peek() const
    {
        Student emptyStudent = {-1, "", "", 0};

        if (front == nullptr)
        {
            cout << "Queue is empty.\n";
            return emptyStudent;
        }

        return front->data;
    }

    void displayQueue() const
    {
        cout << "\n========================================\n";
        cout << "          STUDENT SERVICE QUEUE\n";
        cout << "========================================\n";

        if (front == nullptr)
        {
            cout << "Queue is empty.\n";
            return;
        }

        QueueNode *current = front;

        int position = 1;

        while (current != nullptr)
        {
            cout << position
                 << ". "
                 << current->data.firstName
                 << " "
                 << current->data.lastName
                 << endl;

            current = current->next;

            position++;
        }
    }

    void clear()
    {
        while (front != nullptr)
        {
            QueueNode *temp = front;

            front = front->next;

            delete temp;
        }

        rear = nullptr;
    }
};

class StudentStack
{
private:
    struct StackNode
    {
        Student data;
        StackNode *next;
    };

    StackNode *top;

public:
    StudentStack() : top(nullptr) {}

    ~StudentStack()
    {
        clear();
    }

    StudentStack(const StudentStack &) = delete;
    StudentStack &operator=(const StudentStack &) = delete;

    void push(const Student &student)
    {
        StackNode *newNode = new StackNode;

        newNode->data = student;

        newNode->next = top;

        top = newNode;
    }

    Student pop()
    {
        Student emptyStudent = {-1, "", "", 0};

        if (top == nullptr)
        {
            cout << "Stack is empty.\n";
            return emptyStudent;
        }

        StackNode *temp = top;

        Student student = temp->data;

        top = top->next;

        delete temp;

        return student;
    }

    Student peek() const
    {
        Student emptyStudent = {-1, "", "", 0};

        if (top == nullptr)
        {
            cout << "Stack is empty.\n";
            return emptyStudent;
        }

        return top->data;
    }

    void displayStack() const
    {
        cout << "\nSTACK:\n";

        if (top == nullptr)
        {
            cout << "Stack is empty.\n";
            return;
        }

        StackNode *current = top;

        cout << "Top\n";
        cout << " |\n";
        cout << " v\n";

        while (current != nullptr)
        {
            cout << current->data.id
                 << " "
                 << current->data.firstName << " "
                 << current->data.lastName
                 << endl;

            current = current->next;
        }
    }

    void clear()
    {
        while (top != nullptr)
        {
            StackNode *temp = top;

            top = top->next;

            delete temp;
        }
    }
};

// GLOBAL VARIABLES
// Objects of the two classes

Node *head = nullptr;
StudentStack deletedStack;
StudentQueue serviceQueue;

// MAIN

void mainMenu();
void deleteAllStudents(Node *&head);
void clearInput();
void addStudent(Node *&head);
void displayStudents(Node *head);
void searchStudent(Node *head);
void updateStudent(Node *head);
void deleteStudent(Node *&head);
void sortStudents(Node *head);
void stackOperations();
void queueOperations();
void studentStatistics(Node *head);

int main()
{
    mainMenu();

    // Free dynamically allocated memory
    deleteAllStudents(head);

    cout << "\nProgram terminated safely.\n";

    return 0;
}

// MAIN MENU

void mainMenu()
{
    int choice = 0;
    
    do
    {
        cout << "\n\n";
        cout << "========================================\n";
        cout << "     STUDENT RECORD MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "Welcome!\n";

        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort Students\n";
        cout << "7. Stack Operations\n";
        cout << "8. Queue Operations\n";
        cout << "9. Student Statistics\n";
        cout << "10. Exit\n";

        cout << "========================================\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice)) // when the receiving input fails
        {
            clearInput();
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            addStudent(head);
            break;

        case 2:
            displayStudents(head);
            break;

        case 3:
            searchStudent(head);
            break;

        case 4:
            updateStudent(head);
            break;

        case 5:
            deleteStudent(head);
            break;

        case 6:
            sortStudents(head);
            break;

        case 7:
            stackOperations();
            break;

        case 8:
            queueOperations();
            break;

        case 9:
            studentStatistics(head);
            break;

        case 10:
            cout << "\nExiting program...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 10);
}

// CLEANUP FUNCTION

void deleteAllStudents(Node *&head)
{
    while (head != nullptr)
    {
        Node *temp = head;

        head = head->next;

        delete temp;
    }
}

// UTILITY FUNCTIONS

void clearInput()
{
    cin.clear();                                         // resets the failure state
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discards the invalid input
}

// Reads a Student ID: positive number, maximum 8 digits
int readStudentID()
{
    int ID;

    while (true)
    {
        cout << "Enter Student ID (max 8 digits): ";
        cin >> ID;

        if (cin.fail() || ID <= 0)
        {
            cout << "Invalid input. Enter a positive number.\n";
            clearInput();
            continue;
        }

        // Count the digits of ID
        int length = 0;

        for (int temp = ID; temp > 0; temp /= 10)
        {
            length++;
        }

        if (length != 8)
        {
            cout << "Exceeds the number limit (8 digits) or Not enough. Try again.\n";
            continue;
        }

        return ID;
    }
}
// Capitalizes the first letter of every word, lowercases the rest
// Example: "juan DELA" -> "Juan Dela"
string capitalizeName(string name)
{
    bool startOfWord = true;

    for (size_t i = 0; i < name.size(); i++)
    {
        unsigned char c = static_cast<unsigned char>(name[i]);

        if (c == ' ')
        {
            startOfWord = true;
        }
        else if (startOfWord)
        {
            name[i] = static_cast<char>(toupper(c));
            startOfWord = false;
        }
        else
        {
            name[i] = static_cast<char>(tolower(c));
        }
    }

    return name;
}

// Removes spaces and tabs from the start and end of a string
string trimSpaces(const string &text)
{
    size_t first = text.find_first_not_of(" \t");

    if (first == string::npos)
    {
        return "";
    }

    size_t last = text.find_last_not_of(" \t");

    return text.substr(first, last - first + 1);
}

// Prints the table column headings and separator line
void displayTableHeader()
{
    cout << left
         << setw(10) << "ID"
         << setw(18) << "Last Name"
         << setw(18) << "First Name"
         << "GPA\n";

    cout << "----------------------------------------\n";
}

// Reads a name (a full line). The first letter is capitalized
// automatically. If allowMultipleWords is false, only one word
// is accepted (used for the last name).
string readName(const string &prompt, bool allowMultipleWords)
{
    string name;

    while (true)
    {
        cout << prompt;

        // Skip the newline left behind by an earlier cin >> input
        if (cin.peek() == '\n')
        {
            cin.ignore();
        }

        getline(cin, name);

        name = trimSpaces(name);

        if (name.empty())
        {
            cout << "Name cannot be empty.\n";
            continue;
        }

        if (!allowMultipleWords &&
            name.find(' ') != string::npos)
        {
            cout << "Last name must be one word.\n";
            continue;
        }

        return capitalizeName(name);
    }
}

// Reads a GPA from 1.00 to 5.00
float readGPA(const string &prompt)
{
    float gpa;

    cout << prompt;

    while (!(cin >> gpa) ||
           gpa < 1.0 ||
           gpa > 5.0)
    {
        cout << "Invalid GPA. Enter a value from 1.00 to 5.00: ";
        clearInput();
    }

    return gpa;
}

// BINARY SEARCH
Node *binarySearch(Node *head, int id)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    // Count students
    int size = 0;
    Node *current = head;

    while (current != nullptr)
    {
        size++;
        current = current->next;
    }

    // Copy the node pointers into a temporary array
    Node **nodes = new Node *[size];

    current = head;

    for (int i = 0; i < size; i++)
    {
        nodes[i] = current;
        current = current->next;
    }

    // Sort the pointers by ID (insertion sort)
    for (int i = 1; i < size; i++)
    {
        Node *key = nodes[i];
        int j = i - 1;

        while (j >= 0 && nodes[j]->data.id > key->data.id)
        {
            nodes[j + 1] = nodes[j];
            j--;
        }

        nodes[j + 1] = key;
    }

    // Binary search
    int low = 0;
    int high = size - 1;
    Node *result = nullptr;

    while (low <= high)
    {
        int middle = low + (high - low) / 2;

        if (nodes[middle]->data.id == id)
        {
            result = nodes[middle];
            break;
        }
        else if (nodes[middle]->data.id < id)
        {
            low = middle + 1;
        }
        else
        {
            high = middle - 1;
        }
    }

    delete[] nodes;

    return result;
}

// DISPLAY STUDENT

void displayStudent(const Student &student)
{
    cout << left
         << setw(10) << student.id
         << setw(18) << student.lastName
         << setw(18) << student.firstName
         << fixed << setprecision(2)
         << student.gpa << endl;
}

// ADD STUDENT

void addStudent(Node *&head)
{
    Student student;

    cout << "\n========================================\n";
    cout << "             ADD STUDENT\n";
    cout << "========================================\n";

    student.id = readStudentID();

    // Check if ID already exists
    Node *check = head;

    while (check != nullptr)
    {
        if (check->data.id == student.id)
        {
            cout << "A student with this ID already exists.\n";
            return;
        }

        check = check->next;
    }

    student.firstName = readName("Enter First Name: ", true);

    student.lastName = readName("Enter Last Name: ", false);

    student.gpa = readGPA("Enter GPA (1.00 - 5.00): ");

    // Create a new node dynamically
    Node *newNode = new Node;

    newNode->data = student;
    newNode->next = nullptr;

    // Insert at the end of the list
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
    }

    cout << "\nStudent added successfully!\n";

    // Input 1 to go back to the Main Menu
    int menuChoice = 0;
    while (menuChoice != 2)
    {
        cout << "\nInput 1 to add new Student. ";
        cout << "\nInput 2 to go back to the Main Menu:\n";
        cin >> menuChoice;

        switch (menuChoice)
        {
        case 1:
            addStudent(head);
            return;
        case 2:

            break;
        default:
            cout << "\nInvalid Input!" << endl;
            clearInput();
            break;
        }
    }
}

// DISPLAY ALL STUDENTS

void displayStudents(Node *head)
{
    cout << "\n========================================\n";
    cout << "           ALL STUDENTS\n";
    cout << "========================================\n";

    if (head == nullptr)
    {
        cout << "No student records found.\n";
        return;
    }

    displayTableHeader();

    Node *current = head;

    while (current != nullptr)
    {
        displayStudent(current->data);
        current = current->next;
    }

    // Input 1 to go back to the Main Menu
    int menuChoice;

    cout << "\nInput 1 to go back to the Main Menu: ";

    while (!(cin >> menuChoice) || menuChoice != 1)
    {
        cout << "Invalid input. Input 1 to go back to the Main Menu: ";
        clearInput();
    }
}

// LINEAR SEARCH
// Checks the nodes one by one from the head until the ID is
// found. Works on unsorted data. Time: O(n).

vector<Node *> linearSearch(Node *head, int id)
{
    vector<Node *> results;

    Node *current = head;
    while (current != nullptr)
    {
        if (current->data.id == id)
        {
            results.push_back(current);
        }
        current = current->next;
    }

    return results;
}

// function overload
vector<Node *> linearSearch(Node *head, string name)
{
    vector<Node *> results;
    name = trimSpaces(name);
    name = capitalizeName(name);
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data.firstName.find(name) == 0 || current->data.lastName.find(name) == 0)
        {
            results.push_back(current);
        }
        current = current->next;
    }
    return results;
}
// SEARCH STUDENT

void searchStudent(Node *head)
{
    cout << "\n========================================\n";
    cout << "             SEARCH STUDENT\n";
    cout << "========================================\n";

    if (head == nullptr)
    {
        cout << "There's no currently student records available yet.\n";
        return;
    }
    string searchInput;

    cout << "Enter GPA or Name: ";

    clearInput();
    cin >> searchInput;

    bool isNumber = !searchInput.empty();

    for (char c : searchInput)
    {
        if (!isdigit(c))
        {
            isNumber = false;
            break;
        }
    }
    vector<Node *> results;
    if (isNumber)
    {
        int id = stoi(searchInput);

        results = linearSearch(head, id);
    }
    else
    {
        string name = searchInput;
        results = linearSearch(head, name);
    }

    if (results.empty())
    {
        cout << "No Students found";
        searchStudent(head);
        return;
    }
    displayTableHeader();
    for (Node *student : results)
    {
        displayStudent(student->data);
    }

    // TODO: write your code here
    // (ask for 1 = Linear Search / 2 = Binary Search,
    //  ask for the Student ID, call linearSearch() or
    //  binarySearch(), then display the result)
}

// UPDATE STUDENT

void updateStudent(Node *head)
{
    int id;

    cout << "\n========================================\n";
    cout << "            UPDATE STUDENT\n";
    cout << "========================================\n";

    cout << "Enter Student ID: ";

    if (!(cin >> id))
    {
        clearInput();
        cout << "Invalid input.\n";
        return;
    }

    Node *studentNode = binarySearch(head, id);

    if (studentNode == nullptr)
    {
        cout << "Student not found.\n";
        return;
    }

    cout << "\nCurrent Information:\n";

    displayStudent(studentNode->data);

    cout << "\n";

    studentNode->data.firstName = readName("Enter new First Name: ", true);

    studentNode->data.lastName = readName("Enter new Last Name: ", false);

    studentNode->data.gpa = readGPA("Enter new GPA (1.00 - 5.00): ");

    cout << "\nStudent updated successfully!\n";
}

// DELETE STUDENT

void deleteStudent(Node *&head)
{
    int id;

    cout << "\n========================================\n";
    cout << "            DELETE STUDENT\n";
    cout << "========================================\n";

    if (head == nullptr)
    {
        cout << "No students to delete.\n";
        return;
    }

    cout << "Enter Student ID: ";

    if (!(cin >> id))
    {
        clearInput();
        cout << "Invalid input.\n";
        return;
    }

    Node *current = head;
    Node *previous = nullptr;

    while (current != nullptr &&
           current->data.id != id)
    {
        previous = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Student not found.\n";
        return;
    }

    Student deletedStudent = current->data;

    if (previous == nullptr)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    deletedStack.push(deletedStudent);

    delete current;

    cout << "\nStudent: "
         << deletedStudent.id
         << " - "
         << deletedStudent.firstName
         << " "
         << deletedStudent.lastName
         << endl;

    cout << "\nStudent added to Deleted Stack.\n";

    deletedStack.displayStack();
}

vector<Node *> createStudentArray(Node *head)
{
    vector<Node *> studentArray;

    Node *current = head;
    while (current != nullptr)
    {
        studentArray.push_back(current);

        current = current->next;
    }
    return studentArray;
}

void bubbleSort(vector<Node *> &nodes, int desiredInfo, bool order)
{
    for (int i = 0; i < nodes.size() - 1; i++)
    {
        for (int j = 0; j < nodes.size() - 1; j++)
        {
            switch (desiredInfo)
            {
            case 1:
                if (order ? nodes[j]->data.id < nodes[j + 1]->data.id
                          : nodes[j]->data.id > nodes[j + 1]->data.id)
                {
                    swap(nodes[j], nodes[j + 1]);
                }
                break;
            case 2:
                if (order ? nodes[j]->data.lastName < nodes[j + 1]->data.lastName
                          : nodes[j]->data.lastName > nodes[j + 1]->data.lastName)
                {
                    swap(nodes[j], nodes[j + 1]);
                }
                break;
            case 3:
                if (order ? nodes[j]->data.gpa < nodes[j + 1]->data.gpa
                          : nodes[j]->data.gpa > nodes[j + 1]->data.gpa)
                {
                    swap(nodes[j], nodes[j + 1]);
                }
                break;
            }
        }
    }
}

// SORT STUDENTS
// Student ID and GPA use Insertion Sort.
// Last Name uses Selection Sort.

void sortStudents(Node *head)
{
    vector<Node *> studentArray = createStudentArray(head);

    do
    {
        cout << "\n========================================\n";
        cout << "             SORT STUDENTS\n";
        cout << "========================================\n";

        int input;
        int orderInput = 1;
        if (studentArray.empty())
        {
            cout << "No student records found.\n";
            return;
        }

        displayTableHeader();
        for (Node *student : studentArray)
        {
            displayStudent(student->data);
        }

        cout << "----------------------------------------\n";
        cout << "What do you want it to sort by:" << endl;
        cout << "1. ID" << endl;
        cout << "2. Last Name" << endl;
        cout << "3. GPA" << endl;
        cout << "4. Go back to the Main Menu" << endl;
        cout << "Input: ";

        if (!(cin >> input))
        {
            clearInput();
            cout << "Invalid input, please try again\n";
            continue;
        }
        if (input != 4)
        {
            cout << "Which order do you want it: \n";
            cout << "1. Ascending (A-Z)\n";
            cout << "2. Descending (Z-A)\n";
            cout << "Input:";

            if (!(cin >> orderInput) || orderInput > 2 || orderInput < 1)
            {
                clearInput();
                cout << "Invalid input, please try again\n";
                continue;
            }
        }
        bool order = orderInput - 1;
        switch (input)
        {
        case 1:
            bubbleSort(studentArray, 1, order);
            break;
        case 2:
            bubbleSort(studentArray, 2, order);
            break;
        case 3:
            bubbleSort(studentArray, 3, order);
            break;
        case 4:
            return;
        default:
            clearInput();
            cout << "Invalid Input, try again.";
            break;
        }

    } while (true);
}

// STACK MENU

void stackOperations()
{
    int choice = 0;

    Student student;
    Student removedStudent;
    Student topStudent;

    do
    {
        cout << "\n========================================\n";
        cout << "             STACK OPERATIONS\n";
        cout << "========================================\n";

        cout << "1. Push / Add Deleted Student\n";
        cout << "2. Pop / Remove Recently Deleted\n";
        cout << "3. Peek / View Top\n";
        cout << "4. Display Stack\n";
        cout << "5. Back to Main Menu\n";

        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            clearInput();
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            // PUSH

            cout << "\nADD DELETED STUDENT\n";
            cout << "------------------------------\n";

            student.id = readStudentID();

            student.firstName =
                readName("Enter First Name: ", true);

            student.lastName =
                readName("Enter Last Name: ", false);

            student.gpa =
                readGPA("Enter GPA (1.00 - 5.00): ");

            deletedStack.push(student);

            cout << "\nStudent added to Deleted Stack.\n";

            deletedStack.displayStack();

            break;

        case 2:
            // POP

            removedStudent = deletedStack.pop();

            if (removedStudent.id != -1)
            {
                cout << "\nStudent removed from Deleted Stack:\n";

                cout << "Student: "
                     << removedStudent.id
                     << " - "
                     << removedStudent.firstName
                     << " "
                     << removedStudent.lastName
                     << endl;
            }

            break;

        case 3:
            // PEEK

            topStudent = deletedStack.peek();

            if (topStudent.id != -1)
            {
                cout << "\nTOP STUDENT\n";
                cout << "------------------------------\n";

                cout << "Student: "
                     << topStudent.id
                     << " - "
                     << topStudent.firstName
                     << " "
                     << topStudent.lastName
                     << endl;
            }

            break;

        case 4:
            // DISPLAY STACK

            deletedStack.displayStack();

            break;

        case 5:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);
}

// QUEUE MENU

void queueOperations()
{
    int choice = 0;

    do
    {
        cout << "\n========================================\n";
        cout << "             QUEUE OPERATIONS\n";
        cout << "========================================\n";

        cout << "1. Enqueue Student\n";
        cout << "2. Dequeue Student\n";
        cout << "3. Peek / View Front\n";
        cout << "4. Display Queue\n";
        cout << "5. Back to Main Menu\n";

        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            clearInput();
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            // TODO: write your code here (enqueue)
            {
                Student student;

                cout << "\nADD STUDENT TO QUEUE\n";

                student.id = readStudentID();

                student.firstName = readName("Enter First Name: ", true);

                student.lastName = readName("Enter Last Name: ", false);

                student.gpa = readGPA("Enter GPA(1.00-5.00)");

                serviceQueue.enqueue(student);

                cout << "\nStudent successfully added to Queue\n";
                break;
            }
        case 2:
            // TODO: write your code here (dequeue)
            {
                Student removedStudent = serviceQueue.dequeue();

                if (removedStudent.id != -1)
                {

                    cout << "Student removed from Queue:";

                    displayStudent(removedStudent);
                }

                break;
            }
        case 3:
            // TODO: write your code here (peek)
            {

                Student frontStudent = serviceQueue.peek();

                if (frontStudent.id != -1)
                {

                    cout << "STUDENT AT THE FRONT OF THE QUEUE";

                    displayStudent(frontStudent);
                }
                break;
            }
        case 4:
            // TODO: write your code here (display queue)
            {
                serviceQueue.displayQueue();

                break;
            }
            break;

        case 5:
            cout << "Returning to main menu...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);
};
// STUDENT STATISTICS


void studentStatistics(Node *head)
{

    int countStudents(Node *head);
    
    float calculateGPASum(Node *head);

    
    cout << "\n========================================\n";
    cout << "          STUDENT STATISTICS\n";
    cout << "========================================\n";

    
    if (head == nullptr)
    {
        cout << "No student records found.\n";
        return;
    }

    int total = countStudents(head);
    float average = calculateGPASum(head) / total;

    // 1.00 best grade
    Node *best = head;
    Node *worst = head;
    Node *current = head->next;

    while (current != nullptr)
    {
        if (current->data.gpa < best->data.gpa)
            best = current;

        if (current->data.gpa > worst->data.gpa)
            worst = current;

        current = current->next;
    }

    cout << fixed << setprecision(2);
    cout << "Total Students : " << total << endl;
    cout << "Average GPA    : " << average << endl;

    cout << "Highest GPA    : " << best->data.gpa << " - "
         << best->data.firstName << " " << best->data.lastName << endl;

    cout << "Lowest GPA     : " << worst->data.gpa << " - "
         << worst->data.firstName << " " << worst->data.lastName << endl;

    int menuChoice;
    cout << "\nInput 1 to go back to the Main Menu: ";

    while (!(cin >> menuChoice) || menuChoice != 1)
    {
        cout << "Invalid input. Input 1 to go back to the Main Menu: ";
        clearInput();
    }
}

// PART 6 - RECURSION

// RECURSIVE COUNT FUNCTION

int countStudents(Node *head)
{
    if (head == nullptr)
        return 0;

    return 1 + countStudents(head->next);
}

// RECURSIVE GPA SUM

float calculateGPASum(Node *head)
{
    if (head == nullptr)
        return 0;

    return head->data.gpa + calculateGPASum(head->next);
}
