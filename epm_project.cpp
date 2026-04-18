#include <iostream>
using namespace std;

// =======================
// Headers
// =======================
#include "employee.h"
#include "admin.h"
#include "data.h"
#include "storage.h"
#include "fstream"

// =======================
// Function Declarations
// =======================
void showMainMenu();
void handleAdmin();
void handleEmployee();

// =======================
// Global Variables Definition
// =======================
Employee employees[MAX_EMPLOYEES];
Attendance attendanceRecords[MAX_ATTENDANCE];
AdminAccount admins[MAX_ADMINS];

int employeeCount = 0;
int attendanceCount = 0;
int adminCount = 0;

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
        cin >> choice;

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
    cout << "\n===== Employee Payroll System =====\n";
    cout << "1. Admin Login\n";
    cout << "2. Employee Login\n";
    cout << "3. Exit\n";
    cout << "Choose: ";
}  // youssef 

 
void handleAdmin() {
    string username = "Admin1";
    string password = "Password1";
    if (adminLogin(username, password)) {
        cout << "Admin logged in successfully.\n";

        // TODO:  Menu
        cout << "Admin functions coming soon...\n";
    }
    else {
        cout << "Invalid admin credentials.\n";
    }
}  //  محمود


void handleEmployee()    { 
    if (employeeLogin()) {
        cout << "Employee logged in successfully.\n";

       
        cout << "Employee functions coming soon...\n";
    }
    else {
        cout << "Invalid employee credentials.\n";
	} // ahmed
}



// =======================
// LOGIN STUBS
// =======================

bool adminLogin(string username, string password) {
    string adminname;
    string adminpass;
    cout << "Enter Username: ";
    getline(cin, adminname);
    cout << "Enter Password: ";
    getline(cin, adminpass);

    if (adminname == username && adminpass == password) {
        return true;
    }
    return false;
} // محمود

bool employeeLogin() {
    cout << "[Stub] employeeLogin\n";
    return true;
} // ahmed 

// =======================
// LOAD / SAVE STUBS | yossef 
// =======================

void loadEmployees() {
    ifstream in("employees.txt");
    if (!in) {
        cout << "no file found" << endl;
        return;
    }
    employeeCount = 0;
    while (employeeCount < MAX_EMPLOYEES && in >> employees[employeeCount].employeeID >> employees[employeeCount].name
        >> employees[employeeCount].basicSalary >> employees[employeeCount].age >> employees[employeeCount].phone
        >> employees[employeeCount].role >> employees[employeeCount].bonus
        >> employees[employeeCount].overtime >> employees[employeeCount].tax
        >> employees[employeeCount].netSalary >> employees[employeeCount].TotalHoursWorked
        >> employees[employeeCount].password) {
        employeeCount++;
    }
    in.close();
}

void saveEmployees() {
    ofstream out("employees.txt");
    for (int i = 0; i < employeeCount; i++) {
        out << employees[i].employeeID << " " << employees[i].name << " "
            << employees[i].basicSalary << " " << employees[i].age << employees[i].phone << " "
            << employees[i].role << " " << employees[i].bonus << " "
            << employees[i].overtime << " " << employees[i].tax << " "
            << employees[i].netSalary << " " << employees[i].TotalHoursWorked << " "
            << employees[i].password << endl;
    }
    out.close();
}

void loadAdmins() {
    ifstream in("admins.txt");
    if (!in) {
        cout << "no file found" << endl;
        return;
    }
    adminCount = 0;
    while (adminCount < MAX_ADMINS && in >> admins[adminCount].adminID >> admins[adminCount].name >> admins[adminCount].password) {
        adminCount++;
    }
    in.close();
}

void saveAdmins() {
    ofstream out("admins.txt");
    for (int i = 0; i < adminCount; i++) {
        out << admins[i].adminID << " " << admins[i].name << " " << admins[i].password << endl;
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
    while (attendanceCount < 200 && in >> attendanceRecords[attendanceCount].employeeID >> attendanceRecords[attendanceCount].daysPresent >> attendanceRecords[attendanceCount].daysAbsent) {
        attendanceCount++;
    }
    in.close();
}

void saveAttendance() {
    ofstream out("attendance.txt");
    for (int i = 0; i < attendanceCount; i++) {
        out << attendanceRecords[i].employeeID << " " << attendanceRecords[i].daysPresent << " " << attendanceRecords[i].daysAbsent << endl;
    }
    out.close();
}

// employee functions 

void viewPersonalInfo() {
    cout << "[Stub] viewPersonalInfo\n";
} //  ahmed 

void viewSalary() {
    cout << "[Stub] viewSalary\n";
} // mostafa elhadidy

void viewAttendance() {
    cout << "[Stub] viewAttendance\n";
}// mostafa elhadidy

void viewDepartmentSalarySummary() {
    cout << "[Stub] viewDepartmentSalarySummary\n";
}// mostafa elhadidy



void addEmployee() {
    cout << "[Stub] addEmployee\n";
} // mostafa2

void updateEmployee() {
    cout << "[Stub] updateEmployee\n";
}// mostafa2 


void calculateSalary(int employeeID)
{
    employees[employeeID].overtime = employees[employeeID].TotalHoursWorked - WorkHoursPerMonth;
    employees[employeeID].bonus = (employees[employeeID].basicSalary / WorkHoursPerMonth) * employees[employeeID].overtime;
    employees[employeeID].tax = (employees[employeeID].basicSalary * TaxRate);
    employees[employeeID].netSalary = (employees[employeeID].basicSalary + employees[employeeID].bonus) - employees[employeeID].tax;
}// eyad

void recordAttendance() {
    cout << "[Stub] recordAttendance\n";
}// Abdelrahman

void deleteEmployee() {
    cout << "[Stub] deleteEmployee\n";
}//  Abdelrahman

static void removeEmployee() {
    cout << "[Stub] removeEmployee\n";
}

void resetEmployeePassword(int employeeID) {
    cout << "[Stub] resetEmployeePassword\n";
}

void requestLeave() {
    cout << "[Stub] requestLeave\n";
}



