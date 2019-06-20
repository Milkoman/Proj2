#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "MealPlan.h"
#include "Queue.h"
#include "Food.hpp"
#include "FoodProcessor.hpp"
#include "BinaryTree.hpp"
#include "BinaryNode.hpp"
#include "HashNode.hpp"
#include "HashMap.hpp"
#include "Array.hpp"
#include "ADTStatic.hpp"

using namespace std;

struct Requirements
{
  //cal lower
  int c_l;
  //cal upper
  int c_u;
  //fat lower
  int f_l;
  //fat upper
  int f_u;
  //carb lower
  int cb_l;
  //carb upper
  int cb_u;
  //protein lower
  int p_l;
  //protein upper
  int p_u;
};

void greeting();
int getSelection();
int getSize();
char yesorno();
Food * createFood();
bool isPrime(int);
int nextPrime(int);
void searchVisitor(Food &obj);
int mealPlanCreator(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashMap<string, Food, MyKeyHash<string> > &HM, FoodProcessor &food_p_obj);
int adjustedGoalMealPlanTest(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashMap<string, Food, MyKeyHash<string> > &HM, FoodProcessor &food_p_obj);
void searchFoodsOption(HashMap<string, Food, MyKeyHash<string> > &HM, FoodProcessor &food_p_obj);
Requirements getBounds();
void foodDisplayer(Food food);
void emptyMealPlanOption(MealPlan &plan, List<Food> &possibilities);
void displayMealPlanOption(MealPlan &plan);
void displayCurrentTotalsOption(MealPlan &plan);
void displayGoalsOption(Requirements req);
void deleteFoodOption(List<Food> &possibilities, MealPlan &plan, bool hard_delete, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req);
void addFoodOption(List<Food> &possibilities, MealPlan &plan, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req);
void displayMealPlanMenu(bool version = true);
void possibilityVisitor(Food &obj);
void possibilitiesGetter(FoodProcessor &food_p_obj, Requirements req, List<Food> &possibilities);


Queue<Food> searchResults;
List<Food> possibilities;


void writeFile(HashMap<string, Food, MyKeyHash<string> > &);
void buildDatabase(Array<Food> &, HashMap<string, Food, MyKeyHash<string> >&, BinaryTree<Food> &, FoodProcessor &);

template <class T>
void input(T &a, const char * error = "");

template<class T>
void write(T data, ostream &outfile) { outfile <<= data; }

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
	//meal plan creator variables/objects
	Requirements req;
	int repeat;
	FoodProcessor food_p_obj;
	FoodProcessor addTest;
	FoodProcessor non_possible;
	bool dummy;
	MealPlan plan;
	Food* holder;

	greeting();
	int size = getSize();
	Array<Food> ary(size);

	HashMap<string, Food, MyKeyHash<string> > HM(nextPrime(size));
	BinaryTree<Food> calTree;
	buildDatabase(ary, HM, calTree, food_p_obj);

	int selection = 0;
	do
	{
		selection = getSelection();
		if (selection == 1)
		{
			Food *item = createFood();
			HM.add(item->getName(), item);
			calTree.add(*item, Food::calorieLGreaterR);
			food_p_obj.add(*item);
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
				dummy = food_p_obj.remove(item);
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
			plan.emptyPlan();
			possibilities.empty();
			if(addTest.getQuadrupleCount() != 0)
				addTest.emptyProcessor();
			if(non_possible.getQuadrupleCount() != 0)
				non_possible.emptyProcessor();
			repeat = 0;

			do
			{
				req = getBounds();
				possibilitiesGetter(food_p_obj, req, possibilities);
				holder = NULL;
				for(int i = 0; i < possibilities.getCount(); i++)
				{
					holder = possibilities.getFirst();
					addTest.add(*holder);
					possibilities.removeFront();
					possibilities.insertRear(holder);
				}

				if(plan.getFoodCount() != 0)
			    repeat = adjustedGoalMealPlanTest(plan, possibilities, addTest, non_possible, req, HM, food_p_obj);

				if(repeat != 2)
					repeat = mealPlanCreator(plan, possibilities, addTest, non_possible, req, HM, food_p_obj);

			}while(!repeat);
			if(repeat != 2)
			{
				cout << endl << endl << "Here is your final meal plan!" << endl << endl;
				plan.displayPlan(false);
			}
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
		return yesorno();
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

void buildDatabase(Array<Food> &ary, HashMap<string, Food, MyKeyHash<string> >&HM, BinaryTree<Food> &calT, FoodProcessor &food_p_obj)
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
		food_p_obj.add(ary[i]);
		food_p_obj.getQuadrupleCount();
	}
}

