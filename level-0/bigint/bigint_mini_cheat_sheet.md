# bigint — Mini Cheat Sheet

Main skeleton of the class: has 7 blocks
```cpp
class bigint{
	private:

	public:
		//ctors
		//+= + ++
		//<<= <<
		//>>= >>
		//<= <
		//>= >
		//== !=
};
```

Main skeleton of the addition: has 7 blocks
```cpp
//1. 7 variables
//2. 2 starts + 2 positions
//3. while loop - 3 conditions
//4. resets
//5. take 2 digits
//6. take 2 results
//7. save, normalize, return
```

```text
bigint = arbitrary precision unsigned integer

stores digits as a string
example:
    "0"
    "42"
    "1337"
```

## Main idea

```text
Use a string to store a number bigger than normal integer limits.
```

## Constructors

```cpp
bigint();                    // 0
bigint(unsigned int value);   // from number
bigint(bigint const &src);
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
+
+=

++
post++

<<
<<=
>>
>>=

<
<=
>
>=
==
!=

<< output stream
```

## Addition

```text
Add from right to left, digit by digit.
Keep carry.
Build result string.
Remove leading zeros.
```

## Increment

```cpp
++n
n++
```

```text
++n  -> add 1, return updated object
n++  -> save old copy, add 1, return old copy
```

## Digit shift left

```cpp
42 << 3
```

Result:

```text
42000
```

Meaning:

```text
append zeros to the end
```

Special case:

```text
0 << n is still 0
```

## Digit shift right

```cpp
1337 >> 2
```

Result:

```text
13
```

Meaning:

```text
remove digits from the end
```

Special case:

```text
if shift >= number of digits -> 0
```

## Comparisons

```text
First compare string length.
If lengths are equal, compare strings lexicographically.
```

Example:

```text
"100" > "99" because length 3 > length 2
"42" < "50" because same length and "42" < "50"
```

## Output format

```cpp
std::cout << n;
```

Must print:

```text
decimal number without leading zeros
```

## Heart of the task

```text
bigint is string-based arithmetic + operator overloading.
```

## Remember

```text
Always normalize digits.
No leading zeros except the number "0".
Only unsigned integers.
Digit shift is base 10, not binary bitshift.
```

## Files to implement

```text
bigint.hpp
bigint.cpp
```
