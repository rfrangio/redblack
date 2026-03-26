#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "redblack.h"

template<typename T>
int cmp(const T &a, const T &b)
{
	if (a == b)
		return 0;

	return a < b ? -1 : 1;
}

static void test_empty_tree()
{
	RedBlackTree<uint32_t> tree(cmp);
	uint32_t key = 1;

	assert(tree.NodeCount() == 0);
	assert(tree.Minimum() == 0);
	assert(tree.Maximum() == 0);
	assert(tree.Lookup(key) == 0);
}

static void test_insert_lookup_and_duplicates()
{
	RedBlackTree<uint32_t> tree(cmp);

	for (uint32_t value : {10U, 5U, 20U, 15U}) {
		assert(tree.Insert(value) == 1);
	}

	uint32_t key = 15;
	assert(tree.Lookup(key) != 0);
	assert(*tree.Minimum() == 5);
	assert(*tree.Maximum() == 20);
	assert(tree.NodeCount() == 4);

	assert(tree.Insert(15) == 0);
}

static void test_delete_node_with_two_children()
{
	RedBlackTree<uint32_t> tree(cmp);

	for (uint32_t value : {20U, 10U, 30U, 5U, 15U, 25U, 35U}) {
		assert(tree.Insert(value) == 1);
	}

	uint32_t key = 20;
	uint32_t removed = 0;
	assert(tree.Delete(key, &removed));
	assert(removed == 20);

	assert(tree.NodeCount() == 6);
	assert(*tree.Minimum() == 5);
	assert(*tree.Maximum() == 35);

	uint32_t missing = 20;
	assert(tree.Lookup(missing) == 0);
}

static void test_remove_maximum_order()
{
	RedBlackTree<uint32_t> tree(cmp);

	for (uint32_t value : {8U, 3U, 10U, 1U, 6U, 14U, 4U, 7U, 13U}) {
		assert(tree.Insert(value) == 1);
	}

	std::vector<uint32_t> removed;
	uint32_t value = 0;
	while (tree.RemoveMaximum(&value)) {
		removed.push_back(value);
	}

	assert((removed == std::vector<uint32_t>{14U, 13U, 10U, 8U, 7U, 6U, 4U, 3U, 1U}));
	assert(tree.NodeCount() == 0);
	assert(tree.Minimum() == 0);
	assert(tree.Maximum() == 0);
}

int main()
{
	test_empty_tree();
	test_insert_lookup_and_duplicates();
	test_delete_node_with_two_children();
	test_remove_maximum_order();

	std::cout << "tests passed\n";
	return 0;
}
