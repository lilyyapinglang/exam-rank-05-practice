#include "set.hpp"
#include <iostream>

set::set() : bag(0)
{
}
set::set(searchable_bag &bag) : bag(&bag)
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
	if (bag == 0)
		return ;
	if (bag->has(value) == false)
		bag->insert(value);
}

void set::insert(int *items, int count)
{
	if (bag == 0)
		return ;
	for (int i = 0; i < count; i++)
	{
		if (bag->has(items[i]) == false)
			bag->insert(items[i]);
	}
}

void set::print() const
{
	if (bag == 0)
		return ;
	bag->print();
}

void set::clear()
{
	if (bag == 0)
		return ;
	bag->clear();
}

bool set::has(int value) const
{
	if (bag == 0)
		return (false);
	return (bag->has(value));
}

const searchable_bag &set::get_bag() const
{
	return (*bag);
}

searchable_bag &set::get_bag()
{
	return (*bag);
}