void writeFile(HashMap<string, Food, MyKeyHash<string> >&HM)
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

void displayMealPlanMenu(bool version)
{
  if(version)
  {
    cout << endl << endl;
    cout << "Select an option." << endl << endl;
    cout << "A: Add a Food" << endl;
    cout << "B: Delete a Food" << endl;
    cout << "C: Adjust Goals" << endl;
    cout << "D: Search Foods" << endl;
    cout << "E: Empty Meal Plan" << endl;
    cout << "F: Display Meal Plan" << endl;
    cout << "G: Display Goals" << endl;
    cout << "H: Display Current Meal Plan Totals" << endl;
    cout << "I: I'm Finished!" << endl;
		cout << "J: Exit" << endl;
  }

  else
  {
    cout << endl << endl;
    cout << "Select an option." << endl << endl;
    cout << "A: Delete a Food" << endl;
    cout << "B: Adjust Goals" << endl;
    cout << "C: Search Foods" << endl;
    cout << "D: Empty Meal Plan" << endl;
    cout << "E: Display Meal Plan" << endl;
    cout << "F: Display Goals" << endl;
    cout << "G: Display Current Meal Plan Totals" << endl;
    cout << "H: I'm Finished!" << endl;
		cout << "I: Exit" << endl << endl;
  }
}

void addFoodOption(List<Food> &possibilities, MealPlan &plan, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req)
{
  bool dummy;
  Food start_value;
  int counter = 0, in_int;
  string in_str = "";
  Food *curr, *curr2;
  bool loopA;

  if(possibilities.getCount() == 0)
  {
    cout << endl << "No Possible Options Left!";
  }
  else
  {
    do
    {
      cout << endl << "Possible Options: " << endl << endl;
      start_value = *possibilities.getFirst();
      do
      {
        curr = possibilities.getFirst();
        possibilities.removeFront();
        cout << ++counter << ": " << curr->getName() << endl;
        possibilities.insertRear(curr);
      }while(!(*possibilities.getFirst() == start_value));
      cout << "B: Back" << endl;

      cout << endl << endl << "Enter the number of the food to be added to the meal plan." << endl << endl;
      cin >> in_str;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      if(in_str == "B" || in_str == "b")
        loopA = false;
      else
      {
        try
        {
          in_int = stoi(in_str);
          if(in_int < 1 || in_int > counter)
          {
            throw -1;
          }
          for(int i = 1; i < in_int; i++)
          {
            curr2 = possibilities.getFirst();
            possibilities.removeFront();
            possibilities.insertRear(curr2);
          }
          curr2 = possibilities.getFirst();
          possibilities.removeFront();
          plan.addFood(curr2);
          searchResults.emptyQueue();
          addTest.calIntersectTraverse(ADTStatic::loadQueue, searchResults, req.c_u - plan.getCurrCal(), req.c_u, req.f_u - plan.getCurrFat(), req.f_u, req.cb_u - plan.getCurrCarb(), req.cb_u, req.p_u - plan.getCurrProtein(), req.p_u);
          while(searchResults.front() != NULL)
          {
            if((searchResults.front())->getCalorie() != req.c_u - plan.getCurrCal() && (searchResults.front())->getFat() != req.f_u - plan.getCurrFat() && (searchResults.front())->getProtein() != req.p_u - plan.getCurrProtein() && (searchResults.front())->getCarb() != req.cb_u - plan.getCurrCarb())
            {
              possibilities.remove(searchResults.front(), dummy);
              non_possible.add(*searchResults.front());
            }
            searchResults.dequeue();
          }
          loopA = false;
        }
        catch(...)
        {
          cout << endl << "The value entered was invalid. Please try again." << endl << endl;
          loopA = true;
          counter = 0;
        }
      }
    }while(loopA);
  }
}

