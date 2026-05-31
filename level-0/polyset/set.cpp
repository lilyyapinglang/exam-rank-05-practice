#include "set.hpp"

set::set() : bag(0)
{
}

set::set(searchable_bag &source) : bag(&source)
{
}

set::set(set const &other) : bag(other.bag)
{
}

set &set::operator=(set const &other)
{
	if (this != &other)
		bag = other.bag;
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

void set::insert(int *array, int size)
{
	int i;

	if (bag == 0)
		return ;
	i = 0;
	while (i < size)
	{
		insert(array[i]);
		i++;
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

searchable_bag &set::get_bag()
{
	return (*bag);
}

searchable_bag const &set::get_bag() const
{
	return (*bag);
}