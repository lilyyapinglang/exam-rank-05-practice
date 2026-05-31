#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() : array_bag()
{
}

searchable_array_bag::searchable_array_bag(searchable_array_bag const &other)
	: array_bag(other)
{
}

searchable_array_bag &searchable_array_bag::operator=(searchable_array_bag const &other)
{
	if (this != &other)
		array_bag::operator=(other);
	return (*this);
}

searchable_array_bag::~searchable_array_bag()
{
}

bool searchable_array_bag::has(int value) const
{
	int i;

	i = 0;
	while (i < size)
	{
		if (data[i] == value)
			return (true);
		i++;
	}
	return (false);
}