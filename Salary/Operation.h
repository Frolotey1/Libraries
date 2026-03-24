#ifndef OPERATION_H
#define OPERATION_H
#include "Libraries.h"
class Operation {
public:
	virtual ~Operation() = default;
	virtual void change_salary_tax_rate(double&& tax_rate, double&& NDFL_rate) = 0;
	virtual std::tuple<std::string,std::string,double,unsigned int> data() = 0;
};
#endif