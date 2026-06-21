# vect2 — Mini Cheat Sheet

Main skeleton of the class: has 7 blocks
```cpp
class vect2{
	private:

	public:
		//ctors
		//+= -= *=
		//+ - *
		//++ --
		//unary -
		//[]
		//== !=
};
```

```text
vect2 = small C++ class for a 2D integer vector

stores:
    x
    y
```

## Main idea

```text
Implement a class that behaves like a mathematical 2D vector.
```

## Constructors

```cpp
vect2();              // {0, 0}
vect2(int x, int y);  // {x, y}
vect2(vect2 const &src);
```

## Orthodox Canonical Form

```cpp
Default constructor
Copy constructor
Copy assignment operator
Destructor
```

## Operators to implement

```text
+   vector + vector
-   vector - vector
*   vector * scalar
*   scalar * vector

+=
-=
*=

++
--
unary -

==
!=
[]
<<
```

## Important operator []

```cpp
int &operator[](int index);
const int &operator[](int index) const;
```

```text
index 0 -> x
index 1 -> y

No bounds checking required.
```

## Increment / decrement

```text
++v  -> increment x and y, then return updated object
v++  -> return old object, then increment x and y

--v  -> decrement x and y, then return updated object
v--  -> return old object, then decrement x and y
```

## Unary minus

```cpp
-v
```

```text
{x, y} becomes {-x, -y}
```

## Scalar multiplication

```cpp
v * 2
2 * v
```

Both must work.

## Output format

```cpp
std::cout << v;
```

Must print:

```text
{x, y}
```

## Heart of the task

```text
vect2 is mostly operator overloading practice.
```

## Remember

```text
Non-const [] returns a reference, so v[1] = 12 works.
Const [] returns a const reference, so const vect2 can be read but not modified.
```

## Files to implement

```text
vect2.hpp
vect2.cpp
```