void deleteFoodOption(List<Food> &possibilities, MealPlan &plan, bool hard_delete, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req)
{
  string in_str;
  int in_int;
  bool repeat = false;
  Food *deleted_food;

  if(plan.getFoodCount())
  {
    do
    {
      cout << endl << "Select which food item to delete." << endl << endl;
      plan.displayPlan(true);
      cout << "B: Back" << endl;
      cout << endl << endl;
      cin >> in_str;
      if(in_str == "B")
        repeat = false;
      else
      {
        try
        {
          in_int = stoi(in_str);
          deleted_food = plan.getFood(in_int);
          if(deleted_food == NULL)
            throw -1;
          if(!hard_delete)
          {
            possibilities.insertRear(deleted_food);
            searchResults.emptyQueue();
            non_possible.calIntersectTraverse(ADTStatic::loadQueue, searchResults, req.c_u - plan.getCurrCal(), req.c_u + (plan.getFood(in_int))->getCalorie() - plan.getCurrCal(), req.f_u - plan.getCurrFat() + 1, req.f_u + (plan.getFood(in_int))->getFat() - plan.getCurrFat(), req.cb_u - plan.getCurrCarb(), req.cb_u + (plan.getFood(in_int))->getCarb() - plan.getCurrCarb(), req.p_u - plan.getCurrProtein(), req.p_u + (plan.getFood(in_int))->getProtein() - plan.getCurrProtein());
            while(searchResults.front() != NULL)
            {
              if((searchResults.front())->getCalorie() != req.c_u - plan.getCurrCal() && (searchResults.front())->getFat() != req.f_u - plan.getCurrFat() && (searchResults.front())->getProtein() != req.p_u - plan.getCurrProtein() && (searchResults.front())->getCarb() != req.cb_u - plan.getCurrCarb())
              {
                possibilities.insertRear(searchResults.front());
                addTest.add(*searchResults.front());
                non_possible.remove(*searchResults.front());
              }
            }
          }
          plan.deleteFood(in_int);
          repeat = false;
        }
        catch(...)
        {
          cout << endl << "The value entered was invalid. Please try again." << endl;
          repeat = true;
        }
      }
    }while(repeat);
  }
  else
  {
    cout << endl << "Meal Plan is currently empty!" << endl;
  }
}

void displayGoalsOption(Requirements req)
{
  cout << endl << endl << "Current Goals: ";
  cout << endl << endl << "Calories: " << req.c_l << " - " << req.c_u << endl;
  cout << endl << "Fat: " << req.f_l << " - " << req.f_u << endl;
  cout << endl << "Carbohydrates: " << req.cb_l << " - " << req.cb_u << endl;
  cout << endl << "Protein: " << req.p_l << " - " << req.p_u << endl;
}

void displayCurrentTotalsOption(MealPlan &plan)
{
  cout << endl << endl << "Current Totals: ";
  cout << endl << endl << "Calories: " << plan.getCurrCal() << endl;
  cout << endl << "Fat: " << plan.getCurrFat() << endl;
  cout << endl << "Carbohydrates: " << plan.getCurrCarb() << endl;
  cout << endl << "Protein: " << plan.getCurrProtein() << endl;
}

void displayMealPlanOption(MealPlan &plan)
{
  if(!plan.getFoodCount())
    cout << endl << "Meal Plan empty!" << endl << endl;
  else
  {
    cout << endl << "Meal Plan: " << endl;
    plan.displayPlan(false);
    cout << endl;
  }
}

void emptyMealPlanOption(MealPlan &plan, List<Food> &possibilities)
{
  if(!plan.getFoodCount())
    cout << endl << "Meal Plan is already empty!" << endl;
  else
  {
    while(plan.getFoodCount())
    {
      possibilities.insertRear(plan.getFirstFood());
      plan.deleteFood(1);
    }
    cout << endl << "Emptied!" << endl;
  }
}

void foodDisplayer(Food food)
{
  cout << endl << "Name: " << food.getName() << endl;
  cout << "Calories: " << food.getCalorie() << endl;
  cout << "Fat: " << food.getFat() << endl;
  cout << "Protein: " << food.getProtein() << endl;
}

