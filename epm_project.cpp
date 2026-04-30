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
        cout << "           Welcome, " << admins[currentAdminIndex].name << "!\n";
        cout << "========================================\n";
        int choice_admin;
        long long  empId;
        while (true) {
            cout << "\n===== Admin Menu =====\n";
            cout << "1. Add Employee\n";
            cout << "2. Update Employee\n";
            cout << "3. Delete Employee\n";
            cout << "4. Record Attendance\n";
            cout << "1. Add/Update Employee\n";
            cout << "2. Delete Employee\n";
            cout << "3. Record/Update Attendance\n";
            cout << "4. Delete Attendance\n";
            cout << "5. Calculate Salary\n";
<<<<<<< HEAD
            cout << "6. Search Employee\n";
            cout << "7. Logout\n";
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
<<<<<<< HEAD

=======
            case 4:
                deleteAttendance();
                break;
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
            case 5: {
                cout << "Enter Employee ID to calculate salary: ";
                empId = getValidId();
                calculateSalary(empId);
                break;
            }
<<<<<<< HEAD
            case 6: {
                cout << "Enter Employee ID to search: ";
                empId = getValidId();
                searchEmployee(empId);
                break;
            }
=======
            case 6:
                viewAllEmployeesData();
                break;
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
            case 7:
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
            cout << "\n========================================\n";
            cout << "           Login Successful\n";
            cout << "           Welcome, " << employees[currentEmployeeIndex].name << "!\n";
            cout << "========================================\n";
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
        cout << "\n===== Employee Menu =====\n";
        cout << "1. View Personal Information\n";
        cout << "2. View Salary Information\n";
        cout << "3. View Attendance Record\n";
        cout << "4. Logout\n";
        cout << "Choose: ";
        choice = getValidInt();

        switch (choice) {
        case 1:
            viewPersonalInfo(currentEmployeeIndex);
            break;

        case 2:
            calculateSalary(employees[currentEmployeeIndex].employeeID);
            viewSalary(currentEmployeeIndex);
            break;

        case 3:
            viewAttendance(currentEmployeeIndex);
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
            return true;

        }


    }
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
        getline(in, a.name, '|');
        getline(in, a.username, '|');
        getline(in, a.password);
        adminCount++;
    }
    in.close();
}

