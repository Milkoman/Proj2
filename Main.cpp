#include<iostream>
#include<fstream>
#include "Food.hpp"
#include "HashMap.hpp"
#include "Array.hpp"
#include "BinaryTree.hpp"
#include "Queue.h"
#include "FoodProcessor.hpp"
#include "ADTStatic.hpp"
#include <iomanip>
using namespace std;

void greeting();
int getSelection();
int getSize();
char yesorno();
Food * createFood();
bool isPrime(int);
int nextPrime(int);

struct MyKeyHash 
{
	int operator()(const string &k, int s) const
	{
		int i = 0;
		int temp = 0;
		while (k[i])
		{
			temp += k[i];
			i++;
		}
		return temp % s;
	}
};

void writeFile(HashMap<string, Food, MyKeyHash>&);
void buildDatabase(Array<Food> &, HashMap<string, Food, MyKeyHash>&, BinaryTree<Food> &);

//steven
template <class T>
void input(T &a, const char * error = "");

//template<class T>
//void write(T data, ostream &outfile) { outfile <<= data; }

//olly
template <class T>
void add(Queue<T> & queue, T & data) {
	queue.enqueue(data);
}

template <class T>
void add(BinaryTree<T> & btree, T & data)
{
	btree.add(data);
}

template <class T>
void add(BinaryTree<T> & btree, T & data, bool LGR(const T &, const T &))
{
	btree.add(data, LGR);
}

template <class T>
void print(T & data) {cout << data << '\n';}

template <class T>
void printIndent(T & data, int indent) {
	for (int i = 1; i < indent; i++) {
		cout << '\t';
	}

	cout << data << '\n';
}

template <class T>
Queue<T> qT;

int main()
{
	greeting();
	int size = getSize();
	Array<Food> ary(size);

	HashMap<string, Food, MyKeyHash> HM(nextPrime(size));
	BinaryTree<Food> calTree;
	buildDatabase(ary, HM, calTree);

	int selection = 0;
	do
	{
		selection = getSelection();
		if (selection == 1)
		{
			Food *item = createFood();
			HM.add(item->getName(), item);
			calTree.add(*item, Food::calorieLGreaterR);
		}
		else if (selection == 2)
		{
			string name;
			Food item;
			cout << "\nWhat is the name of the item you wish to remove? ";
			getline(cin, name);
			if (HM.get(name, item))
			{
				Food item2(name,0,0,0,0);
				HM.remove(name);
				calTree.remove(item2);
				cout << name << " has been removed.";
			}
			else
				cout << "Does not exsist";
		}
		else if (selection == 3)
		{
			bool done = false;
			do
			{
				string key;
				cout << "\nEnter the Key: ";
				getline(cin, key);
				Food item;
				if (HM.get(key, item)) 
					cout << item;
				else
					cout << "Not Found";
				cout << "\nWould you like to Search again? ";
				char inp = yesorno();
				if (inp == 'N')
					done = true;

			} while (done == false);

		}
		else if (selection == 4)
		{
			string s = "-";
			s.assign(25, '-');

			cout << "\nHere is your Table\n" << s << "\n";
			HM.displayTable();
		}
		else if (selection == 5)
		{
			calTree.inorderTraverse(print);
		}
		else if (selection == 6)
		{
			calTree.inorderTraverse(printIndent);
		}
		else if (selection == 7)
		{
			string s = "-";
			s.append(15,'-');
			cout << "\nEFFICIENCIES\n" << s
				 << "\n\nCollisions in Hash Table: " << HM.getNumCollisions() << '\n'
				 << "Load Factor: " << setprecision(1) << fixed << HM.getLoadFactor() << "\n"
				 << "Longest Chain is: " << HM.getLongestChain() << '\n';
		}
		else if (selection == 8)
		{

		}
		else if (selection == 9)
		{
			cout << "\nStay Healty -GoodBye!\n";
			writeFile(HM);
		}
	} while (selection != 9);
	//cout << ary;
	system("pause");
	return 0;
}

void greeting()
{
	cout << "Welcome to the Food Data Base! - with maybe (??Meal plan creater with macro constraints and suggestions??)\n";
}

int getSelection()
{
	int num = 0;
	cout << "\n\nWhat would you like to do? Enter a number [1-9].\n1. Add a new food\n2. Remove a food\n3. Find a food\n4. List Data by Key\n5. List Data by Calorie\n6. Print indented tree\n7. Efficiency\n"
		<< "8. Create meal plan\n9. Quit & Save\n";
	cin >> num;
	if (num < -1 || num > 255)
		num = 0;
	if (!isdigit(num)) {
		cin.clear();
		cin.ignore(20, '\n');
	}
	if (num <= 0 || num > 9)
		num = getSelection();

	return num;
}

int getSize()
{
	fstream file;
	file.open("foodData.txt");
	int num = 0;
	file >> num;
	file.close();
	return num;
}

char yesorno()
{
	cout << "Enter <y/n> ";
	char inp = 'X';
	cin >> inp;
	cin.ignore(20, '\n');
	inp = toupper(inp);
	if (inp == 'Y' || inp == 'N')
		return inp;
	else
		inp = yesorno();
}

Food *createFood()
{

	Food *item = new Food;
	bool happy = false;
	
	do 
	{
		string name;
		int cal, fat, carb, prot;
		cout << "What is the new item? ";
		getline(cin, name);
		cout << "Enter calorie: ";
		input(cal,"Enter calorie");
		cout << "Enter Fat: ";
		input(fat, "Enter Fat");
		cout << "Enter carb: ";
		input(carb, "Enter carb");
		cout << "Enter protien: ";
		input(prot, "enter protien");
		item->setName(name);
		item->setCalorie(cal);
		item->setFat(fat);
		item->setCarb(carb);
		item->setProtein(prot);
		cout << "is this the correct item you wish to add? " << *item << "\n";
		char inp = yesorno();
		if (inp == 'Y')
			happy = true;

	} while (happy == false);

	return item;
}

bool isPrime(int num)
{
	if (num == 2 || num == 3)
		return true;
	if (num % 2 == 0 || num % 3 == 0)
		return false;
	int divisor = 6;
	while (divisor * divisor - 2 * divisor + 1 <= num)
	{
		if (num % (divisor - 1) == 0)
			return false;
		if (num % (divisor + 1) == 0)
			return false;
		divisor += 6;
	}
	return true;
}

int nextPrime(int num)
{
	while (!isPrime(++num)){}
	return num;
}

void buildDatabase(Array<Food> &ary, HashMap<string, Food, MyKeyHash>&HM, BinaryTree<Food> &calT)
{
	fstream file;
	file.open("foodData.txt");
	int num = 0;
	file >> num;
	file.ignore(20, '\n');
	Food item;
	for (int i = 0; i < num; i++)
	{
		file >> item;
		ary[i] = item;
		HM.add(item.getName(), &ary[i]);
		calT.add(ary[i], Food::calorieLGreaterR);
	}
}

void writeFile(HashMap<string, Food, MyKeyHash>&HM)
{
	ofstream file;
	file.open("foodData.txt");
	file << HM.getNumNodes() << '\n';
	HM.traverse(write, file);
	file.close();
}

template<class T>
void input(T & a, const char * error)
{
	while (!(cin >> a))
	{
		cin.clear();
		cin.ignore(20, '\n');
		while (cin.get() != '\n') continue;
		cout << "Invalid Value! " << error << endl;
	}

}