void searchFoodsOption(HashMap<string, Food, MyKeyHash<string> > &HM, FoodProcessor &food_p_obj)
{
  char answer;
  string in_str_low, in_str_up, name;
  int in_int_low, in_int_up;
  bool repeat = true, big_repeat = true, dummy;
  Food obj1;

  do
  {
    cout << endl << "What would you like to search by?" << endl << endl;
    cout << "A: By Name" << endl;
    cout << "B: By Calories" << endl;
    cout << "C: By Protein" << endl;
    cout << "D: By Total Fat" << endl;
    cout << "E: By Carbohydrates" << endl;
    cout << "F: Back" << endl << endl;

    cin >> answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    searchResults.emptyQueue();

    if(answer == 'A' || answer == 'a')
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

    else if(answer == 'B' || answer == 'b' || answer == 'C' || answer == 'c' || answer == 'D' || answer == 'd' || answer == 'E' || answer == 'e')
    {
      do
      {
        try
        {
          cout << endl << endl << "Enter the lower bound for the search range." << endl;
          cin >> in_str_low;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          in_int_low = stoi(in_str_low);
          if(in_int_low < 0)
            throw -1;

          cout << endl << endl << "Enter the upper bound for the search range." << endl;
          cin >> in_str_up;
          cin.ignore(numeric_limits<streamsize>::max(), '\n');

          in_int_up = stoi(in_str_up);
          if(in_int_up < 0 || in_int_low > in_int_up)
            throw -1;

          if(answer == 'B' || answer == 'b')
          {
            food_p_obj.calRangeTraverse(ADTStatic::loadQueue, searchResults, in_int_low, in_int_up);
            repeat = false;
          }

          else if(answer == 'C' || answer == 'c')
          {
            food_p_obj.protRangeTraverse(ADTStatic::loadQueue, searchResults, in_int_low, in_int_up);
            repeat = false;
          }

          else if(answer == 'D' || answer == 'd')
          {
            food_p_obj.fatRangeTraverse(ADTStatic::loadQueue, searchResults, in_int_low, in_int_up);
            repeat = false;
          }

          else
          {
            food_p_obj.carbRangeTraverse(ADTStatic::loadQueue, searchResults, in_int_low, in_int_up);
            repeat = false;
          }

          if(searchResults.front() == NULL)
            cout << endl << "No foods meet your search criteria!" << endl << endl;
          else
          {
            cout << endl << "Search Results:" << endl;
            while(searchResults.front() != NULL)
            {
              foodDisplayer(*searchResults.front());
              searchResults.dequeue();
            }
          }

        }
        catch(...)
        {
          cout << endl << "The value entered was invalid. Please try again." << endl;
          repeat = true;
        }
      }while(repeat);
      big_repeat = false;
    }

    else if(answer == 'F' || answer == 'f')
    {
      cout << endl << endl;
      big_repeat = false;
    }

    else
    {
      cout << endl << "The value entered was invalid. Please try again." << endl;
      big_repeat = true;
    }
  }while(big_repeat);
}

int adjustedGoalMealPlanTest(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashMap<string, Food, MyKeyHash<string> > &HM, FoodProcessor &food_p_obj)
{
  bool OptionH;
  bool OptionB = false;
  char answer;
	bool hard_exit = false;

  while(!OptionB && !hard_exit && (plan.getCurrCal() > req.c_u || plan.getCurrFat() > req.f_u || plan.getCurrCarb() > req.cb_u || plan.getCurrProtein() > req.p_u))
  {
    if(!OptionB && !hard_exit)
    {
      OptionH = false;
      cout << endl << "Your current meal plan totals are out of your goal ranges. Please adjust your meal plan." << endl;
      while(!OptionH)
      {
        displayMealPlanMenu(false);

        cin >> answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(answer == 'A' || answer == 'a')
        {
          deleteFoodOption(possibilities, plan, true, addTest, non_possible, req);
        }

        else if(answer == 'B' || answer == 'b')
        {
          OptionB = true;
        }

        else if(answer == 'C' || answer == 'c')
        {
          searchFoodsOption(HM, food_p_obj);
        }

        else if(answer == 'D' || answer == 'd')
        {
          emptyMealPlanOption(plan, possibilities);
        }

        else if(answer == 'E' || answer == 'e')
        {
          displayMealPlanOption(plan);
        }

        else if(answer == 'F' || answer == 'f')
        {
          displayGoalsOption(req);
        }

        else if(answer == 'G' || answer == 'g')
        {
          displayCurrentTotalsOption(plan);
        }

        else if(answer == 'H' || answer == 'h')
        {
          OptionH = true;
        }

				else if(answer == 'I' || answer == 'i')
				{
					hard_exit = true;
				}

        else
        {
          cout << endl << "The value entered was invalid. Please try again." << endl;
        }
      }
    }
  }
  if(!OptionB)
    cout << endl << endl << "Your current meal plan is within your goal range!" << endl;
	if(OptionH)
  	return 2;
	else if(OptionB)
		return 0;
	else
		return 1;
}

