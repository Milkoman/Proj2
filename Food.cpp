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

bool Food::calorieLGreaterR(const Food & left, const Food & right)
{
	return left.calorie > right.calorie;
}

bool Food::fatLGreaterR(const Food & left, const Food & right)
{
	return left.fat > right.fat;
}

bool Food::carbLGreaterR(const Food & left, const Food & right)
{
	return left.carb > right.carb;
}

bool Food::proteinLGreaterR(const Food & left, const Food & right)
{
	return left.protein > right.protein;
}

bool Food::calorieLLessR(const Food & left, const Food & right)
{
	return left.calorie < right.calorie;
}
bool Food::fatLLessR(const Food & left, const Food & right)
{
	return left.fat < right.fat;
}
bool Food::carbLLessR(const Food & left, const Food & right)
{
	return left.carb < right.carb;
}
bool Food::calorieLEqualR(const Food & left, const Food & right)
{
	return left.calorie == right.calorie;
}
bool Food::fatLEqualR(const Food & left, const Food & right)
{
	return left.fat == right.fat;
}
bool Food::proteinLEqualR(const Food & left, const Food & right)
{
	return left.protein == right.protein;
}
bool Food::carbLEqualR(const Food & left, const Food & right)
{
	return left.carb == right.carb;
}
bool Food::completeLEqualR(const Food &left, const Food &right)
{
	return left.name == right.name && left.calorie == right.calorie && left.fat == right.fat && left.carb == right.carb && left.protein == right.protein;
}
bool Food::proteinLLessR(const Food & left, const Food & right)
{
	return left.protein < right.protein;
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
