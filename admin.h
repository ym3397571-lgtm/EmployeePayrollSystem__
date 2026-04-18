#ifndef ADMIN_H
#define ADMIN_H

#include "data.h"
#include <string>
using namespace std;

// =======================
// Admin Panel Functions
// =======================

bool adminLogin(string username, string password);    // تسجيل دخول الأدمن
void addEmployee();                 // إضافة موظف جديد
void updateEmployee();              // تعديل بيانات موظف موجود
void deleteEmployee();              // حذف موظف
void recordAttendance();            // تسجيل حضور الموظفين
void calculateSalary(int employeeID);             // حساب صافي الراتب لكل موظف

// =======================
// Optional / Additional Admin Functions
// =======================

int findEmployeeByName(string name);      // البحث عن موظف بالاسم
void sortEmployeesBySalary();             // ترتيب الموظفين حسب الراتب
void sortEmployeesByName();               // ترتيب الموظفين حسب الاسم
void showDepartmentSummary();             // عرض تقرير قسم معين
void resetEmployeePassword(int employeeID); // إعادة تعيين كلمة سر الموظف

#endif