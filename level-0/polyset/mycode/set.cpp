#include "set.hpp"
#include <iostream>

set::set(searchable_bag &bag) : bag(bag)
{
}

set::set(const set &copy) : bag(copy.bag)
{
}

set &set::operator=(const set &other)
{
	if (this != &other)
		this->bag = other.bag;
	return (*this);
}

set::~set()
{
}

void set::insert(int value)
{
	if (!bag.has(value))
		bag.insert(value);
}

void set::insert(int *items, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!bag.has(items[i]))
			bag.insert(items[i]);
	}
}

void set::print() const
{
	bag.print();
}

void set::clear()
{
	bag.clear();
}

bool set::has(int value) const
{
	return (bag.has(value));
}

const searchable_bag &set::get_bag() const
{
	return (bag);
}