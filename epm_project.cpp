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
// Globals
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
// Function Declarations
// =======================
void showMainMenu();
void handleAdmin();
void handleEmployee();
int getValidInt();
long long getValidId();

// =======================
// MAIN
// =======================
int main() {

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
// MAIN MENU
// =======================
void showMainMenu() {
    cout << "\n===== Employee Payroll System =====\n";
    cout << "1. Admin Login\n";
    cout << "2. Employee Login\n";
    cout << "3. Exit\n";
    cout << "Choose: ";
}

// =======================
// ADMIN HANDLER
// =======================
void handleAdmin() {

    if (!adminLogin()) {
        cout << "Invalid username or password\n";
        return;
    }

    cout << "Login Successful\n";

    int choice;

    while (true) {
        cout << "\n===== ADMIN DASHBOARD =====\n";
        cout << "1. Add Employee\n";
        cout << "2. Update Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Record Attendance\n";
        cout << "5. Calculate Salary\n";
        cout << "6. Logout\n";
        cout << "Choose: ";

        choice = getValidInt();

        switch (choice) {

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
            long long id;
            cout << "Enter Employee ID: ";
            id = getValidId();
            calculateSalary(id);
            break;
        }

        case 6:
            cout << "Logging out...\n";
            isAdminLoggedIn = false;
            currentAdminIndex = -1;
            return;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

// =======================
// EMPLOYEE HANDLER
// =======================
void handleEmployee() {

    int chance = 3;
    bool loggedIn = false;

    while (chance > 0) {
        if (employeeLogin()) {
            loggedIn = true;
            cout << "Login successful\n";
            break;
        }
        chance--;
        cout << "Invalid credentials (" << chance << " attempts left)\n";
    }

    if (!loggedIn) {
        cout << "Access denied\n";
        return;
    }

    int choice;

    while (true) {
        cout << "\n===== EMPLOYEE DASHBOARD =====\n";
        cout << "1. View Personal Info\n";
        cout << "2. View Salary\n";
        cout << "3. View Attendance\n";
        cout << "4. Logout\n";
        cout << "Choose: ";

        choice = getValidInt();

        switch (choice) {

        case 1:
            viewPersonalInfo();
            break;

        case 2:
            viewSalary();
            break;

        case 3:
            viewAttendance();
            break;

        case 4:
            cout << "Logging out...\n";
            isEmployeeLoggedIn = false;
            currentEmployeeIndex = -1;
            return;

        default:
            cout << "Invalid choice!\n";
        }
    }
}

// =======================
// LOGIN SYSTEM
// =======================
bool adminLogin() {

    string user, pass;

    cout << "Username: ";
    getline(cin, user);

    cout << "Password: ";
    getline(cin, pass);

    for (int i = 0; i < adminCount; i++) {
        if (admins[i].username == user &&
            admins[i].password == pass) {

            currentAdminIndex = i;
            isAdminLoggedIn = true;
            return true;
        }
    }
    return false;
}

bool employeeLogin() {

    string user, pass;

    cout << "Username: ";
    getline(cin, user);

    cout << "Password: ";
    getline(cin, pass);

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].username == user &&
            employees[i].password == pass) {

            currentEmployeeIndex = i;
            isEmployeeLoggedIn = true;
            return true;
        }
    }
    return false;
}

// =======================
// VIEW FUNCTIONS
// =======================
void viewPersonalInfo() {

    if (!isEmployeeLoggedIn) {
        cout << "Access denied!\n";
        return;
    }

    cout << "\n===== PROFILE =====\n";
    cout << "Name: " << employees[currentEmployeeIndex].name << "\n";
    cout << "ID: " << employees[currentEmployeeIndex].employeeID << "\n";
    cout << "Age: " << employees[currentEmployeeIndex].age << "\n";
    cout << "Phone: " << employees[currentEmployeeIndex].phone << "\n";
    cout << "Role: " << employees[currentEmployeeIndex].role << "\n";
}

void viewSalary() {

    if (!isEmployeeLoggedIn) {
        cout << "Access denied!\n";
        return;
    }

    cout << "\n===== SALARY =====\n";
    cout << "ID: " << employees[currentEmployeeIndex].employeeID << "\n";
    cout << "Name: " << employees[currentEmployeeIndex].name << "\n";
    cout << "Basic: " << employees[currentEmployeeIndex].basicSalary << "\n";
    cout << "Bonus: " << employees[currentEmployeeIndex].bonus << "\n";
    cout << "Overtime: " << employees[currentEmployeeIndex].overtime << "\n";
    cout << "Tax: " << employees[currentEmployeeIndex].tax << "\n";
    cout << "Net: " << employees[currentEmployeeIndex].netSalary << "\n";
}

