#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "data.h"
#include <string>
using namespace std;

// =======================
// Employee Panel Functions
// =======================

bool employeeLogin();               // تسجيل دخول الموظف
void viewPersonalInfo(int index);            // عرض البيانات الشخصية للموظف
void viewSalary(int index );                  // عرض تفاصيل المرتب
void viewAttendance(int index );              // عرض سجل الحضور للموظف

// =======================
// Optional / Additional Employee Functions
// =======================

//void viewDepartmentSalarySummary();  // عرض رواتب القسم
//void requestLeave();                 // تقديم طلب إجازة (يمكن إضافتها لاحقًا)

#endif