int mealPlanCreator(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashMap<string, Food, MyKeyHash<string> > &HM, FoodProcessor &food_p_obj)
{
  char answer;
  int counter;
  bool loop_again = true;

  do
  {
    counter = 0;
    displayMealPlanMenu();

    cin >> answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(answer == 'A' || answer == 'a')
    {
      addFoodOption(possibilities, plan, addTest, non_possible, req);
    }

    else if(answer == 'B' || answer == 'b')
    {
      deleteFoodOption(possibilities, plan, false, addTest, non_possible, req);
    }

    else if(answer == 'C' || answer == 'c')
    {
      return 0;
    }

    else if(answer == 'D' || answer == 'd')
    {
      searchFoodsOption(HM, food_p_obj);
    }

    else if(answer == 'E' || answer == 'e')
    {
      emptyMealPlanOption(plan, possibilities);
    }

    else if(answer == 'F' || answer == 'f')
    {
      displayMealPlanOption(plan);
    }

    else if(answer == 'G' || answer == 'g')
    {
      displayGoalsOption(req);
    }

    else if(answer == 'H' || answer == 'h')
    {
      displayCurrentTotalsOption(plan);
    }

    else if(answer == 'I' || answer == 'i')
    {
      if(plan.getCurrCal() >= req.c_l && plan.getCurrFat() > req.f_l && plan.getCurrCarb() > req.cb_l && plan.getCurrProtein() > req.p_l)
      {
        return 1;
      }
      else
      {
        cout << endl << endl << "Your goals have not been met!" << endl;
        loop_again = true;
      }
    }

		else if(answer == 'J' || answer == 'j')
    {
			return 2;
		}

    else
    {
      cout << endl << "The value entered was invalid. Please try again.";
      loop_again = true;
    }
  }while(loop_again);
}


void searchVisitor(Food &obj)
{
  searchResults.enqueue(&obj);
}

void possibilitiesGetter(FoodProcessor &food_p_obj, Requirements req, List<Food> &possibilities)
{
	food_p_obj.calIntersectTraverse(ADTStatic::loadLinkedList, possibilities, req.c_l, req.c_u, req.f_l, req.f_u, req.cb_l, req.cb_u, req.p_l, req.p_u);
}

void possibilityVisitor(Food &obj)
{
	possibilities.insertRear(&obj);
}

Requirements getBounds()
{
	Requirements req;
	string in_str;
	bool repeat = true;
	do
	{
		try
		{
			cout << endl << "Enter the requirements for your meal plan!" << endl;
			cout << endl << "Lower Bound for Calories: ";
			cin >> in_str;
			req.c_l = stoi(in_str);
			if(req.c_l < 0)
				throw -1;
			cout << endl << "Upper Bound for Calories: ";
			cin >> in_str;
			req.c_u = stoi(in_str);
			if(req.c_u < 0)
				throw -1;
			cout << endl << "Lower Bound for Fat: ";
			cin >> in_str;
			req.f_l = stoi(in_str);
			if(req.f_l < 0)
				throw -1;
			cout << endl << "Upper Bound for Fat: ";
			cin >> in_str;
			req.f_u = stoi(in_str);
			if(req.f_u < 0)
				throw -1;
			cout << endl << "Lower Bound for Carbohydrates: ";
			cin >> in_str;
			req.cb_l = stoi(in_str);
			if(req.cb_l < 0)
				throw -1;
			cout << endl << "Upper Bound for Carbohydrates: ";
			cin >> in_str;
			req.cb_u = stoi(in_str);
			if(req.cb_u < 0)
				throw -1;
			cout << endl << "Lower Bound for Protein: ";
			cin >> in_str;
			req.p_l = stoi(in_str);
			if(req.p_l < 0)
				throw -1;
			cout << endl << "Upper Bound for Protein: ";
			cin >> in_str;
			req.p_u = stoi(in_str);
			if(req.p_u < 0)
				throw -1;
			repeat = false;
		}
		catch(...)
		{
			cout << endl << "The value entered was invalid. Please try again." << endl;
			repeat = true;
		}
	}while(repeat);
	return req;
}
