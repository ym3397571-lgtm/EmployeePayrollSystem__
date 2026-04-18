#include <iostream>
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
    if (adminLogin()) {
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

bool adminLogin() {
    cout << "[Stub] adminLogin\n";
    return true;
} // محمود 

bool employeeLogin() {
    cout << "[Stub] employeeLogin\n";
    return true;
} // ahmed 

// =======================
// LOAD / SAVE STUBS | yossef 
// =======================

void loadEmployees() {
    cout << "[Stub] loadEmployees\n";
}

void saveEmployees() {
    cout << "[Stub] saveEmployees\n";
}

void loadAdmins() {
    cout << "[Stub] loadAdmins\n";
}

void saveAdmins() {
    cout << "[Stub] saveAdmins\n";
}

void loadAttendance() {
    cout << "[Stub] loadAttendance\n";
}

void saveAttendance() {
    cout << "[Stub] saveAttendance\n";
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


void calculateSalary() {
    cout << "[Stub] calculateSalary\n";
}// eyad 

void recordAttendance() {
    cout << "[Stub] recordAttendance\n";
}// Abdelrahman

void deleteEmployee() {
    cout << "[Stub] deleteEmployee\n";
}//  Abdelrahman

void removeEmployee() {
    cout << "[Stub] removeEmployee\n";
}

void resetEmployeePassword(int employeeID) {
    cout << "[Stub] resetEmployeePassword\n";
}

void requestLeave() {
    cout << "[Stub] requestLeave\n";
}



