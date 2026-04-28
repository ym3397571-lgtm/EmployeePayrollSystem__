#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

// =======================
// Headers
// =======================
#include "employee.h"
#include "admin.h"
#include "data.h"
#include "storage.h"

// =======================
// Function Declarations
// =======================
void showMainMenu();
void handleAdmin();
void handleEmployee();
int getValidInt();
long long getValidId();

// =======================
// Global Variables Definition
// =======================
Employee employees[MAX_EMPLOYEES];
Attendance attendanceRecords[MAX_ATTENDANCE];
AdminAccount admins[MAX_ADMINS];

int employeeCount = 0;
int attendanceCount = 0;
int adminCount = 0;
int currentEmployeeIndex = -1;
int currentAdminIndex = -1;

bool isAdminLoggedIn = false;
bool isEmployeeLoggedIn = false;

// =======================
// MAIN
// =======================
int main() {



    // load data
    loadEmployees();
    loadAdmins();
    loadAttendance();
    int choice;

    while (true) {
        showMainMenu();
        choice = getValidInt();

        switch (choice) {
        case 1:
            handleAdmin();
            break;

        case 2:
            handleEmployee();
            break;

        case 3:
            cout << "Exiting system...\n";

            // save data before exit
            saveEmployees();
            saveAdmins();
            saveAttendance();

            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

// =======================
// Function Definitions
// =======================


void showMainMenu() {
    cout << "\n===== Employee Payroll Management System =====\n";
    cout << "1. Admin Login\n";
    cout << "2. Employee Login\n";
    cout << "3. Exit\n";
    cout << "Choose: ";
}  // youssef 


void handleAdmin() {
    if (adminLogin()) {
        cout << "\n========================================\n";
        cout << "           Login Successful\n";
        cout << "========================================\n";
        int choice_admin;
        long long  empId;
        while (true) {
            cout << "\n===== Admin Menu =====\n";
            cout << "1. Add Employee\n";
            cout << "2. Update Employee\n";
            cout << "3. Delete Employee\n";
            cout << "4. Record Attendance\n";
            cout << "5. Calculate Salary\n";
            cout << "6. Logout\n";
            cout << "Choose: ";
            choice_admin = getValidInt();
            switch (choice_admin) {
            case 1:
                addEmployee();
                break;
            case 2:
                updateEmployee();
                break;
            case 3:
                deleteEmployee();
                break;
            case 4:
                recordAttendance();
                break;
            case 5: {
                cout << "Enter Employee ID to calculate salary: ";
                empId = getValidId();
                calculateSalary(empId);
                break;
            }
            case 6:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }


    }
    else {
        cout << "\nError: Invalid username or password\n";
    }
}


void handleEmployee() {

    int chance = 3;
    bool loggedIn = false;

    while (chance > 0) {
        if (employeeLogin()) {
            loggedIn = true;
            break;
        }

        chance--;
        cout << "Invalid credentials (" << chance << " attempts left)\n";
    }

    if (!loggedIn) {
        cout << "Access denied!\n";
        return;
    }

    int choice;

    while (true) {
        cout << "\n===== EMPLOYEE MENU =====\n";
        cout << "1. View Personal Information\n";
        cout << "2. View Salary Information\n";
        cout << "3. View Attendance Record\n";
        cout << "4. Logout\n";
        cout << "Choose: ";
        choice = getValidInt();

        switch (choice) {
        case 1:
            viewPersonalInfo();
            break;

        case 2:
            calculateSalary(employees[currentEmployeeIndex].employeeID);
            viewSalary();
            break;

        case 3:
            viewAttendance();
            break;

        case 4:
            cout << "Logging out...\n";
            return;

        default:
            cout << "Invalid choice!\n";
        }
    }
}



// =======================
// LOGIN STUBS
// =======================

// Fixed signature: called without arguments in code, so read credentials inside function
bool adminLogin() {
    string adminname;
    string adminpass;
    cout << "Enter Username: ";
    getline(cin >> ws, adminname);
    cout << "Enter Password: ";
    getline(cin, adminpass);

    for (int i = 0; i < adminCount; i++) {
        if (admins[i].username == adminname && admins[i].password == adminpass) {
            currentAdminIndex = i;
            isAdminLoggedIn = true;
            return true;
        }
    }
    return false;
} // محمود

bool employeeLogin()
{
    string Username;
    string Password;

    cout << "Enter your username: ";
    getline(cin >> ws, Username);
    cout << "Enter your password: ";
    getline(cin, Password);

    for (int i = 0; i < employeeCount; i++)
    {
        if (employees[i].username == Username && employees[i].password == Password)
        {
            currentEmployeeIndex = i;
            isEmployeeLoggedIn = true;
            cout << "Login successful\n";
            return true;

        }


    }
    cout << "Login failed\n";
    return false;
} // ahmed 

// =======================
// LOAD / SAVE STUBS | yossef 
// =======================

void loadEmployees() {
    ifstream in("employees.txt");

    if (!in) {
        cout << "ERROR: employees.txt not found in execution folder\n";
        return;
    }

    employeeCount = 0;

    while (employeeCount < MAX_EMPLOYEES) {
        Employee& e = employees[employeeCount];

        // 1. Read ID
        if (!(in >> e.employeeID)) break;
        in.ignore(); // consume '|'

        // 2 & 3. Read Name and Username
        getline(in, e.name, '|');
        getline(in, e.username, '|');

        // 4. Read Age
        in >> e.age;
        in.ignore(); // consume '|'

        // 5 & 6. Read Phone and Role
        getline(in, e.phone, '|');
        getline(in, e.role, '|');

        // 7 to 11. Read Salary & Financials
        in >> e.basicSalary;
        in.ignore();

        in >> e.bonus;
        in.ignore();

        in >> e.overtime;
        in.ignore();

        in >> e.tax;
        in.ignore();

        in >> e.netSalary;
        in.ignore();

        // 12. Read Password (until the next '|')
        getline(in, e.password, '|');

        // 13 & 14. Read Hours
        in >> e.TotalHoursWorked;
        in.ignore();

        in >> e.WorkHoursPerMonth;

        // Clear the leftover newline character before the next loop
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        employeeCount++;
    }

    in.close();
    cout << "Loaded " << employeeCount << " employees successfully.\n";
}


void saveEmployees() {
    ofstream out("employees.txt");

    if (!out.is_open()) {
        cout << "Error: Could not open employees.txt for writing!" << endl;
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        out << employees[i].employeeID << "|"
            << employees[i].name << "|"
            << employees[i].username << "|"
            << employees[i].age << "|"
            << employees[i].phone << "|"
            << employees[i].role << "|"
            << employees[i].basicSalary << "|"
            << employees[i].bonus << "|"
            << employees[i].overtime << "|"
            << employees[i].tax << "|"
            << employees[i].netSalary << "|"
            << employees[i].password << "|"
            << employees[i].TotalHoursWorked << "|"
            << employees[i].WorkHoursPerMonth << endl; // Added missing variable
    }
    out.close();
    cout << "Successfully saved " << employeeCount << " employees to file." << endl;
}

void loadAdmins() {
    ifstream in("admins.txt");
    if (!in) {
        cout << "no file found\n";
        return;
    }
    adminCount = 0;

    while (adminCount < MAX_ADMINS) {

        AdminAccount& a = admins[adminCount];
        if (!(in >> a.adminID)) break;
        in.ignore();
        getline(in, a.username, '|');
        getline(in, a.password);
        adminCount++;
    }
    in.close();
}

void saveAdmins() {
    ofstream out("admins.txt");
    for (int i = 0; i < adminCount; i++) {
        out << admins[i].adminID << "|" << admins[i].username << "|" << admins[i].password << endl;
    }
    out.close();
}

void loadAttendance() {
    ifstream in("attendance.txt");
    if (!in) {
        cout << "no file found" << endl;
        return;
    }
    attendanceCount = 0;
    while (attendanceCount < MAX_ATTENDANCE) {
        Attendance& a = attendanceRecords[attendanceCount];
        if (!(in >> a.employeeID)) break;
        in.ignore();
        getline(in, a.month, '|');
        in >> a.daysPresent;
        in.ignore();
        in >> a.daysAbsent;
        in.ignore();
        attendanceCount++;
    }
    in.close();
}

void saveAttendance() {
    ofstream out("attendance.txt");
    for (int i = 0; i < attendanceCount; i++) {
        out << attendanceRecords[i].employeeID << "|" << attendanceRecords[i].month << "|"
            << attendanceRecords[i].daysPresent << "|" << attendanceRecords[i].daysAbsent << endl;
    }
    out.close();
}

//  functions 

void viewPersonalInfo()
{

    cout << "\n========================================\n";
    cout << "           EMPLOYEE PROFILE             \n";
    cout << "========================================\n";
    cout << "Employee ID: " << employees[currentEmployeeIndex].employeeID << "\n";
    cout << "Name:     " << employees[currentEmployeeIndex].name << endl;
    cout << "ID:       " << employees[currentEmployeeIndex].employeeID << endl;
    cout << "Age:      " << employees[currentEmployeeIndex].age << endl;
    cout << "Phone:    " << employees[currentEmployeeIndex].phone << endl;
    cout << "Role:     " << employees[currentEmployeeIndex].role << endl;
    cout << "========================================\n";
} //  ahmed

void viewSalary() {
    cout << "\n========================================\n";
    cout << "          View Salary Information\n";
    cout << "========================================\n";
    cout << "Employee ID: " << employees[currentEmployeeIndex].employeeID << "\n";
    cout << "Name: " << employees[currentEmployeeIndex].name << "\n";
    cout << "Basic Salary: " << fixed << setprecision(2) << employees[currentEmployeeIndex].basicSalary << "\n";
    cout << "Bonus: " << fixed << setprecision(2) << employees[currentEmployeeIndex].bonus << "\n";
    cout << "Overtime: " << fixed << setprecision(2) << employees[currentEmployeeIndex].overtime << "\n";
    cout << "Tax: " << fixed << setprecision(2) << employees[currentEmployeeIndex].tax << "\n";
    cout << "Net Salary: " << fixed << setprecision(2) << employees[currentEmployeeIndex].netSalary << "\n";
    cout << "========================================\n";
} // mostafa elhadidy

void viewAttendance() {
    cout << "\n========================================\n";
    cout << "           Attendance Record\n";
    cout << "========================================\n";

    cout << "\n========================================\n";
    cout << "Employee ID: " << employees[currentEmployeeIndex].employeeID << "\n";

    bool found = false;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == employees[currentEmployeeIndex].employeeID) {
            cout << "Month: " << attendanceRecords[i].month << "\n";
            cout << "Days Present: " << attendanceRecords[i].daysPresent << "\n";
            cout << "Days Absent: " << attendanceRecords[i].daysAbsent << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No attendance records found for this employee\n";
    }
    cout << "========================================\n";
}



void addEmployee() {

    cout << "\n--- Add New Employee ---\n";
    // Check if employee list is full
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee list is full!\n";
        return;
    }
    // Create a new employee object and get details from user
    Employee e;

    cout << "Enter ID: ";
    cin >> e.employeeID;

    // Check duplicate ID
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == e.employeeID) {
            cout << "ID already exists!\n";
            return;
        }

    }
    cout << "User Name: ";
    cin >> e.username;
    cout << "Enter Name: ";
    cin >> e.name;
    cout << "Phone: ";
    cin >> e.phone;
    cout << "Role: ";
    cin >> e.role;  
    cout << "Age: ";
	cin >> e.age;
    cout << "Enter New Password: ";
	cin >> e.password;
    cout << "Enter Salary: ";
    cin >> e.basicSalary;

    employees[employeeCount] = e;
    employeeCount++;

    cout << "Employee added successfully!\n";
}// mostafa2

