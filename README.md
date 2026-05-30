# 42 – Exam Rank 05 Practice 🧪

> Practice solutions for **42 Exam Rank 05** in C/C++ (`vect2`, `bigint`, `polyset`, `Life`, `BSQ`).
> Personal study repo, **not for cheating during the exam**.

---

## ⚠️ Disclaimer

This repository is **only for personal study and revision**:

* It is **not** an official 42 resource.
* It is **not** meant to be used during the actual exam.
* Please respect your campus rules and the spirit of the project.

Use it to **understand concepts**, re-implement exercises on your own, and build your muscle memory in C/C++.

---

## 📂 Repository Structure

The repository is organized by exam level and assignment:

```text
exam-rank-05/
├── level-0
│   ├── vect2/
│   ├── bigint/
│   └── polyset/
└── level-1
    ├── Life/
    └── BSQ/
```

Each directory contains my practice implementation and simple test code.

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

A C++ exercise around sets / polynomials depending on the given subject version:

* Practices containers, parsing, and class logic.
* Focuses on clean data representation.
* Requires careful handling of duplicates, ordering, and edge cases.
* Good exercise after `vect2` and `bigint`, because it is more specific.

> ⚠️ NOTE:
>
> The exact subject can vary depending on the exam version or repository source.
> Always read the provided `subject.txt` before implementing.

---

### level-1 / `Life`

A small implementation of Conway’s Game of Life:

* Reads an initial map / pattern.
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

* Convert the map into a numeric DP grid.
* For each empty cell, compute the biggest square ending at that position.
* Track the maximum size and its coordinates.
* Replace the final square in the output map.

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

# Build and run all projects
make run_all

# Clean object files and binaries
make clean   # remove all .o files
make fclean  # remove .o files and all binaries
make re      # full rebuild (fclean + all)
```

> All commands above must be run **from the root directory** of the repository.

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
|     4 | `Life`    | Very likely and important C exercise with grid simulation        |
|     5 | `BSQ`     | More algorithmic, better after the base is solid                 |

