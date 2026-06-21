# 42 – Exam Rank 05 Practice 🧪

> Practice solutions for **42 Exam Rank 05** in C/C++ (`vect2`, `bigint`, `polyset`, `Life`, `BSQ`).
> Personal study repo, **not for cheating during the exam**.

---

## ⚠️ Disclaimer

This repository is **only for personal study and revision**:

* It is **not** an official 42 resource.
* It is **not** meant to be used during the actual exam.
* Exercise subjects and supplied starter code were not written by me.
* The subjects may change, so always follow the version provided during your exam.
* Please respect your campus rules and the spirit of the project.

Use it to **understand concepts**, re-implement exercises on your own, and build your muscle memory in C/C++.

---

## 📂 Repository Structure

The repository is organized by exam level and assignment:

```text
42-exam-rank-05/
├── level-0
│   ├── vect2/
│   ├── bigint/
│   └── polyset/
└── level-1
    ├── Life/
    └── BSQ/
```

Each exercise directory contains the subject, my practice implementation,
test files where applicable, and a compact revision cheat sheet.

---

## 🧩 Exercises Overview

### level-0 / `vect2`

A small C++ exercise focused on a 2D vector class:

* Implements a simple `vect2` class.
* Practices constructors, operators, and basic class design.
* Usually includes arithmetic operators such as `+`, `-`, `*`, comparisons, and stream output.
* Good warm-up for C++ syntax and operator overloading.

---

### level-0 / `bigint`

A minimal big integer implementation:

* Represents very large positive integers that do not fit in built-in types.
* Stores the number internally as a string or digit container.
* Implements arithmetic and comparison operators.
* Good exercise for operator overloading, string manipulation, and edge cases.

Typical things to practice:

* Addition with carry.
* Increment operators.
* Comparison operators.
* Clean output formatting.

---

### level-0 / `polyset`

A C++ exercise focused on abstract classes, multiple inheritance and container wrappers:

* Extends `array_bag` and `tree_bag` with a searchable interface.
* Implements `has()` for an array and a binary search tree.
* Wraps a `searchable_bag` inside a `set`.
* Prevents duplicate values from being inserted.
* Practices Orthodox Canonical Form and const correctness.

The exercise includes supplied base classes inside the `given-code` directory.

> ⚠️ NOTE:
>
> Always read the provided `subject.txt` and inspect the supplied classes
> before implementing the missing files.

---

### level-1 / `Life`

A small implementation of Conway’s Game of Life:

* Draws the initial board using movement and pen commands from standard input.
* Applies the Game of Life rules for a given number of iterations.
* Handles a 2D grid and neighbor counting.
* Good exercise for arrays, loops, boundary checks, and simulation logic.

Core rules:

* A live cell survives with 2 or 3 live neighbors.
* A live cell dies with fewer than 2 or more than 3 live neighbors.
* A dead cell becomes alive with exactly 3 live neighbors.

---

### level-1 / `BSQ`

The classic “Biggest Square” algorithm:

* Reads a map containing empty cells and obstacles.
* Finds the largest square that can be placed without touching obstacles.
* Usually solved efficiently with dynamic programming.
* Good exercise for parsing, memory management, and algorithmic thinking.

Typical approach:

* Parse and validate the complete map.
* Use dynamic programming to compute the biggest square ending at each cell.
* Keep only one DP row to reduce additional memory usage.
* Track the maximum size and its coordinates.
* Replace the selected empty cells with the full character.

### Header parsing edge case

The map characters can be printable characters, including whitespace.
For example, the empty character itself may be a space.

Because of this, avoid parsing the header like this:

```c
fscanf(file, "%d %c %c %c\n",
    &map->rows, &map->empty, &map->obs, &map->full);
```

Whitespace characters inside an `fscanf` format string do not match exactly one
space or one newline. They consume any amount of consecutive whitespace.

This can cause two important problems:

* An empty character represented by a space may be skipped instead of stored.
* The final `\n` may consume spaces from the beginning of the first map row.

A safer approach is to read every separator and the final newline explicitly:

```c
char sep1;
char sep2;
char sep3;
char end;

if (fscanf(file, "%d%c%c%c%c%c%c%c", 
			&map->rows, &sep1, &map->empty, &sep2,
			&map->obs, &sep3, &map->full, &end) != 8)
    return (0);
if (sep1 != ' ' || sep2 != ' ' || sep3 != ' ')
    return (0);
if (end != '\n')
    return (0);
```

