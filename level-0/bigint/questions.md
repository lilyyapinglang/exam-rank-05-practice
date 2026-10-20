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

4. 
bigint& means “reference to an existing bigint”.
result is a std::deque<char>.
result is local and cannot safely be returned by reference.
operator+ should return bigint by value.
operator+= is the operator that should modify the existing object and return bigint&.

5. AN ARRYA OR A STRING ？ WHAT DOES IT MEAN ？
在计算机科学和题目语境中，它主要意味着以下三点：

1. 彻底打破硬件类型的限制

现代 CPU 的寄存器是有固定大小的（通常是 32 位或 64 位）。C++ 里最大的原生无符号整数类型 unsigned long long 最大也只能存到 \(2^{64}-1\)（约 20 位十进制数）。
题目提到 SIZE_MAX，意思是当数字大到连硬件都装不下时，你不能再用任何单一的原生数字类型（如 int, long, __int128）来存它了。你必须把这个大数字切碎，分成很多个“部分”（parts），然后用一个容器把这些碎片串起来。

2. 给你极大的架构设计自由度（暗示了两种主流实现路线）

题目特意点出了 array（数组） 和 string（字符串），其实是在暗示你可以选择以下两种设计路线之一：
• 路线 A：选择 String（更直观，适合初学者/快速实现）
	• 含义： 每个 char 就是数字的一个“part”（即十进制的某一位，比如 '1', '2', '3'）。
	• 优点： 打印输出（std::cout）和从用户输入读取时极其方便，不需要做复杂的进制转换。
	• 缺点： 像你之前感受到的那样，在做加减乘除算法时，你需要频繁地处理 ASCII 码转换（- '0'）和逐位对齐，性能较差，内存占用大（1个字节只存了0-9）。
• 路线 B：选择 Array / std::vector（更专业，适合工业级/高性能）
	• 含义： 这里的“array”指的是一块连续的数字内存（在 C++ 里通常用 std::vector<int> 或 std::vector<uint32_t>）。每个元素不是存一个字符，而是存一个切片数字。
	• 例如： 如果大数是 1234567890123456，你可以把它切成两部分（两段 8 位数），数组里存 [890123456, 1234567]。此时，数组的每个元素就是大数的一个 "part"。
	• 优点： 压榨 CPU 性能，运算速度极快。
	• 缺点： 编写“字符串转大数”和“大数转字符串打印”的逻辑时，需要写一些取模和除法的转换逻辑。

3. “Unsigned” 降低了题目难度

题目特别强调了 unsigned integer（无符号整数）。
这意味着什么？这意味着你完全不需要考虑负号 '-' 的情况！你的类只需要处理 0 和正整数。在写加法和后面的减法算法时，你不用去判断“正数加负数变成减法”等复杂的正负号组合逻辑，这大大简化了你的代码边界条件。


6 。

第二：为什么构造函数要写 const std::string& str 而不是 std::string str？

你写的 bigint(std::string str) 可以正常工作，程序能跑通。但之所以在 C++ 中大家普遍推崇写成 const std::string& str，主要是为了极致的性能优化（避免不必要的内存拷贝）。
我们来看看这两种写法的底层执行逻辑：

1. 你当前的写法：bigint(std::string str) （传值）

当你调用 bigint x("12345678901234567890"); 时：
1. 编译器把字符串字面量转成一个临时的 std::string。
2. 第一次拷贝（传参）：因为是值传递，编译器会把这个临时字符串完整地复制一份给构造函数的形参 str。这里会发生一次内存动态分配（malloc）和字符复制。
3. 第二次拷贝（内部存储）：在构造函数内部，你必然要把 str 的内容存到你的类成员变量里（比如 this->my_data = str;），这又引发了第二次内存复制。

2. 推荐的写法：bigint(const std::string& str) （常引用传递）

