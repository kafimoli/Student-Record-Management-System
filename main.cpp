#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>

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
    Node* next;
};


// GLOBAL VARIABLES

Node* head = nullptr;


// UTILITY FUNCTIONS

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// Removes spaces and tabs from the start and end of a string
string trimSpaces(const string& text)
{
    size_t first = text.find_first_not_of(" \t");

    if (first == string::npos)
    {
        return "";
    }

    size_t last = text.find_last_not_of(" \t");

    return text.substr(first, last - first + 1);
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


// Reads a name (a full line). The first letter is capitalized
// automatically. If allowMultipleWords is false, only one word
// is accepted (used for the last name).
string readName(const string& prompt, bool allowMultipleWords)
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

        if (length > 8 || length < 8)
        {
            cout << "Exceeds the number limit (8 digits) or Not enough. Try again.\n";
            continue;
        }

        return ID;
    }
}


// Reads a GPA from 1.00 to 5.00
float readGPA(const string& prompt)
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


// DISPLAY STUDENT

void displayStudent(const Student& student)
{
    cout << left
         << setw(10) << student.id
         << setw(18) << student.firstName
         << setw(18) << student.lastName
         << fixed << setprecision(2)
         << student.gpa << endl;
}


// Prints the table column headings and separator line
void displayTableHeader()
{
    cout << left
         << setw(10) << "ID"
         << setw(18) << "First Name"
         << setw(18) << "Last Name"
         << "GPA\n";

    cout << "----------------------------------------\n";
}


// PART 4 - STACK CLASS (RECENTLY DELETED STUDENTS)
// Kept as-is: Delete Student (option 5) depends on this class.

class StudentStack
{
private:
    struct StackNode
    {
        Student data;
        StackNode* next;
    };

    StackNode* top;

public:
    StudentStack() : top(nullptr) {}

    ~StudentStack()
    {
        clear();
    }

    StudentStack(const StudentStack&) = delete;
    StudentStack& operator=(const StudentStack&) = delete;

    void push(const Student& student)
    {
        StackNode* newNode = new StackNode;

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

        StackNode* temp = top;

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

        StackNode* current = top;

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
            StackNode* temp = top;

            top = top->next;

            delete temp;
        }
    }
};


// PART 5 - QUEUE CLASS (STUDENT SERVICE QUEUE)

class StudentQueue
{
private:
    struct QueueNode
    {
        Student data;
        QueueNode* next;
    };

    QueueNode* front;
    QueueNode* rear;

public:
    StudentQueue() : front(nullptr), rear(nullptr) {}

    ~StudentQueue()
    {
        clear();
    }

    StudentQueue(const StudentQueue&) = delete;
    StudentQueue& operator=(const StudentQueue&) = delete;

    void enqueue(const Student& student)
    {
        QueueNode* newNode = new QueueNode;

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

        QueueNode* temp = front;

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

        QueueNode* current = front;

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
            QueueNode* temp = front;

            front = front->next;

            delete temp;
        }

        rear = nullptr;
    }
};


// Objects of the two classes
StudentStack deletedStack;
StudentQueue serviceQueue;


// PART 1 - STUDENT RECORDS


// ADD STUDENT

void addStudent(Node*& head)
{
    Student student;

    cout << "\n========================================\n";
    cout << "             ADD STUDENT\n";
    cout << "========================================\n";

    student.id = readStudentID();

    // Check if ID already exists
    Node* check = head;

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
    Node* newNode = new Node;

    newNode->data = student;
    newNode->next = nullptr;

    // Insert at the end of the list
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
    }

    cout << "\nStudent added successfully!\n";

    // Input 1 to go back to the Main Menu
    int menuChoice;

    cout << "\nInput 1 to add new Student. ";
    cout << "\nInput 2 to go back to the Main Menu:\n";
    cin >> menuChoice;

    switch (menuChoice)
    {
    case 1:
        addStudent(head);
        break;
    case 2:
        while (!(menuChoice) ||
               (menuChoice != 2))
        {
            cout << "Invalid input";
            clearInput();
        }
        break;
    default:
        break;
    }
}


// DISPLAY ALL STUDENTS

void displayStudents(Node* head)
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

    Node* current = head;

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


// PART 2 - SEARCHING


// LINEAR SEARCH
// Checks the nodes one by one from the head until the ID is
// found. Works on unsorted data. Time: O(n).

Node* linearSearch(Node* head, int id)
{
    // TODO: write your code here

    return nullptr;
}


// BINARY SEARCH


