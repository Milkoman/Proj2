#include <iostream>
#include "MealPlan.h"
#include <string>
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

void setRequirements(Food min, Food max, Requirements req);
void searchVisiter(Food &obj);
bool mealPlanCreater(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashTable<sting, Food, MyKeyHash> &HM, FoodProcessor &food_p_obj);
bool adjustedGoalMealPlanTest(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashTable<sting, Food, MyKeyHash> &HM, FoodProcessor &food_p_obj);
void searchFoodsOption(HashTable<sting, Food, MyKeyHash> &HM, FoodProcessor &food_p_obj);
void foodDisplayer(Food food);
void emptyMealPlanOption(MealPlan &plan, List<Food> &possibilities);
void displayMealPlanOption(MealPlan &plan);
void displayCurrentTotalsOption(MealPlan &plan);
void displayGoalsOption(Requirements req);
void deleteFoodOption(List<Food> &possibilities, MealPlan &plan, bool hard_delete, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req);
void addFoodOption(List<Food> &possibilities, MealPlan &plan, FoodProcessor &addTest, FoodProcessor &non_possibile, Requirements req);
void displayMealPlanMenu(bool version = true);


Queue<Food> searchResults;

int main()
{
  //note: queue on line 48 needs to be global


  //should already be available from olly's code
  Food min;
  Food max;

  //these lines should be at beginning of program
  MealPlan plan;
  FoodProcessor non_possible;

  //this should be the food processor object with everything in it
  FoodProcessor food_p_obj

  //this should be the last food processor object (ie FoodProcessor with only foods that meet requirements)
  FoodProcessor addTest;

  //this variable should just be the variable that is used in the huge while loop
  bool x;

  Requirements req;
  setRequirements(min, max, req);

  //if x or y is true, go to the beginning of program where we ask user for goals; if false, we end program by printing final food plan or something
  if(plan.getFoodCount())
  {
    x = adjustedGoalMealPlanTest(plan, possibilities);
  }

  x = mealPlanCreater(plan, possibilities);


  return 0;
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
    cout << "I: I'm Finished!" << endl << endl;
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
    cout << "H: I'm Finished!" << endl << endl;
  }
}

