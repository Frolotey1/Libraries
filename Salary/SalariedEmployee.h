#ifndef SALARIED_EMPLOYEE_H
#define SALARIED_EMPLOYEE_H
#include "Employee.h"
class SalariedEmployee : public Employee {
	std::string json_format;
	std::vector<double> months;
public:
	explicit SalariedEmployee();
	explicit SalariedEmployee(std::initializer_list<double> salary_months);
	void report();
	void date_accepting_and_salary_months();
};
#endif