#include "SalariedEmployee.h"

SalariedEmployee::SalariedEmployee() = default;
SalariedEmployee::SalariedEmployee(std::initializer_list<double> salary_months) {
	months.assign(salary_months.begin(),salary_months.end());
}
std::ostream& operator <<(std::ostream& out, const SalariedEmployee& se) {
	out << se.get_name() << " " << se.get_status() << " " << se.get_salary() << " " << se.get_experience() << std::endl;
	return out;
}
void SalariedEmployee::date_accepting_and_salary_months() {
	for (std::size_t i = 0; i < months.size(); ++i) {
		std::cout << std::format("{} месяц:\n{} рублей",(i + 1),months.at(i)) << " ";
	}
	std::cout << std::endl;
	std::cout << "Дата принятия на работу: " << std::chrono::system_clock::now() << std::endl;
};
void SalariedEmployee::report() {
	std::cout << "{\n\tName: " << get_name() << "\n\tStatus: " << get_status() << "\n\tSalary: " << get_salary() << "\n\tExperience: " << get_experience() << "\t }" << std::endl;
}