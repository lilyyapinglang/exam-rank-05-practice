#pragma once
#include "searchable_bag.hpp"

class set
{
  private:
	searchable_bag *bag;

  public:
	set();
	set(const set &copy);
	set(searchable_bag &a);
	set &operator=(const set &other);
	~set();

	void insert(int value);
	void insert(int *arr, int size);
	void print() const;
	void clear();

	bool has(int value) const;
	/*
		这个 const 与返回值前面的 const 不是一回事。
		返回值前面的 const：限制调用者能否通过返回的引用修改对象。
		函数末尾的 const：表示这个成员函数不能通过 this 修改对象的普通成员状态。
	*/
	const searchable_bag &get_bag() const;
	searchable_bag &get_bag();
};
