#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;

// =======================
// Structs
// =======================

struct Employee {
    int employeeID;         // معرف الموظف
    string name;            // الاسم
    int age;                // العمر
    string phone;           // رقم الهاتف
    string role;            // الوظيفة
    double basicSalary;     // الراتب الأساسي
    double bonus;           // البونص
    double overtime;        // العمل الإضافي
    double tax;             // الضريبة
    double netSalary;       // صافي الراتب
    string password;        // كلمة السر
    bool isActive;          // true = يعمل، false = في إجازة
};

struct Attendance {
    int employeeID;         // ID الموظف
    string month;           // الشهر
    int daysPresent;        // عدد أيام الحضور
    int daysAbsent;         // عدد أيام الغياب
};

struct AdminAccount {
    int adminID;            // معرف الأدمن
    string name;            // اسم المستخدم
    string password;        // كلمة السر
};

// =======================
// Constants
// =======================

const int MAX_EMPLOYEES = 100;
const int MAX_ATTENDANCE = 200;
const int MAX_ADMINS = 2;
const double TaxRate = 0.14, WorkHoursPerDay = 8, WorkHoursPerMonth = 160, BasicSalary = 8000;

// =======================
// Arrays
// =======================

Employee employees[MAX_EMPLOYEES];
Attendance attendanceRecords[MAX_ATTENDANCE];
AdminAccount admins[MAX_ADMINS];

// =======================
// Counters
// =======================

int employeeCount = 5;
int attendanceCount = 0;
int adminCount = 1;

// =======================
// Roles
// =======================

const string ROLES[] = { "Manager", "Accountant", "Developer", "Designer", "HR" };


#endif
