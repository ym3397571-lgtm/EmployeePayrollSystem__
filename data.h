#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;

// =======================
// Structs
// =======================

struct Employee {
    int employeeID = 0 ;         // معرف الموظف
    string name = 0 ;            // الاسم
    int age = 0 ;                // العمر
    string phone ;           // رقم الهاتف
    string role ;            // الوظيفة
    double basicSalary = 0.0;     // الراتب الأساسي
    double bonus = 0.0 ;           // البونص
    double overtime = 0.0 ;        // العمل الإضافي
    double tax = 0.0 ;             // الضريبة
    double netSalary = 0.0 ;       // صافي الراتب
    string password ;        // كلمة السر
    bool isActive = true;          // true = يعمل، false = في إجازة
};

struct Attendance {
    int employeeID = 0 ;         // ID الموظف
    string month = 0 ;           // الشهر
    int daysPresent = 0 ;        // عدد أيام الحضور
    int daysAbsent = 0 ;         // عدد أيام الغياب
};

struct AdminAccount {
    int adminID = 0 ;            // معرف الأدمن
    string name ;            // اسم المستخدم
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

extern Employee employees[MAX_EMPLOYEES];
extern Attendance attendanceRecords[MAX_ATTENDANCE];
extern AdminAccount admins[MAX_ADMINS];

// =======================
// Counters
// =======================

extern int employeeCount;
extern int attendanceCount;
extern int adminCount;

// =======================
// Roles
// =======================

const string ROLES[] = { "Manager", "Accountant", "Developer", "Designer", "HR" };


#endif