void saveAdmins() {
    ofstream out("admins.txt");
    for (int i = 0; i < adminCount; i++) {
        out << admins[i].adminID << "|" << admins[i].name << "|" << admins[i].username << "|" << admins[i].password << endl;
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
        in >> a.month;
        in.ignore();
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

void viewPersonalInfo(int index)
{

    cout << "\n========================================\n";
    cout << "           EMPLOYEE PROFILE             \n";
    cout << "========================================\n";
<<<<<<< HEAD
    cout << "Employee ID: " << employees[index].employeeID << "\n";
    cout << "Name:     " << employees[index].name << endl;
    cout << "ID:       " << employees[index].employeeID << endl;
    cout << "Age:      " << employees[index].age << endl;
    cout << "Phone:    " << employees[index].phone << endl;
    cout << "Role:     " << employees[index].role << endl;
    cout << "========================================\n";
} //  ahmed

void viewSalary(int index) {
    cout << "\n========================================\n";
    cout << "          View Salary Information\n";
    cout << "========================================\n";
    cout << "Employee ID: " << employees[index].employeeID << "\n";
    cout << "Name: " << employees[index].name << "\n";
    cout << "Basic Salary: " << fixed << setprecision(2) << employees[index].basicSalary << "\n";
    cout << "Bonus: " << fixed << setprecision(2) << employees[index].bonus << "\n";
    cout << "Overtime: " << fixed << setprecision(2) << employees[index].overtime << "\n";
    cout << "Tax: " << fixed << setprecision(2) << employees[index].tax << "\n";
    cout << "Net Salary: " << fixed << setprecision(2) << employees[index].netSalary << "\n";
    cout << "========================================\n";
} // mostafa elhadidy

void viewAttendance(int index) {
    cout << "\n========================================\n";
<<<<<<< HEAD
    cout << "        Attendance Records\n";
    cout << "========================================\n";

    cout << "Employee ID: " << employees[index].employeeID << "\n";
    cout << "Name: " << employees[index].name << "\n";
=======
    cout << "           Attendance Records\n";
    cout << "========================================\n";

    cout << "\n========================================\n";
    cout << "Employee ID: " << employees[currentEmployeeIndex].employeeID << "\n";
    cout << "Name: " << employees[currentEmployeeIndex].name << "\n";
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0

    bool found = false;

    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == employees[index].employeeID) {
            cout << "Month: " << attendanceRecords[i].month << "\n";
            cout << "Days Present: " << attendanceRecords[i].daysPresent << "\n";
            cout << "Days Absent: " << attendanceRecords[i].daysAbsent << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No attendance records found\n";
    }
}



void addEmployee() {
    cout << "\n--- Add New Employee ---\n";
    // Check if employee list is full
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee list is full!\n";
        return;
    }

    Employee e;
    cout << "Enter the following details:\n";

    cout << "ID: ";
    e.employeeID = getValidId();

    // Check duplicate ID
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == e.employeeID) {
            cout << "ID already exists!\n";
            updateEmployee(e.employeeID);
        }
    }
    cout << "Username: ";
    getline(cin >> ws, e.username);

    cout << "Password: ";
    getline(cin, e.password);

    cout << "Name: ";
    getline(cin, e.name);

    cout << "Phone: ";
    getline(cin, e.phone);

    cout << "Role: ";
    getline(cin, e.role);

    cout << "Age: ";
    e.age = getValidInt();

    cout << "Salary: ";
    while (true) {
        cin >> e.basicSalary;
        if (!cin.fail() && e.basicSalary >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a valid salary amount: ";
    }

    employees[employeeCount] = e;
    employeeCount++;

    cout << "Employee added successfully!\n";
    saveEmployees();
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

            getline(cin >> ws, employees[i].name);

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
    int index = findEmployeeIndex(empId);


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
    bool employeeExists = false;
<<<<<<< HEAD

    cout << "\n========================================\n";
    cout << "      Record Attendance\n";
    cout << "========================================\n";

=======

    cout << "\n========================================\n";
    cout << "           Record Attendance\n";
    cout << "========================================\n";

    // 1. Get and Validate Employee ID
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
    while (true) {
        cout << "Enter Employee ID: ";
        id = getValidId();

        employeeExists = false;
        for (int i = 0; i < employeeCount; i++) {
            if (employees[i].employeeID == id) {
                employeeExists = true;
                break;
            }
        }

        if (employeeExists) {
            break;
        }
        else {
            cout << "ID not found! Please enter again.\n\n";
        }
    }

<<<<<<< HEAD
    int month;
    while (true) {
        cout << "Enter Month (1-12): ";
        month = getValidInt();

        if (month >= 1 && month <= 12) {
            break;
        }
        else {
            cout << "Error: Month must be between 1 and 12. Try again: ";
        }
    }

    // --- Check for Existing Record ---
    int recordIndex = -1;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == id && attendanceRecords[i].month == month) {
=======
    // 2. Check for an Existing Record using ONLY the ID
    int recordIndex = -1;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == id) {
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
            recordIndex = i;
            break;
        }
    }

    if (recordIndex != -1) {
<<<<<<< HEAD
        cout << "\nRecord found for Month " << month << "! Updating...\n";
        cout << "Current Days Present: " << attendanceRecords[recordIndex].daysPresent << "\n";
        cout << "Current Days Absent: " << attendanceRecords[recordIndex].daysAbsent << "\n";

        cout << "Enter New Days Present: ";
        attendanceRecords[recordIndex].daysPresent = getValidInt();

        cout << "Enter New Days Absent: ";
        attendanceRecords[recordIndex].daysAbsent = getValidInt();

        cout << "\nAttendance updated successfully!\n";
    }
    else {

=======
        // --- RECORD EXISTS: Call Update Flow ---
		cout << "\nExisting attendance record found for this ID. Redirecting to update...\n";
        updateAttendance(id);
    }
    else {
        // --- NO RECORD EXISTS: Creation Flow ---
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
        if (attendanceCount >= MAX_ATTENDANCE) {
            cout << "Error: Attendance records are full.\n";
            cout << "========================================\n";
            return;
        }

<<<<<<< HEAD
=======
        cout << "\nNo existing record found for this ID. Creating a new one.\n";

        int month;
        while (true) {
            cout << "Enter Month (1-12): ";
            month = getValidInt();

            if (month >= 1 && month <= 12) {
                break;
            }
            else {
                cout << "Error: Month must be between 1 and 12. Try again: ";
            }
        }

>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
        attendanceRecords[attendanceCount].employeeID = id;
        attendanceRecords[attendanceCount].month = month;

        cout << "Enter Days Present: ";
        attendanceRecords[attendanceCount].daysPresent = getValidInt();

        cout << "Enter Days Absent: ";
        attendanceRecords[attendanceCount].daysAbsent = getValidInt();

        attendanceCount++;
        cout << "\nAttendance recorded successfully.\n";
<<<<<<< HEAD
    }

    cout << "========================================\n";
    saveAttendance();
}//abdelrahman


void deleteAttendance() {
    long long id;
=======
        cout << "========================================\n";
        saveAttendance();
    }
}//abdelrahman

