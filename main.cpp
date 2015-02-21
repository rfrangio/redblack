#include <iostream>
#include <random>
#include "redblack.h"

const int range = std::numeric_limits<int>::max();
const unsigned int NUM_OBJECTS = 1000000;
 
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
	RedBlackTree<int32_t> rbtree(cmp);
	for(int i = 0; i < NUM_OBJECTS; i++) {
		int *entry = new(int);
		*entry = roll();
		//std::cout << "inserting " << *entry << " \n";
		rbtree.Insert(entry);
	}

	//rbtree.DoWalk();	

	int *res = 0;
	while((res = rbtree.RemoveMaximum())) {
		//std::cout << "Max ele " << *res << " \n";
		delete res;
	}
}