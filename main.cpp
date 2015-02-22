#include <iostream>
#include <random>
#include "redblack.h"

const int range = std::numeric_limits<int>::max();
const unsigned int NUM_OBJECTS = 10000000;
 
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0,range);
auto roll = std::bind ( distribution, generator );

template<typename T>
int cmp(T* a, T* b)
{
	if(*a == *b) 
		return 0;

	return *a < *b ? -1 : 1; 
}

int main()
{
	RedBlackTree<int> rbtree(cmp);
	int dups = 0, depth = 0;
	int left_tree = 0, right_tree = 0;
	for(int i = 0; i < NUM_OBJECTS; i++) {
		int *entry = new(int);
		*entry = roll();
		//std::cout << "inserting " << *entry << " \n";
		if(!rbtree.Insert(entry)) {
			dups++;
		}
	}

	std::cout << "After insert phase rbtree has " << rbtree.NodeCount() + dups << " nodes \n";

	rbtree.GetSubtreeDepths(&left_tree, &right_tree);
	std::cout << "left subtree depth " << left_tree << " right subtree depth " << right_tree << " \n";

	rbtree.DoWalk();	

	int *res = 0;
	while((res = rbtree.RemoveMaximum())) {
		//std::cout << "Max ele " << *res << " \n";
		delete res;
	}

	depth = 0;
	std::cout << "After delete phase rbtree has " << rbtree.NodeCount() 
				<< " nodes  \n";
}
