#include "SalariedEmployee.h"

int main() {
	std::setlocale(LC_ALL,"Rus");
	SalariedEmployee se{1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,12000};
	se.date_accepting_and_salary_months();
	se.set_name("Bob");
	se.set_status("Employee");
	se.change_salary_tax_rate(5, 5);
	std::cout << se.get_name() << " " << se.get_status() << " " << se.get_salary() << " " << se.get_experience() << std::endl;
	return 0;
}