#ifndef FOODPROCESSOR_H
#define FOODPROCESSOR_H
#include "BinaryTree.hpp"
#include "ADTStatic.hpp"
#include "Food.hpp"
#include "Queue.hpp"

class FoodProcessor
{
private:
	BinaryTree<Food> calTree;
	BinaryTree<Food> fatTree;
	BinaryTree<Food> carbTree;
	BinaryTree<Food> protTree;
	void intersect(void visit(Food &), bool LGR(const Food &, const Food &), Food & minF, Food & maxF);

	template<template <class V> class U>
	void intersect(void visit(U<Food> &, Food &), U<Food> & obj, bool LGR(const Food &, const Food &), Food & minF, Food & maxF);
	
public:
	FoodProcessor();
	~FoodProcessor();

	bool replace(Food&, Food&);
	void calRangeTraverse(void visit(Food &), int min, int max);
	void fatRangeTraverse(void visit(Food &), int min, int max);
	void carbRangeTraverse(void visit(Food &), int min, int max);
	void protRangeTraverse(void visit(Food &), int min, int max);

	void calIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);
	void fatIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);
	void carbIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);
	void protIntersectTraverse(void visit(Food &), int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);

	template<template <class V> class U>
	void calIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj,int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);
	template<template <class V> class U>
	void fatIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj, int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);
	template<template <class V> class U>
	void carbIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj, int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);
	template<template <class V> class U>
	void protIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj, int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt);

	int getNumFoods() { return calTree.getNumNodes(); };

	void add(Food &);
	bool remove(Food&);

	Food & search(Food & data) { return calTree.search(data, Food::completeLEqualR, Food::calorieLGreaterR); };

	
};

template<template<class V> class U>
inline void FoodProcessor::intersect(void visit(U<Food> &, Food &), U<Food>& obj, bool LGR(const Food &, const Food &), Food & minF, Food & maxF)
{
	BinaryTree<Food> tree1;
	BinaryTree<Food> tree2;

	calTree.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree1, Food::calorieLGreaterR, Food::fatLGreaterR, minF, maxF);

	tree1.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree2, Food::fatLGreaterR, Food::carbLGreaterR, minF, maxF);
	tree1.clear();

	tree2.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree1, Food::carbLGreaterR, Food::proteinLGreaterR, minF, maxF);
	
	tree2.clear();
	tree1.inorderBoundedTraverse(ADTStatic::loadBinaryTree, tree2, Food::proteinLGreaterR, LGR, minF, maxF);
	tree2.inorderTraverse(visit, obj);
}



template<template <class V> class U>
inline void FoodProcessor::calIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj, int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, obj, Food::calorieLGreaterR, minF, maxF);
}

template<template <class V> class U>
inline void FoodProcessor::fatIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj, int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, obj, Food::fatLGreaterR, minF, maxF);
}
template<template <class V> class U>
inline void FoodProcessor::carbIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj, int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, obj, Food::carbLGreaterR, minF, maxF);
}

template<template <class V> class U>
inline void FoodProcessor::protIntersectTraverse(void visit(U<Food> &, Food &), U<Food> & obj, int minCal, int maxCal, int minFat, int maxFat, int minCarb, int maxCarb, int minProt, int maxProt)
{
	Food minF("", minCal, minFat, minCarb, minProt);
	Food maxF("", maxCal, maxFat, maxCarb, maxProt);
	intersect(visit, obj, Food::proteinLGreaterR, minF, maxF);
}

#endif // !FOODPROCESSOR_H


