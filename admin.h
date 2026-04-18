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

// =======================
// Optional / Additional Admin Functions
// =======================

int findEmployeeByName(string name);      // البحث عن موظف بالاسم
void sortEmployeesBySalary();             // ترتيب الموظفين حسب الراتب
void sortEmployeesByName();               // ترتيب الموظفين حسب الاسم
void showDepartmentSummary();             // عرض تقرير قسم معين
void resetEmployeePassword(long long employeeID); // إعادة تعيين كلمة سر الموظف

#endif