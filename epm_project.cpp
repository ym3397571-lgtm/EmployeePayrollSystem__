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
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after reading choice

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
        cout << "\n========================================\n";
        cout << "Login Successful\n";
        cout << "========================================\n";
		int choice_admin;
        while (true) {
            cout << "\n===== Admin Menu =====\n";
            cout << "1. Add Employee\n";
            cout << "2. Update Employee\n";
            cout << "3. Delete Employee\n";
            cout << "4. Record Attendance\n";
            cout << "5. Calculate Salary\n";
            cout << "6. Logout\n";
            cout << "Choose: ";
            cin >> choice_admin;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after reading choice
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
                    long long  empId;
                    cout << "Enter Employee ID to calculate salary: ";
                    cin >> empId;
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


void handleEmployee()    { 
    if (employeeLogin()) {
        cout << "Employee logged in successfully.\n";
        int choice_employe;
        while (true) {
            cout << "\n===== Employee Menu =====\n";
            cout << "1. View Personal Information\n";
            cout << "2. View Salary Information\n";
            cout << "3. View Attendance Record\n";
            cout << "4. View Department Salary Summary\n";
            cout << "5. Logout\n";
            cout << "Choose: ";
            cin >> choice_employe;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer after reading choice
            switch (choice_employe) {
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
                    viewDepartmentSalarySummary();
                    break;
                case 5:
                    cout << "Logging out...\n";
                    return;
                default:
                    cout << "Invalid choice!\n";
            }
		}
    }
    else {
        cout << "Invalid employee credentials.\n";
	}
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

    for (int i = 0; i < adminCount; i++) {
        if (admins[i].username == adminname && admins[i].password == adminpass) {
            return true;
        }
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
        cout << "ERROR: employees.txt not found in execution folder\n";
        return;
    }

    cout << "File opened successfully\n";
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
        out << employees[i].employeeID << "|" << employees[i].name << "|"
            << employees[i].basicSalary << "|" << employees[i].age<< "|" << employees[i].phone << "|"
            << employees[i].role << "|" << employees[i].bonus << "|"
            << employees[i].overtime << "|" << employees[i].tax << "|"
            << employees[i].netSalary << "|" << employees[i].TotalHoursWorked << "|"
            << employees[i].password << endl;
    }
    out.close();
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

bool employeeExists(long long empId) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == empId) {
            return true;
        }
    }
    return false;
}

void viewPersonalInfo() {
    long long empId;
    cout << "\n========================================\n";
    cout << "          View Personal Information\n";
    cout << "========================================\n";
    cout << "Enter Employee ID: ";
    cin >> empId;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == empId) {
            cout << "\n========================================\n";
            cout << "Employee ID: " << employees[i].employeeID << "\n";
            cout << "Name: " << employees[i].name << "\n";
            cout << "Age: " << employees[i].age << "\n";
            cout << "Phone: " << employees[i].phone << "\n";
            cout << "Role: " << employees[i].role << "\n";
            cout << "========================================\n";
            return;
        }
    }
    cout << "\nError: No employee found with ID " << empId << "\n";
    cout << "========================================\n";
} //  ahmed

void viewSalary() {
    long long  empId;
    cout << "\n========================================\n";
    cout << "          View Salary Information\n";
    cout << "========================================\n";
    cout << "Enter Employee ID: ";
    cin >> empId;

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == empId) {
            cout << "\n========================================\n";
            cout << "Employee ID: " << employees[i].employeeID << "\n";
            cout << "Name: " << employees[i].name << "\n";
            cout << "Basic Salary: " << fixed << setprecision(2) << employees[i].basicSalary << "\n";
            cout << "Bonus: " << fixed << setprecision(2) << employees[i].bonus << "\n";
            cout << "Overtime: " << fixed << setprecision(2) << employees[i].overtime << "\n";
            cout << "Tax: " << fixed << setprecision(2) << employees[i].tax << "\n";
            cout << "Net Salary: " << fixed << setprecision(2) << employees[i].netSalary << "\n";
            cout << "========================================\n";
            return;
        }
    }
    cout << "\nError: No employee found with ID " << empId << "\n";
    cout << "========================================\n";
} // mostafa elhadidy

void viewAttendance() {
    long long empId;
    cout << "\n========================================\n";
    cout << "           Attendance Record\n";
    cout << "========================================\n";
    cout << "Enter Employee ID: ";
    cin >> empId;

    cout << "\n========================================\n";
    cout << "Employee ID: " << empId << "\n";

    bool found = false;
    for (int i = 0; i < attendanceCount; i++) {
        if (attendanceRecords[i].employeeID == empId) {
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
    cout << "[Stub] addEmployee\n";
} // mostafa2

void updateEmployee() {
    cout << "[Stub] updateEmployee\n";
}// mostafa2 

void calculateSalary(long long employeeID)
{
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].employeeID == employeeID) {

            employees[i].overtime = employees[i].TotalHoursWorked - employees[i].WorkHoursPerMonth;
            employees[i].bonus = (employees[i].basicSalary / employees[i].WorkHoursPerMonth) * employees[i].overtime;
            employees[i].tax = (employees[i].basicSalary * TaxRate);
            employees[i].netSalary = (employees[i].basicSalary + employees[i].bonus) - employees[i].tax;

            return;
        }
    }

    cout << "Employee not found!\n";

}// eyad 

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