This validates the exact header format, supports whitespace map characters,
and ensures that the next `getline` starts at the first real map row.

> ⚠️ NOTE:
>
> `BSQ` is usually more algorithmically demanding than the other exercises.
> It is better to practice it after becoming comfortable with the C++ exercises
> and after implementing `Life`.

---

## 🛠️ Build & Run

All projects are built and run via the **root Makefile**.

From the repository root:

```bash
# Build all binaries (vect2, bigint, polyset, Life, BSQ)
make

# Build a single project
make vect2
make bigint
make polyset
make life
make bsq

# Build and run a single project
make run_vect2
make run_bigint
make run_polyset
make run_life
make run_bsq

# Clean object files and binaries
make clean   # remove all .o files
make fclean  # remove .o files and all binaries
make re      # full rebuild (fclean + all)
```

> All commands above must be run **from the root directory** of the repository.

---

## 🧪 Level 1 Test Suites

I wrote dedicated Bash test suites for both Level 1 exercises:

* `Life`
* `BSQ`

The testers contain a comprehensive collection of normal cases, edge cases,
invalid inputs and output comparisons.

Each test is executed with a timeout to detect infinite loops or programs
waiting unexpectedly for additional input.

### Life tester

The `Life` tester checks:

* Different board sizes and iteration counts.
* Empty and populated boards.
* Stable patterns and oscillators.
* Drawing commands and pen behavior.
* Output formatting.
* Unexpected output on `stderr`.
* Execution timeouts.
* Border-movement policy cases.

The tester compares the program output with the expected output stored in:

```text
level-1/Life/tests/expected/
```

Arguments and input commands are stored separately in:

```text
level-1/Life/tests/args/
level-1/Life/tests/input/
```

Border-policy cases are stored in:

```text
level-1/Life/tests/policy/
```

#### Run the Life tests

From the `level-1/Life` directory:

```bash
make -C ../.. life
./tests/run-tests.sh
```

Or, if the program is already compiled:

```bash
cd level-1/Life
./tests/run-tests.sh
```

The script uses `./life` as the default executable.
A different executable can also be passed explicitly:

```bash
./tests/run-tests.sh ./life
```

### BSQ tester

The `BSQ` tester checks:

* Valid maps of different dimensions.
* Empty and obstacle-filled maps.
* Selection priority for equal-size squares.
* Whitespace characters used as map symbols.
* Invalid headers.
* Invalid characters.
* Different row widths.
* Missing or additional rows.
* Output written to both `stdout` and `stderr`.
* Execution timeouts.

Input maps are stored in:

```text
level-1/BSQ/tests/input/
```

Expected standard output and error output are stored separately in:

```text
level-1/BSQ/tests/expected-out/
level-1/BSQ/tests/expected-err/
```

#### Run the BSQ tests

From the `level-1/BSQ` directory:

```bash
make -C ../.. bsq
./tests/run-tests.sh
```

Or, if the program is already compiled:

```bash
cd level-1/BSQ
./tests/run-tests.sh
```

The script uses `./bsq` as the default executable.
A different executable can also be passed explicitly:

```bash
./tests/run-tests.sh ./bsq
```

A successful test run displays the number of passed and failed tests and exits
with a non-zero status if at least one strict test fails.

> These testers are additional practice tools written for this repository.
> They are not official 42 testers and cannot guarantee that every possible
> exam edge case is covered.

---

## 📖 How I Use This Repo

* Re-implement exercises **from scratch** without copy-paste.
* Add small **test mains** for each exercise.
* Practice both **C** and **C++98** versions depending on the subject.
* Try to solve with **limited functions**, just like in the exam.
* Refactor until the code is **clean, readable and robust**.
* Repeat the exercises until I can write the main logic without looking.

If you are a 42 student:
Treat this repo as a **reference and practice ground**, not as something to memorize. The real skill for the exam is being able to write these solutions again under pressure.

---

## 🧠 Suggested Study Order

My suggested order for preparing this exam:

| Order | Exercise  | Why                                                              |
| ----: | --------- | ---------------------------------------------------------------- |
|     1 | `vect2`   | Best C++ warm-up: classes, operators, clean syntax               |
|     2 | `bigint`  | Strong practice for operator overloading and number/string logic |
|     3 | `polyset` | More specific C++ exercise, better after the basics              |
|     4 | `Life`    | Important C exercise for grid handling and simulation            |
|     5 | `BSQ`     | More algorithmic, better after the base is solid                 |