void updateEmployee() {

    int id;

    cout << "\n--- Update Employee ---\n";

    cout << "Enter Employee ID: ";

    id = getValidId();

    for (int i = 0; i < employeeCount; i++) {

        if (employees[i].employeeID == id) {

            cout << "Current Name: " << employees[i].name << endl;

            cout << "Current Salary: " << employees[i].basicSalary << endl;

            cout << "Enter New Name: ";

            cin >> employees[i].name;

            cout << "Enter New Salary: ";

            cin >> employees[i].basicSalary;

            cout << "Employee updated successfully!\n";

            return;

        }

    }

    cout << "Employee not found!\n";

}// mostafa2 

void calculateSalary(long long empId)
{
    int index = -1;

    // 1. Search for the employee's actual position (index) in the array
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == empId) {
            index = i;
            break;
        }
    }

    // 2. If the loop finishes and index is still -1, the ID doesn't exist
    if (index == -1) {
        cout << "Error: Employee with ID " << empId << " not found.\n";
        return;
    }

    // 3. Safety Check: Prevent Division by Zero crash
    if (employees[index].WorkHoursPerMonth <= 0) {
        cout << "Error: WorkHoursPerMonth must be greater than 0 to calculate salary.\n";
        return;
    }

    // 4. Calculate everything using the correct 'index'
    employees[index].overtime = employees[index].TotalHoursWorked - employees[index].WorkHoursPerMonth;

    // Optional: Prevent negative overtime if they worked less than the required hours
    if (employees[index].overtime < 0) {
        employees[index].overtime = 0;
    }

    employees[index].bonus = (employees[index].basicSalary / employees[index].WorkHoursPerMonth) * employees[index].overtime;

    // Assuming TaxRate is a global variable defined in one of your headers (like data.h)
    employees[index].tax = (employees[index].basicSalary * TaxRate);

    employees[index].netSalary = (employees[index].basicSalary + employees[index].bonus) - employees[index].tax;

    cout << "Salary calculated successfully for Employee ID " << empId << ".\n";
}
// eyad 

