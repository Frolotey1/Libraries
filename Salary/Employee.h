#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "Operation.h"
class Employee : public Operation {
	std::string name = "";
	std::string status = "";
	double salary = 0.0;
	unsigned int experience = 0;
	unsigned int count_sales = 0;
public:
	explicit Employee();
	explicit Employee(std::string&& get_name, std::string&& get_status, double&& get_salary, unsigned int&& get_experience);
	std::string get_name() const;
	std::string get_status() const;
	void set_name(const std::string& new_name);
	void set_status(const std::string& new_status);
	double get_salary() const;
	void set_count_sales(unsigned int&& count_sales);
	unsigned int get_experience() const;
	void change_salary_tax_rate(double&& tax_rate, double&& NDFL_rate) override;
	std::tuple<std::string, std::string, double, unsigned int> data() override;
	std::string to_string();
	void increase_procents_from_sales(unsigned int&& new_count_sales);
	void raise_salary_for_work_years(unsigned int&& count_work_years);
private:
	void raise_salary(double& procent);
	void change_salary(double& rate_result);
};
#endif