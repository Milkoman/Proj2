#include "FoodProcessor.hpp"
#include "ADTStatic.hpp"

void FoodProcessor::intersect(void visit(Food &) , bool LGR(const Food &, const Food &), Food & minF, Food & maxF)
{

	BinaryTree<Food> tree1;
	BinaryTree<Food> tree2;

	calTree.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree1, Food::calorieLGreaterR, Food::fatLGreaterR, minF, maxF);

	tree1.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree2, Food::fatLGreaterR, Food::carbLGreaterR, minF, maxF);
	tree1.clear();

	tree2.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree1, Food::carbLGreaterR, Food::proteinLGreaterR, minF, maxF);

	tree2.clear();
	tree1.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree2, Food::proteinLGreaterR, LGR, minF, maxF);
	tree2.inorderTraverse(visit);
}







FoodProcessor::FoodProcessor()
{
}

FoodProcessor::~FoodProcessor()
{
}

bool FoodProcessor::replace(Food& foodIn, Food & foodOut)
{
	return calTree.replace(foodIn, foodOut, Food::completeLEqualR, Food::calorieLGreaterR) && fatTree.replace(foodIn, foodOut, Food::completeLEqualR, Food::fatLGreaterR)
		&& carbTree.replace(foodIn, foodOut, Food::completeLEqualR, Food::carbLGreaterR) && protTree.replace(foodIn, foodOut, Food::completeLEqualR, Food::proteinLGreaterR);
}

void FoodProcessor::calRangeTraverse(void visit(Food &), int min, int max)
{
	Food minF;
	Food maxF;
	minF.setCalorie(min);
	maxF.setCalorie(max);
	calTree.inorderBoundedTraverse(visit, Food::calorieLGreaterR, minF, maxF);
}

void FoodProcessor::fatRangeTraverse(void visit(Food &), int min, int max)
{
	Food minF;
	Food maxF;
	minF.setFat(min);
	maxF.setFat(max);
	fatTree.inorderBoundedTraverse(visit, Food::fatLGreaterR, minF, maxF);
}

void FoodProcessor::carbRangeTraverse(void visit(Food &), int min, int max)
{
	Food minF;
	Food maxF;
	minF.setCarb(min);
	maxF.setCarb(max);
	carbTree.inorderBoundedTraverse(visit, Food::carbLGreaterR, minF, maxF);
}

void FoodProcessor::protRangeTraverse(void visit(Food &), int min, int max)
{
	Food minF;
	Food maxF;
	minF.setProtien(min);
	maxF.setProtien(max);
	protTree.inorderBoundedTraverse(visit, Food::proteinLGreaterR, minF, maxF);
}

void FoodProcessor::calIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, Food::calorieLGreaterR, minF, maxF);
}



void FoodProcessor::fatIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, Food::fatLGreaterR, minF, maxF);
}



void FoodProcessor::carbIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, Food::carbLGreaterR, minF, maxF);
}



void FoodProcessor::protIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, Food::proteinLGreaterR, minF, maxF);
}



void FoodProcessor::add(Food &food)
{
	calTree.add(food, Food::calorieLGreaterR);
	fatTree.add(food, Food::fatLGreaterR);
	carbTree.add(food, Food::carbLGreaterR);
	protTree.add(food, Food::proteinLGreaterR);
}

bool FoodProcessor::remove(Food& food)
{
	return calTree.remove(food, Food::completeLEqualR, Food::calorieLGreaterR) && fatTree.remove(food, Food::completeLEqualR, Food::fatLGreaterR) && carbTree.remove(food, Food::completeLEqualR, Food::carbLGreaterR) && protTree.remove(food, Food::completeLEqualR, Food::proteinLGreaterR);
}
