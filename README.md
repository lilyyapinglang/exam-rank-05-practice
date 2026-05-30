# 42 – Exam Rank 05 Practice

> Practice repository for the new 42 Exam Rank 05 (`vect2`, `bigint`, `polyset`, `Life`, `BSQ`).
> Personal study repo, not for cheating during the exam.

---

## ⚠️ Disclaimer

This repository is only for personal study and revision:

- It is not an official 42 resource.
- It is not meant to be used during the actual exam.
- Please respect your campus rules and the spirit of the project.
- The goal is to understand the exercises and be able to re-implement them from scratch.

Use this repository to build muscle memory, test edge cases, and prepare under exam-like conditions.

---

## Repository Structure

```text
42-exam-rank-05/
├── level-0
│   ├── vect2/
│   ├── bigint/
│   └── polyset/
├── level-1
│   ├── Life/
│   └── BSQ/
├── docs/
├── .gitignore
├── Makefile
└── README.md
```

---

## Exercises Overview

### level-0 / `vect2`

A small C++ vector class exercise:

- Practice classes, constructors, operators and simple geometry.
- Useful for reviewing operator overloads.
- Good first exercise because it is compact and very C++ oriented.

---

### level-0 / `bigint`

A big integer implementation:

- Practice operator overloads.
- Work with numbers represented as strings or digit containers.
- Focus on addition, comparison, increment/decrement and output formatting.

---

### level-0 / `polyset`

A polynomial / set-like C++ exercise:

- Practice containers, parsing, class design and operator logic.
- More specific than `vect2` and `bigint`.
- Better to study after the basics of operator overloads are clear.

---

### level-1 / `Life`

A small implementation inspired by Conway's Game of Life:

- Practice grid handling.
- Parse input.
- Simulate generations.
- Very important exercise because it has been reported as appearing in the new Exam Rank 05.

---

### level-1 / `BSQ`

Biggest Square algorithm:

- Find the biggest square in a map.
- Practice parsing, dynamic programming and edge cases.
- Algorithmically heavier, so it is better to study after the other exercises.

---

## Suggested Study Order

| Order | Exercise | Why |
| ----: | -------- | --- |
| 1 | `vect2` | Best C++ warm-up: classes, operators, small scope |
| 2 | `bigint` | Strong practice for operator overloads and string/number logic |
| 3 | `polyset` | More specific C++ task, easier after `bigint` |
| 4 | `Life` | Very likely and important practical task |
| 5 | `BSQ` | More algorithmic, better after the base is solid |

---

## Build & Run

All exercises can be built from the root Makefile.

```bash
# Build all exercises
make

# Build one exercise
make vect2
make bigint
make polyset
make life
make bsq

# Run one exercise
make run_vect2
make run_bigint
make run_polyset
make run_life
make run_bsq

# Clean
make clean
make fclean
make re
```

> All commands above must be run from the root directory of the repository.

---

## How I Use This Repo

- Re-implement every exercise from scratch.
- Keep simple tests next to each exercise.
- Add edge cases after each failed attempt.
- Avoid copy-paste during practice.
- Time myself to simulate real exam pressure.

---

## Repository Topics

Recommended GitHub topics:

```text
42
42school
exam
exam-rank-05
rank-05
new-exam-rank
cpp
cpp98
c-language
vect2
bigint
polyset
life
bsq
algorithm
practice
```