void viewAttendance() {

    if (!isEmployeeLoggedIn) {
        cout << "Access denied!\n";
        return;
    }

    cout << "\n===== ATTENDANCE =====\n";

    long long id = employees[currentEmployeeIndex].employeeID;

    bool found = false;

    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == id) {

            cout << "Month: " << attendanceRecords[i].month << "\n";
            cout << "Present: " << attendanceRecords[i].daysPresent << "\n";
            cout << "Absent: " << attendanceRecords[i].daysAbsent << "\n";

            found = true;
            break;
        }
    }

    if (!found)
        cout << "No attendance record found\n";
}

// =======================
// ADMIN FUNCTIONS
// =======================
void recordAttendance() {

    if (!isAdminLoggedIn) return;

    long long id;
    cout << "Enter Employee ID: ";
    id = getValidId();

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == id) {

            attendanceRecords[attendanceCount].employeeID = id;

            cout << "Month: ";
            cin.ignore();
            getline(cin, attendanceRecords[attendanceCount].month);

            cout << "Present: ";
            cin >> attendanceRecords[attendanceCount].daysPresent;

            cout << "Absent: ";
            cin >> attendanceRecords[attendanceCount].daysAbsent;

            attendanceCount++;
            saveAttendance();

            cout << "Saved successfully\n";
            return;
        }
    }

    cout << "Employee not found\n";
}

void deleteEmployee() {

    if (!isAdminLoggedIn) return;

    long long id;
    cout << "Enter Employee ID: ";
    id = getValidId();

    for (int i = 0; i < employeeCount; i++) {

        if (employees[i].employeeID == id) {

            for (int j = i; j < employeeCount - 1; j++)
                employees[j] = employees[j + 1];

            employeeCount--;
            saveEmployees();

            cout << "Deleted successfully\n";
            return;
        }
    }

    cout << "Employee not found\n";
}

// =======================
// INPUT VALIDATION
// =======================
int getValidInt() {

    int x;

    while (true) {
        cin >> x;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input: ";
    }
}

long long getValidId() {

    long long x;

    while (true) {
        cin >> x;

        if (!cin.fail() && x > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID: ";
    }
}


// =======================
// EMPLOYEES
// =======================
void loadEmployees() {

    ifstream in("employees.txt");
    if (!in) return;

    employeeCount = 0;

    while (employeeCount < MAX_EMPLOYEES) {

        Employee& e = employees[employeeCount];

        if (!(in >> e.employeeID)) break;
        in.ignore();

        getline(in, e.name, '|');
        in >> e.basicSalary;
        in.ignore();

        in >> e.age;
        in.ignore();

        getline(in, e.phone, '|');
        getline(in, e.role, '|');

        in >> e.bonus;
        in.ignore();

        in >> e.overtime;
        in.ignore();

        in >> e.tax;
        in.ignore();

        in >> e.netSalary;
        in.ignore();

        in >> e.TotalHoursWorked;
        in.ignore();

        getline(in, e.password);

        employeeCount++;
    }

    in.close();
}

void saveEmployees() {

    ofstream out("employees.txt");

    for (int i = 0; i < employeeCount; i++) {
        out << employees[i].employeeID << "|"
            << employees[i].name << "|"
            << employees[i].basicSalary << "|"
            << employees[i].age << "|"
            << employees[i].phone << "|"
            << employees[i].role << "|"
            << employees[i].bonus << "|"
            << employees[i].overtime << "|"
            << employees[i].tax << "|"
            << employees[i].netSalary << "|"
            << employees[i].TotalHoursWorked << "|"
            << employees[i].password << "\n";
    }

    out.close();
}

// =======================
// ADMINS
// =======================
void loadAdmins() {

    ifstream in("admins.txt");
    if (!in) return;

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
        out << admins[i].adminID << "|"
            << admins[i].username << "|"
            << admins[i].password << "\n";
    }

    out.close();
}

// =======================
// ATTENDANCE
// =======================
void loadAttendance() {

    ifstream in("attendance.txt");
    if (!in) return;

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
        out << attendanceRecords[i].employeeID << "|"
            << attendanceRecords[i].month << "|"
            << attendanceRecords[i].daysPresent << "|"
            << attendanceRecords[i].daysAbsent << "\n";
    }

    out.close();
}