void addFoodOption(List<Food> &possibilities, MealPlan &plan, FoodProcessor &addTest, FoodProcessor &non_possibile, Requirements req)
{
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
      cin.ignore(256, '\n');
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
          addTest.calIntersectTraverse(searchResults, req.c_u - plan.getCurrCal(), req.c_u, req.f_u - plan.getCurrFat(), req.f_u, req.cb_u - plan.getCurrCarb(), req.cb_u, req.p_u - plan.getCurrProtein(), req.p_u)
          while(searchResults.front() != NULL)
          {
            if((searchResults.front())->getCalorie() != req.c_u - plan.getCurrCal() && (searchResults.front())->getFat() != req.f_u - plan.getCurrFat() && (searchResults.front())->getProtein() != req.p_u - plan.getCurrProtein() && (searchResults.front())->getCarb() != req.cb_u - plan.getCurrCarb())
            {
              possibilities.remove(searchResults.front());
              non_possibile.add(*searchResults.front());
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
            non_possibile.calIntersectTraverse(deleteSearchResults, req.c_u - plan.getCurrCal(), req.c_u + (plan.getFood(in_int))->getCalorie() - plan.getCurrCal(), req.f_u - plan.getCurrFat() + 1, req.f_u + (plan.getFood(in_int))->getFat() - plan.getCurrFat(), req.cb_u - plan.getCurrCarb(), req.cb_u + (plan.getFood(in_int))->getCarb() - plan.getCurrCarb(), req.p_u - plan.getCurrProtein(), req.p_u + (plan.getFood(in_int))->getProtein() - plan.getCurrProtein());
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

void searchFoodsOption(HashTable<sting, Food, MyKeyHash> &HM, FoodProcessor &food_p_obj)
{
  char answer;
  string in_str_low, in_str_up, name;
  int in_int_low, in_int_up;
  bool repeat = true;
  bool big_repeat = true;
  Food obj, obj1;

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
    cin.ignore(256, '\n');

    searchResults.emptyQueue();

    if(answer == 'A' || answer == 'a')
    {
      cout << endl << endl << "Enter the name of the food." << endl << endl;
      cin.ignore();
      getline(cin, name);
      obj = HM.get(name, obj1);
      obj.foodDisplayer();
      cout << endl;
      big_repeat = false;
    }

    else if(answer == 'B' || answer == 'b' || answer == 'C' || answer == 'c' || answer == 'D' || answer == 'd' || answer == 'E' || answer == 'e')
    {
      do
      {
        cout << endl << endl << "Enter the lower bound for the search range." << endl;
        cin >> in_str_low;
        cin.ignore(256, '\n');

        cout << endl << endl << "Enter the upper bound for the search range." << endl;
        cin >> in_str_up;
        cin.ignore(256, '\n');

        try
        {
          in_int_up = stoi(in_str_up);
          if(in_int_up < 0)
            throw -1;
          in_int_low = stoi(in_int_low);
          if(in_int_low < 0 || in_int_low > in_int_up)
            throw -1;

          if(answer == 'B' || answer == 'b')
          {
            food_p_obj.calRangeTraverse(searchVisiter, in_int_low, in_int_up);
            repeat = false;
          }

          else if(answer == 'C' || answer == 'c')
          {
            food_p_obj.protRangeTraverse(searchVisiter, in_int_low, in_int_up);
            repeat = false;
          }

          else if(answer == 'D' || answer == 'd')
          {
            food_p_obj.fatRangeTraverse(searchVisiter, in_int_low, in_int_up);
            repeat = false;
          }

          else
          {
            food_p_obj.carbRangeTraverse(searchVisiter, in_int_low, in_int_up);
            repeat = false;
          }

          if(searchResults.front() == NULL)
          {
            cout << endl << "No foods meet your search criteria!" << endl << endl;
          }
          cout << endl << "Search Results:" << endl;
          while(searchResults.front() != NULL)
          {
            foodDisplayer(*searchResults.front());
            searchResults.dequeue();
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

bool adjustedGoalMealPlanTest(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashTable<sting, Food, MyKeyHash> &HM, FoodProcessor &food_p_obj)
{
  bool OptionH;
  bool OptionB = false;
  char answer;

  while(!OptionB && (plan.getCurrCal() > req.c_u || plan.getCurrFat() > req.f_u || plan.getCurrCarb() > req.cb_u || plan.getCurrProtein() > req.p_u))
  {
    if(!OptionB)
    {
      OptionH = false;
      cout << endl << "Your current meal plan totals are out of your goal ranges. Please adjust your meal plan." << endl;
      while(!OptionH)
      {
        displayMealPlanMenu(false);

        cin >> answer;
        cin.ignore(256, '\n');

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

        else
        {
          cout << endl << "The value entered was invalid. Please try again." << endl;
        }
      }
    }
  }
  if(!OptionB)
    cout << endl << endl << "Your current meal plan is within your goal range!" << endl;
  return OptionB;
}

bool mealPlanCreater(MealPlan &plan, List<Food> &possibilities, FoodProcessor &addTest, FoodProcessor &non_possible, Requirements req, HashTable<sting, Food, MyKeyHash> &HM, FoodProcessor &food_p_obj)
{
  char answer;
  int counter;
  bool loop_again = true;

  do
  {
    counter = 0;
    displayMealPlanMenu();

    cin >> answer;
    cin.ignore(256, '\n');

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
      return true;
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
        return false;
      }
      else
      {
        cout << endl << endl << "Your goals have not been met!" << endl;
        loop_again = true;
      }
    }

    else
    {
      cout << endl << "The value entered was invalid. Please try again.";
      loop_again = true;
    }
  }while(loop_again);
}

void searchVisiter(Food &obj)
{
  searchResults.enqueue(&obj);
}

void setRequirements(Food min, Food max, Requirements req)
{
  req.c_l = min.getCalorie();
  req.c_u = max.getCalorie();
  req.f_l = min.getFat();
  req.f_u = max.getFat();
  req.cb_l = min.getCarb();
  req.cb_u = max.getCarb();
  req.p_l = min.getProtein();
  req.p_u = max.getProtein();
}
