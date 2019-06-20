#ifndef MEAL_PLAN_H
#define MEAL_PLAN_H

#include "List.h"
#include "Food.hpp"
#include "Node.h"
#include <string>

class MealPlan : protected List<Food>
{
private:
  int curr_calorie;
  int curr_fat;
  int curr_carb;
  int curr_protein;

public:
  MealPlan(){curr_calorie = 0; curr_fat = 0; curr_carb = 0; curr_protein = 0;}
  void addFood(Food *obj){this->insertFront(obj); curr_calorie += obj->getCalorie(); curr_fat += obj->getFat(); curr_carb += obj->getCarb(); curr_protein += obj->getProtein();}
  void deleteFood(int pos){Food *obj = getFood(pos); this->remove(pos); curr_calorie -= obj->getCalorie(); curr_fat -= obj->getFat(); curr_carb -= obj->getCarb(); curr_protein -= obj->getProtein();}
  void displayPlan(bool a){this->display(a);}
  void emptyPlan(){this->empty();}
  int getCurrCal(){return curr_calorie;}
  int getCurrProtein(){return curr_protein;}
  int getCurrFat(){return curr_fat;}
  int getCurrCarb(){return curr_carb;}
  int getFoodCount(){return this->getCount();}
  Food *getFirstFood(){return (this->getHead())->getData();}


  template <typename U>
  U planIterator(U func(Food *obj, U), U start_val){return this->iterator(func, start_val);}
  Food *getFood(int pos){Food *node_data = NULL; Node<Food> *ptr = this->getNodePTR(pos); if(ptr != NULL){node_data = ptr->getData();} return node_data;}

};

#endif
