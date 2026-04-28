#ifndef ADMIN_H
#define ADMIN_H

#include "data.h"
#include <string>
using namespace std;

// =======================
// Admin Panel Functions
// =======================

bool adminLogin();                  // تسجيل دخول الأدمن
void addEmployee();                 // إضافة موظف جديد
void updateEmployee();              // تعديل بيانات موظف موجود
void deleteEmployee();              // حذف موظف
void recordAttendance();            // تسجيل حضور الموظفين
void calculateSalary(long long employeeID);             // حساب صافي الراتب لكل موظف

#endif // ADMIN_H