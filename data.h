#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;

// =======================
// Structs
// =======================

struct Employee {
    long long employeeID ;         // معرف الموظف
    string name  ;            // الاسم
    string username;
    int age  ;                // العمر
    string phone ;           // رقم الهاتف
    string role ;            // الوظيفة
    double basicSalary ;     // الراتب الأساسي
    double bonus  ;           // البونص
    double overtime  ;        // العمل الإضافي
    double tax  ;             // الضريبة
    double netSalary  ;       // صافي الراتب
    string password ;        // كلمة السر
    double TotalHoursWorked = 0;
    double WorkHoursPerMonth = 0;
};

struct Attendance {
    long long employeeID = 0 ;         // ID الموظف
    string month  ;           // الشهر
    int daysPresent = 0 ;        // عدد أيام الحضور
    int daysAbsent = 0 ;         // عدد أيام الغياب
};

struct AdminAccount {
    long long adminID  ;            // معرف الأدمن
    string username;
    string password ;        // كلمة السر
};

// =======================
// Constants
// =======================

const int MAX_EMPLOYEES = 100;
const int MAX_ATTENDANCE = 200;
const int MAX_ADMINS = 2;
const double TaxRate = 0.14;
const double WorkHoursPerMonth = 160.0;

// =======================
// SystemData Struct
// =======================

struct SystemData {
    Employee employees[MAX_EMPLOYEES];
    Attendance attendanceRecords[MAX_ATTENDANCE];
    AdminAccount admins[MAX_ADMINS];

    int employeeCount = 0;
    int attendanceCount = 0;
    int adminCount = 0;

<<<<<<< HEAD
    int currentEmployeeIndex = -1;
    int currentAdminIndex = -1;
};

extern SystemData data;

// =======================
// Roles
// =======================

const string ROLES[] = { "Manager", "Accountant", "Developer", "Designer", "HR" };


#endif
=======
extern int employeeCount;
extern int attendanceCount;
extern int adminCount;
#endif
>>>>>>> a876b1f48e9d64cf96044774c1a3b686c1006665
