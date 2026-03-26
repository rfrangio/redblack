#include <iostream>
#include <random>

#include "redblack.h"
// Author: Robert B Frangios

const uint32_t range = std::numeric_limits<uint32_t>::max();
const uint32_t NUM_OBJECTS = 10000000;
 
std::default_random_engine generator;
std::uniform_int_distribution<uint32_t> distribution(0,range);

int main()
{
	RedBlackTree<uint32_t> rbtree;
	RedBlackTree<char> rbctree;
	uint32_t dups = 0;
	int left_tree = 0, right_tree = 0;
	uint32_t res = 0;

/////   Worst case insertion order showing worst case height imbalance of 2/1  ////////////////////////////////////

	dups = left_tree = right_tree = 0;

	std::cout << "Inserting " << NUM_OBJECTS << " monotonically increasing objects \n";
 
	for(uint32_t i = 0; i < NUM_OBJECTS; i++) {
		if(!rbtree.Insert(i)) {
			dups++;
		}
	}

	std::cout << "After insert phase rbtree has " << rbtree.NodeCount() + dups << " nodes \n";
	rbtree.GetSubtreeDepths(&left_tree, &right_tree);
	std::cout << "left subtree depth " << left_tree << " right subtree depth " << right_tree << " \n";

	while(rbtree.RemoveMaximum(&res)) {}

	std::cout << "After delete phase rbtree has " << rbtree.NodeCount() << " nodes  \n";

	std::cout << "Inserting " << NUM_OBJECTS << " random objects \n";
	dups = left_tree = right_tree = 0;
 
	for(uint32_t i = 0; i < NUM_OBJECTS; i++) {
		if(!rbtree.Insert(distribution(generator))) {
			dups++;
		}
	}

	std::cout << "After insert phase rbtree has " << rbtree.NodeCount() + dups << " nodes \n";
	rbtree.GetSubtreeDepths(&left_tree, &right_tree);
	std::cout << "left subtree depth " << left_tree << " right subtree depth " << right_tree << " \n";

	while(rbtree.RemoveMaximum(&res)) {}

	std::cout << "After delete phase rbtree has " << rbtree.NodeCount() << " nodes  \n";
}