void updateAttendance(long long empId) {
    int month;
    bool found = false;

    cout << "\n========================================\n";
    cout << "           Delete Attendance\n";
    cout << "========================================\n";

    while (true) {
        cout << "Enter Employee ID: ";
        id = getValidId();

        bool idExists = false;
        for (int i = 0; i < attendanceCount; i++) {
            if (attendanceRecords[i].employeeID == id) {
                idExists = true;
                break;
            }
        }

        if (idExists) {
            break;
        }
        else {
            cout << "ID not found! Please enter again.\n\n";
        }
    }

    cout << "Enter Month (1-12) to delete: ";
=======
    cout << "           Update Attendance\n";
    cout << "========================================\n";

    // --- ID Validation Loop Removed (Handled in recordAttendance) ---

    // --- Month Validation Loop ---
    cout << "Enter Month (1-12) to update: ";
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
    while (true) {
        month = getValidInt();
        if (month >= 1 && month <= 12) {
            break;
        }
        else {
            cout << "Error: Month must be between 1 and 12. Try again: ";
        }
    }

<<<<<<< HEAD
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == id && attendanceRecords[i].month == month) {
            found = true;

            // Shift elements to the left to overwrite the deleted record
            for (int j = i; j < attendanceCount - 1; j++) {
                attendanceRecords[j] = attendanceRecords[j + 1];
            }

            attendanceCount--;

            cout << "Attendance record deleted successfully.\n";
=======
    // --- Update Process ---
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == empId && attendanceRecords[i].month == month) {
            found = true;

            cout << "Current Days Present: " << attendanceRecords[i].daysPresent << "\n";
            cout << "Current Days Absent: " << attendanceRecords[i].daysAbsent << "\n";

            cout << "Enter New Days Present: ";
            attendanceRecords[i].daysPresent = getValidInt();

            cout << "Enter New Days Absent: ";
            attendanceRecords[i].daysAbsent = getValidInt();

            cout << "Attendance updated successfully!\n";
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
            cout << "========================================\n";

            saveAttendance();
            break;
        }
    }

    if (!found) {
        cout << "Error: No record found for Month " << month << ".\n";
        cout << "========================================\n";
    }
}//eyad
<<<<<<< HEAD
=======

void deleteAttendance() {
    long long id;
    int month;
    bool found = false;

    cout << "\n========================================\n";
    cout << "           Delete Attendance\n";
    cout << "========================================\n";

    while (true) {
        cout << "Enter Employee ID: ";
        id = getValidId();

        bool idExists = false;
        for (int i = 0; i < attendanceCount; i++) {
            if (attendanceRecords[i].employeeID == id) {
                idExists = true;
                break;
            }
        }

        if (idExists) {
            break;
        }
        else {
            cout << "ID not found! Please enter again.\n\n";
        }
    }

    cout << "Enter Month (1-12) to delete: ";
    while (true) {
        month = getValidInt();
        if (month >= 1 && month <= 12) {
            break;
        }
        else {
            cout << "Error: Month must be between 1 and 12. Try again: ";
        }
    }

    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == id && attendanceRecords[i].month == month) {
            found = true;

            // Shift elements to the left to overwrite the deleted record
            for (int j = i; j < attendanceCount - 1; j++) {
                attendanceRecords[j] = attendanceRecords[j + 1];
            }

            attendanceCount--;

            cout << "Attendance record deleted successfully.\n";
            cout << "========================================\n";

            saveAttendance();
            break;
        }
    }

    if (!found) {
        cout << "Error: No record found for Month " << month << ".\n";
        cout << "========================================\n";
    }
}//mostafa hadidi
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0

void deleteEmployee() {
    long long id;
    bool found = false;
    cout << "\n========================================\n";
    cout << "           Delete Employee\n";
    cout << "========================================\n";
    cout << "Enter Employee ID: ";

    id = getValidId();

    for (int j = 0; j < employeeCount; j++) {
        if (employees[j].employeeID == id) {
            found = true;

            // Shift elements to the left to overwrite the deleted employee
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
}//abdelrahman

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

<<<<<<< HEAD
int findEmployeeIndex(long long id) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == id) return i;
    }
    return -1;
}

void searchEmployee(long long id) {
    int index = findEmployeeIndex(id);

    if (index == -1) {
        cout << "Employee not found!\n";
        return;
    }

    cout << "\nEmployee Found:\n";
    cout << "Name: " << employees[index].name << "\n";
    cout << "ID: " << employees[index].employeeID << "\n";

    int choice;
    cout << "\n1. View Salary\n";
    cout << "2. View Attendance\n";
    cout << "3. View Full Profile\n";
    cout << "Choose: ";

    choice = getValidInt();

    switch (choice) {
    case 1:
        viewSalary(index);
        break;

    case 2:
        viewAttendance(index);
        break;

    case 3:
        viewPersonalInfo(index);
        viewSalary(index);
        viewAttendance(index);
        break;

    default:
        cout << "Invalid choice!\n";
    }
}
=======
void viewAllEmployeesData() {
    cout << "\n========================================\n";
    cout << "          ALL EMPLOYEES REPORT          \n";
    cout << "========================================\n";

    if (employeeCount == 0) {
        cout << "No employees found in the system.\n";
        cout << "========================================\n";
        return;
    }

    // 1. Save the original index so we don't break the system state
    int originalIndex = currentEmployeeIndex;

    // 2. Loop through all employees
    for (int i = 0; i < employeeCount; i++) {
        cout << "\n\n>>>>>>>>>> EMPLOYEE #" << (i + 1) << " <<<<<<<<<<";

        // Temporarily trick the program into thinking 'i' is the logged-in employee
        currentEmployeeIndex = i;

        // Call your existing functions!
        viewPersonalInfo();
        viewSalary();
        viewAttendance();
    }

    // 3. Restore the original index when finished
    currentEmployeeIndex = originalIndex;
}//mahmoud 
>>>>>>> abd0562040685f873fcf6c14d50520790d3691d0
