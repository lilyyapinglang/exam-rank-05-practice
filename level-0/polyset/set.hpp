#ifndef SET_HPP
# define SET_HPP

# include "searchable_bag.hpp"

class set
{
	private:
		searchable_bag *bag;

	public:
		set();
		set(searchable_bag &source);
		set(set const &other);
		set &operator=(set const &other);
		~set();

		void insert(int value);
		void insert(int *array, int size);
		void print() const;
		void clear();
		bool has(int value) const;

		searchable_bag &get_bag();
		searchable_bag const &get_bag() const;
};

#endif