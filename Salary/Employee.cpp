#include "Employee.h"

Employee::Employee() = default;
Employee::Employee(std::string&& get_name, std::string&& get_status, double&& get_salary, unsigned int&& get_experience) {
	this->name = get_name;
	this->status = get_status;
	this->salary = get_salary;
	this->experience = get_experience;
}
std::string Employee::get_name() const { return this->name; }
std::string Employee::get_status() const { return this->status; }
void Employee::set_name(const std::string& new_name) {
	this->name = new_name;
}
void Employee::set_status(const std::string& new_status) {
	this->status = new_status;
}
double Employee::get_salary() const { return this->salary; }
unsigned int Employee::get_experience() const { return this->experience; }
std::tuple<std::string, std::string, double, unsigned int> Employee::data() {
	return std::make_tuple(get_name(),get_status(),get_salary(),get_experience());
}
void Employee::change_salary(double& rate_result) {
	this->salary = rate_result;
}
void Employee::change_salary_tax_rate(double&& tax_rate, double&& NDFL_rate) {
	double rate_result = tax_rate / (1 - NDFL_rate / 100);
	std::cout << std::format("Зарплата до налоговой ставки: {}\nЗарплата после налоговой ставки: {}",get_salary(),rate_result) << std::endl;
	change_salary(rate_result);
}
void Employee::raise_salary(double& procent) {
	if (procent < 0.0) throw std::invalid_argument("Процентная ставка не может быть ниже нуля");
	this->salary = this->salary + ((this->salary * procent) / 100);
}
void Employee::set_count_sales(unsigned int&& count_sales) {
	if (count_sales < 0) throw std::invalid_argument("Ошибка ввода количества продаж");
	this->count_sales = count_sales;
}
void Employee::increase_procents_from_sales(unsigned int&& new_count_sales) {
	double procent = new_count_sales - this->count_sales / this->count_sales * 100;
	raise_salary(procent);
}
void Employee::raise_salary_for_work_years(unsigned int&& count_work_years) {
	if (count_work_years < 0) throw std::invalid_argument("Ошибка ввода количества лет работы");
	double procent_for_years = this->salary + (this->salary * static_cast<double>(count_work_years) / 100);
	raise_salary(procent_for_years);
}
std::string Employee::to_string() {
	std::ostringstream for_string;
	for_string << get_name() << " " << get_status() << " " << get_salary() << " " << get_experience();
	return for_string.str();
}