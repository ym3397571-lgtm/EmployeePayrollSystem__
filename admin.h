#ifndef ADMIN_H
#define ADMIN_H

#include "data.h"
#include <string>
using namespace std;

// =======================
// Admin Panel Functions
// =======================

bool adminLogin();                  // تسجيل دخول الأدمن
void addEmployee(long long empId);                 // إضافة موظف جديد
void updateEmployee(long long empId);              // تعديل بيانات موظف موجود
void deleteEmployee(long long empId);              // حذف موظف
void recordAttendance(long long empId);            // تسجيل حضور الموظفين
void calculateSalary(long long empId);             // حساب صافي الراتب لكل موظف

#endif // ADMIN_H