void recordAttendance() {
    long long id;
    bool found = false;
    cout << "\n========================================\n";
    cout << "           Record Attendance\n";
    cout << "========================================\n";
    cout << "Enter Employee ID: ";
    cin >> id;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == id) {
            found = true;
            break;
        }
    }

    if (found) {
        if (attendanceCount < MAX_ATTENDANCE) {
            attendanceRecords[attendanceCount].employeeID = id;
            cout << "Enter Month: ";
            cin.ignore();
            getline(cin, attendanceRecords[attendanceCount].month);
            cout << "Enter Days Present: ";
            cin >> attendanceRecords[attendanceCount].daysPresent;
            cout << "Enter Days Absent: ";
            cin >> attendanceRecords[attendanceCount].daysAbsent;
            attendanceCount++;
            cout << "Attendance recorded successfully.\n";
            cout << "========================================\n";
            saveAttendance();
        }
        else {
            cout << "Error: Attendance records are full.\n";
            cout << "========================================\n";
        }
    }
    else {
        cout << "Error: Employee ID " << id << " not found.\n";
        cout << "========================================\n";
    }
}

void deleteEmployee() {
    long long id;
    bool found = false;
    cout << "\n========================================\n";
    cout << "           Delete Employee\n";
    cout << "========================================\n";
    cout << "Enter Employee ID: ";
    cin >> id;

    for (int j = 0; j < employeeCount; j++) {
        if (employees[j].employeeID == id) {
            found = true;
            for (int k = j; k < employeeCount - 1; k++) {
                employees[k] = employees[k + 1];
            }
            cout << "Employee with ID " << id << " deleted successfully.\n";
            cout << "========================================\n";
            employeeCount--;
            saveEmployees();
            break;
        }
    }

    if (!found) {
        cout << "Error: Employee ID " << id << " not found.\n";
        cout << "========================================\n";
    }
}

int getValidInt() {
    int value;

    while (true) {
        cin >> value;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }



}

long long  getValidId() {
    long long id;

    while (true) {
        cin >> id;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return id;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }
}
