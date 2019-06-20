#ifndef FOOD_H
#define FOOD_H
#include <string>
#include <iostream>
using std::string;
using std::ostream;
using std::istream;

class Food;
ostream &operator<< (ostream &, const Food &);
istream &operator>> (istream &, Food &);

class Food
{
	private:
		string name;
		int calorie;
		int fat;
		int carb;
		int protein;

	public:
		Food();
		Food(const string, const int, const int, const int, const int);

		//Mutators
		void setName(const string n) { name = n; }
		void setCalorie(const int c) { calorie = c; }
		void setFat(const int f) { fat = f; }
		void setCarb(const int c) { carb = c; }
		void setProtein(const int p) { protein = p; }
		//Accessors
		string getName() const { return name; }
		int getCalorie() const { return calorie; }
		int getFat() const { return fat; }
		int getCarb() const { return carb; }
		int getProtein() const { return protein; }
		//Operators
		friend ostream &operator<< (ostream &, const Food &);
		friend istream &operator>> (istream &, Food &);
		bool operator== (const Food &obj){return (name == obj.getName() && calorie == obj.getCalorie() && fat == obj.getFat() && carb == obj.getCarb() && protein == obj.getProtein());}
		bool operator> (const Food &);
		//Methods
		bool calorieGreater(const Food &) const;
		bool fatGreater(const Food &) const;
};


#endif
