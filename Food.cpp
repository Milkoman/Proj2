#include "Food.hpp"

Food::Food()
{
	name = "";
	calorie = 0;
	fat = 0;
	carb = 0;
	protein = 0;
}

Food::Food(const string n, const int cal, const int f, const int c, const int p)
{
	name = n;
	calorie = cal;
	fat = f;
	carb = c;
	protein = p;
}

bool Food::operator>(const Food &right)
{
	bool status = false;
	if (name > right.name)
		status = true;

	return status;
}

bool Food::calorieGreater(const Food &right) const
{
	bool status = false;
	if (calorie > right.calorie)
		status = true;
	return status;
}

bool Food::fatGreater(const Food &right) const
{
	bool status = false;
	if (fat > right.fat)
		status = true;
	return status;
}

ostream & operator<<(ostream &strm, const Food &obj)
{
	strm << obj.name << " " << obj.calorie << " " << obj.fat << " " << obj.carb << " " << obj.protein;
	return strm;
}

istream & operator>>(istream &strm, Food &obj)
{
	//std::cout << "Enter item name: ";
	getline(strm, obj.name, '\n');
	//std::cout << "Enter cal. fat. carb. prot.: ";
	strm >> obj.calorie >> obj.fat >> obj.carb >> obj.protein;
	strm.ignore(20, '\n');
	return strm;
}
