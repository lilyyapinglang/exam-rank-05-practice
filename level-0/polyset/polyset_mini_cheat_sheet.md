# Polyset — Mini Cheat Sheet

```text
array_bag stores values in an array
tree_bag stores values in a binary search tree

searchable_array_bag = array_bag + searchable_bag + has()
searchable_tree_bag  = tree_bag  + searchable_bag + has()

set = wrapper around searchable_bag
set prevents duplicates
```

## Main idea

```text
bag can contain duplicates
set must contain only unique values
```

## searchable_array_bag

```cpp
class searchable_array_bag : public array_bag, public searchable_bag
```

```text
has(value):
    loop through data
    if data[i] == value -> true
    otherwise -> false
```

## searchable_tree_bag

```cpp
class searchable_tree_bag : public tree_bag, public searchable_bag
```

```text
has(value):
    if node is empty -> false
    if node value == value -> true
    if value < node value -> search left
    else -> search right
```

## set

```cpp
class set
{
    private:
        searchable_bag *bag;
};
```

## Heart of the task

```cpp
if (bag->has(value) == false)
    bag->insert(value);
```

## Remember

```text
searchable_bag is needed because set must call has()
```

## Orthodox Canonical Form

For each new class:

```cpp
Default constructor
Copy constructor
Copy assignment operator
Destructor
```

## Const

```cpp
bool has(int value) const;
```

## Files to implement

```text
searchable_array_bag.hpp / .cpp
searchable_tree_bag.hpp  / .cpp
set.hpp / .cpp
```
