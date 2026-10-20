1. what is a SIZE_MAX ?

SIZE_MAX is maximum value of size_t 
Defined in header <limits.h>

2. what is a size_t ? 

printf("SIZE_MAX = %zu\n", SIZE_MAX);
SIZE_MAX = 18446744073709551615


3. how to define data memebers of the class?

the input examples are :
a(42);  b(21), c, d(1337), e(d);

so it meants it can take 
1. nothing 
2. a number 

and it have a copy ocnstructor ..
but how? 
so it should take a string ?

ok let's see some explanations:
在计算机科学中，Bignum（大数）是一个用来表示任意精度数字的对象。
当你需要存储一个比系统默认的最大限制（例如 SIZE_MAX）还要大的数字，且不希望损失任何精度时，大数就非常有用。

它是如何实现的？

在底层实现上，它通常通过存储一个数组（Array）或一个字符串（String）来记录该数字的各个“部分”。

举个通俗的例子：

假设你的计算器非常旧，每个格子只能装一个 0 到 9 的数字。
• 如果你想存数字 8，用一个格子就够了。
• 如果你想存数字 125，原生的单个格子就装不下了。
Bignum 的做法是： 既然一个格子装不下，那我就用一个一排格子（数组/字符串）。第一个格子放 1，第二个放 2，第三个放 5。通过这种把数字拆开、拼起来的方式，理论上只要你的计算机内存足够大，你就可以存储无限大的数字，并且在计算时（比如做加减乘除）不会像浮点数那样丢失任何精度。
许多现代编程语言（如 Python 中的 int，Java 中的 BigInteger）都在底层自动实现了这种机制。