Node* binarySearch(Node* head, int id)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    // Count students
    int size = 0;
    Node* current = head;

    while (current != nullptr)
    {
        size++;
        current = current->next;
    }

    // Copy the node pointers into a temporary array
    Node** nodes = new Node*[size];

    current = head;

    for (int i = 0; i < size; i++)
    {
        nodes[i] = current;
        current = current->next;
    }

    // Sort the pointers by ID (insertion sort)
    for (int i = 1; i < size; i++)
    {
        Node* key = nodes[i];
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
    Node* result = nullptr;

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


// SEARCH STUDENT

void searchStudent(Node* head)
{
    cout << "\n========================================\n";
    cout << "             SEARCH STUDENT\n";
    cout << "========================================\n";

    // TODO: write your code here
    // (ask for 1 = Linear Search / 2 = Binary Search,
    //  ask for the Student ID, call linearSearch() or
    //  binarySearch(), then display the result)
}


// UPDATE STUDENT

void updateStudent(Node* head)
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

    Node* studentNode = binarySearch(head, id);

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

    studentNode->data.gpa = readGPA("Enter new GPA (0.00 - 5.00): ");

    cout << "\nStudent updated successfully!\n";
}


// DELETE STUDENT

void deleteStudent(Node*& head)
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

    Node* current = head;
    Node* previous = nullptr;

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


// STACK MENU

void stackOperations()
{
    int choice = 0;

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
                // TODO: write your code here (push)
                break;

            case 2:
                // TODO: write your code here (pop)
                break;

            case 3:
                // TODO: write your code here (peek)
                break;

            case 4:
                // TODO: write your code here (display stack)
                break;

            case 5:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);
}


// PART 3 - SORTING


// COUNT STUDENTS ITERATIVELY

int getStudentCount(Node* head)
{
    // TODO: write your code here

    return 0;
}


// COPY LINKED LIST TO ARRAY

Student* createStudentArray(Node* head, int& size)
{
    // TODO: write your code here

    size = 0;
    return nullptr;
}


// DISPLAY ARRAY

void displayArray(Student arr[], int size)
{
    // TODO: write your code here
}


// COMPARE TWO STUDENTS
// sortChoice: 1 = ID, 2 = Last Name, 3 = GPA
// Returns true if a must come before b

bool comesBefore(const Student& a, const Student& b, int sortChoice)
{
    // TODO: write your code here

    return false;
}


// INSERTION SORT
// Takes one student at a time and inserts it into its correct
// place among the students already sorted on its left.

void insertionSort(Student arr[], int size, int sortChoice)
{
    // TODO: write your code here
}


// SELECTION SORT
// Finds the smallest remaining student and swaps it into the
// next position.

void selectionSort(Student arr[], int size, int sortChoice)
{
    // TODO: write your code here
}


// UPDATE LINKED LIST FROM ARRAY

void updateLinkedListFromArray(Node* head,
                               Student arr[],
                               int size)
{
    // TODO: write your code here
}


// SORT STUDENTS
// Student ID and GPA use Insertion Sort.
// Last Name uses Selection Sort.

void sortStudents(Node* head)
{
    cout << "\n========================================\n";
    cout << "             SORT STUDENTS\n";
    cout << "========================================\n";

    // TODO: write your code here
    // (ask what to sort by: 1 = ID, 2 = Last Name, 3 = GPA,
    //  build the array with createStudentArray(),
    //  sort it with insertionSort() or selectionSort(),
    //  display it with displayArray(),
    //  then copy it back with updateLinkedListFromArray())
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
                break;

            case 2:
                // TODO: write your code here (dequeue)
                break;

            case 3:
                // TODO: write your code here (peek)
                break;

            case 4:
                // TODO: write your code here (display queue)
                break;

            case 5:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);
}


// PART 6 - RECURSION

// RECURSIVE COUNT FUNCTION

int countStudents(Node* head)
{
    // TODO: write your code here

    return 0;
}


// RECURSIVE GPA SUM

float calculateGPASum(Node* head)
{
    // TODO: write your code here

    return 0;
}


// STUDENT STATISTICS

void studentStatistics(Node* head)
{
    cout << "\n========================================\n";
    cout << "          STUDENT STATISTICS\n";
    cout << "========================================\n";

    // TODO: write your code here
    // (use countStudents() and calculateGPASum() to get the
    //  total and average GPA, then find the highest and lowest
    //  GPA and display everything)
}


// CLEANUP FUNCTION

void deleteAllStudents(Node*& head)
{
    while (head != nullptr)
    {
        Node* temp = head;

        head = head->next;

        delete temp;
    }
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

        if (!(cin >> choice))
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


// MAIN

int main()
{
    cout << "========================================\n";
    cout << "     STUDENT RECORD MANAGEMENT SYSTEM\n";
    cout << "========================================\n";

    cout << "Welcome!\n";

    mainMenu();

    // Free dynamically allocated memory
    deleteAllStudents(head);

    deletedStack.clear();

    serviceQueue.clear();

    cout << "\nProgram terminated safely.\n";

    return 0;
}
