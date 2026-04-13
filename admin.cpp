#include "data.h"
#include "admin.h"ٍ
#include <iostream>
using namespace std;

void calculateSalary()
{
    double TotalHoursWorked = 0;
    double BonusHours = TotalHoursWorked - WorkHoursPerMonth;
    double BonusSalary = (BasicSalary / WorkHoursPerMonth) * BonusHours;
    double Tax = (BasicSalary * TaxRate);
    double NetSalary = (BasicSalary + BonusSalary) - Tax;
}