• &（引用）：代表“别名”或“指针”。它不会在传参时复制整个字符串，而是直接把原字符串的内存地址传过去。
• const：确保你在构造函数内部只能读取它，不能修改它。
当你用这种方式调用 bigint x("12345678901234567890"); 时：
1. 编译器把字符串字面量转成临时 std::string。
2. 没有拷贝：构造函数的形参 str 只是这个临时对象的“影子”（引用），传递代价几乎为 0。
3. 只有一次拷贝：进入构造函数后，你将其赋值给类成员变量，此时才发生唯一一次内存复制。

📊 性能对比总结

• std::string str ➔ 2 次内存分配和字符复制。
• const std::string& str ➔ 1 次内存分配和字符复制。
对于大数类来说，输入的字符串可能会非常长，多一次复制就会多消耗一倍的内存和 CPU 时间。因此，在 C++ 中，除了基础类型（如 int, size_t），所有对象类型的参数都强烈建议加上 const &。

7.。。。。


第一：size_t 和 unsigned long 在不考虑负数时有什么区别？

在没有负数的情况下，它们在绝大多数现代系统（如 Linux 64 位）上是完全等价的，但在跨平台和语义定义上有一些微小的区别：
1. 底层大小的区别（仅在 Windows 64 位上有差异）：
	• 在 Linux 64 位（Ubuntu、macOS 等）上：size_t 和 unsigned long 都是 64 位（8字节），最大值都是 \(2^{64}-1\)。因此在这里它们毫无区别。
	• 在 Windows 64 位上：unsigned long 被限定为 32 位（4字节），而 size_t 依然是 64 位（8字节）。如果你在 Windows 上用 unsigned long，超过 42 亿的数字就会溢出。
2. 语义上的区别：
	• size_t 的本意是“用来表示内存中对象大小或数组下标的类型”。
	• unsigned long 就是一个单纯的“大整数”。
	• 结论：既然你的大数类不需要负数，为了防止 Windows 平台下的 32 位截断问题，使用 size_t 是比 unsigned long 更安全、更好的选择。你的设计很对。


8 。。。。。


1. 为什么不建议用 bigint(size_t number)？

当然可以用 size_t，但用 long 或 int 会更好，原因有两个：
• size_t 无法表示负数：size_t 是一个无符号整型（unsigned）。如果题目中出现 bigint b(-21);，负数 -21 会被隐式转换成一个非常巨大的正整数（在 64 位系统上变成 18446744073709551595），导致大数类内部的值完全错误。
• 为了兼顾正负数：大数类通常需要处理负数，因此构造函数应该接受一个带符号的类型。在 C++98 中，long 是原生支持的最大带符号整数，它既能装下 int，又能正确保留负号。

2. const std::string& 和 const char* 有什么区别？

这两者代表了 C++ 中字符串的两代标准：

特性	const std::string& str	const char* str
本质	C++ 标准库的对象（封装了内存管理）	C 语言风格的指针（指向一个以 \0 结尾的字符数组）
来源	比如 std::string s = "123"; bigint x(s);	比如直接写的字面量 bigint x("1289496...");


为什么建议两个都写？（历史遗留与编译优化问题）

在 C++98 中，如果你只写 bigint(const std::string& str)：
当你调用 bigint x("12345"); 时，编译器其实很聪明，它会发现 "12345"（这是 const char*）可以隐式转换成 std::string，所以编译也能通过。
但是，这会带来两个隐患：
1. 额外的性能开销：编译器必须在幕后悄悄创建一个临时的 std::string 对象，把内容动态复制进去，传给构造函数，用完后再销毁它。
2. 多重隐式转换冲突：如果你的类设计变得复杂（比如增加了其他重载或运算符），C++98 的编译器在面对 bigint x("12345") 时，可能会在“将其转为 string”还是“将其转为其他类型”之间产生歧义，直接抛出 ambiguous（不明确的匹配）编译错误。
一句话总结：
显式提供 const char* 版本，是为了让 bigint x("超级大数"); 这种直接带双引号的赋值速度最快、匹配最精准、绝不让编译器产生误解。