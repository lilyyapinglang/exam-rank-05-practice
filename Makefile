# ============================================================
#              42 Exam Rank 05 – Makefile 🧪
# ============================================================

# 🧱 Compilers & Flags
CC       := cc
CXX      := c++
CFLAGS   := -Wall -Wextra -Werror -g3
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -g3
# Debug only, without warnings:
# CFLAGS   := -g3
# CXXFLAGS := -g3 -std=c++98

# 📁 Project Directories
VECT2_DIR   := level-0/vect2
BIGINT_DIR  := level-0/bigint
POLYSET_DIR := level-0/polyset
LIFE_DIR    := level-1/Life
BSQ_DIR     := level-1/BSQ

# 🎯 Binary Names (per directory)
VECT2_NAME   := vect2
BIGINT_NAME  := bigint
POLYSET_NAME := polyset
LIFE_NAME    := life
BSQ_NAME     := bsq

# 📦 Binaries (full paths)
VECT2_BIN   := $(VECT2_DIR)/$(VECT2_NAME)
BIGINT_BIN  := $(BIGINT_DIR)/$(BIGINT_NAME)
POLYSET_BIN := $(POLYSET_DIR)/$(POLYSET_NAME)
LIFE_BIN    := $(LIFE_DIR)/$(LIFE_NAME)
BSQ_BIN     := $(BSQ_DIR)/$(BSQ_NAME)

# 🧩 Source / Object lists (explicit files)
VECT2_SRCS   := $(VECT2_DIR)/main.cpp \
				$(VECT2_DIR)/vect2.cpp
BIGINT_SRCS  := $(BIGINT_DIR)/main.cpp \
				$(BIGINT_DIR)/bigint.cpp
POLYSET_SRCS := $(POLYSET_DIR)/given-code/main.cpp \
				$(POLYSET_DIR)/given-code/array_bag.cpp \
				$(POLYSET_DIR)/given-code/tree_bag.cpp \
				$(POLYSET_DIR)/searchable_array_bag.cpp \
				$(POLYSET_DIR)/searchable_tree_bag.cpp \
				$(POLYSET_DIR)/set.cpp
LIFE_SRCS    := $(LIFE_DIR)/main.c
BSQ_SRCS     := $(BSQ_DIR)/main.c \
				$(BSQ_DIR)/bsq.c

# 🧱 Object files
VECT2_OBJS   := $(VECT2_SRCS:.cpp=.o)
BIGINT_OBJS  := $(BIGINT_SRCS:.cpp=.o)
POLYSET_OBJS := $(POLYSET_SRCS:.cpp=.o)
LIFE_OBJS    := $(LIFE_SRCS:.c=.o)
BSQ_OBJS     := $(BSQ_SRCS:.c=.o)

$(POLYSET_OBJS): CXXFLAGS += -I$(POLYSET_DIR) -I$(POLYSET_DIR)/given-code

# 📦 All binaries together
BINS := \
	$(VECT2_BIN) \
	$(BIGINT_BIN) \
	$(POLYSET_BIN) \
	$(LIFE_BIN) \
	$(BSQ_BIN)

OBJS := \
	$(VECT2_OBJS) \
	$(BIGINT_OBJS) \
	$(POLYSET_OBJS) \
	$(LIFE_OBJS) \
	$(BSQ_OBJS)

# ============================================================
#  Generic Rules
# ============================================================

# Default target
.PHONY: all

all: $(BINS)
	@echo "✅ All Exam Rank 05 binaries built."

# Generic rule: compile any .c -> .o
%.o: %.c
	@echo "🔧 Compiling C $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Generic rule: compile any .cpp -> .o
%.o: %.cpp
	@echo "🔧 Compiling C++ $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
#  Link Rules
# ============================================================

$(VECT2_BIN): $(VECT2_OBJS)
	@echo "🔗 Linking $@"
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(BIGINT_BIN): $(BIGINT_OBJS)
	@echo "🔗 Linking $@"
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(POLYSET_BIN): $(POLYSET_OBJS)
	@echo "🔗 Linking $@"
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(LIFE_BIN): $(LIFE_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(BSQ_BIN): $(BSQ_OBJS)
	@echo "🔗 Linking $@"
	@$(CC) $(CFLAGS) $^ -o $@

# ============================================================
#  Per-project build targets
# ============================================================

.PHONY: vect2 bigint polyset life bsq

vect2: $(VECT2_BIN)
	@echo "✅ Built $(VECT2_BIN)"

bigint: $(BIGINT_BIN)
	@echo "✅ Built $(BIGINT_BIN)"

polyset: $(POLYSET_BIN)
	@echo "✅ Built $(POLYSET_BIN)"

life: $(LIFE_BIN)
	@echo "✅ Built $(LIFE_BIN)"

bsq: $(BSQ_BIN)
	@echo "✅ Built $(BSQ_BIN)"

# ============================================================
#  Per-project clean / rebuild
# ============================================================

.PHONY: clean_vect2 clean_bigint clean_polyset clean_life clean_bsq
.PHONY: re_vect2 re_bigint re_polyset re_life re_bsq

clean_vect2:
	@echo "🧹 Cleaning vect2"
	@rm -f $(VECT2_OBJS) $(VECT2_BIN)

re_vect2: clean_vect2
	@$(MAKE) --no-print-directory vect2
	@echo "🔁 Rebuilt vect2."

clean_bigint:
	@echo "🧹 Cleaning bigint"
	@rm -f $(BIGINT_OBJS) $(BIGINT_BIN)

re_bigint: clean_bigint
	@$(MAKE) --no-print-directory bigint
	@echo "🔁 Rebuilt bigint."

clean_polyset:
	@echo "🧹 Cleaning polyset"
	@rm -f $(POLYSET_OBJS) $(POLYSET_BIN)

re_polyset: clean_polyset
	@$(MAKE) --no-print-directory polyset
	@echo "🔁 Rebuilt polyset."

clean_life:
	@echo "🧹 Cleaning Life"
	@rm -f $(LIFE_OBJS) $(LIFE_BIN)

re_life: clean_life
	@$(MAKE) --no-print-directory life
	@echo "🔁 Rebuilt Life."

clean_bsq:
	@echo "🧹 Cleaning BSQ"
	@rm -f $(BSQ_OBJS) $(BSQ_BIN)

re_bsq: clean_bsq
	@$(MAKE) --no-print-directory bsq
	@echo "🔁 Rebuilt BSQ."

# ============================================================
#  Run helpers
# ============================================================

.PHONY: run_vect2 run_bigint run_polyset run_life run_bsq run_all

run_vect2: re_vect2
	@echo "🚀 Running vect2\n"
	@$(VECT2_BIN)

run_bigint: re_bigint
	@echo "🚀 Running bigint\n"
	@$(BIGINT_BIN)

run_polyset: re_polyset
	@echo "🚀 Running polyset\n"
	@$(POLYSET_BIN) 1 2 3 4 5 5 3

run_life: re_life
	@echo "🚀 Running Life\n"

	@echo "🧪 Test 1: 5x5, 0 iterations"
	@echo 'sdxddssaaww' | $(LIFE_BIN) 5 5 0 | cat -e
	@echo

	@echo "🧪 Test 2: 10x6, 0 iterations"
	@echo 'sdxssdswdxddddsxaadwxwdxwaa' | $(LIFE_BIN) 10 6 0 | cat -e
	@echo

	@echo "🧪 Test 3: blinker 3x3, 0 iterations"
	@echo 'dxss' | $(LIFE_BIN) 3 3 0 | cat -e
	@echo

	@echo "🧪 Test 4: blinker 3x3, 1 iteration"
	@echo 'dxss' | $(LIFE_BIN) 3 3 1 | cat -e
	@echo

	@echo "🧪 Test 5: blinker 3x3, 2 iterations"
	@echo 'dxss' | $(LIFE_BIN) 3 3 2 | cat -e

run_bsq: re_bsq
	@echo "🚀 Running BSQ\n"

	@echo "🧪 Test 1: subject example"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/example_file | cat -e
	@echo

	@echo "🧪 Test 2: 1x1 empty"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/map1_empty | cat -e
	@echo

	@echo "🧪 Test 3: 1x1 obstacle"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/map2_obstacle | cat -e
	@echo

	@echo "🧪 Test 4: 3x5 no obstacle"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/map3_no_obstacle | cat -e
	@echo

	@echo "🧪 Test 5: priority top-left"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/map4_priority | cat -e
	@echo

	@echo "🧪 Test 6: bad map, different line width"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/bad1_width 2>&1 | cat -e
	@echo

	@echo "🧪 Test 7: bad map, same chars"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/bad2_same_chars 2>&1 | cat -e
	@echo

	@echo "🧪 Test 8: bad map, extra line"
	@$(BSQ_BIN) $(BSQ_DIR)/tests/bad3_extra_line 2>&1 | cat -e
	@echo

run_all: all
	@echo "🚀 Running all binaries"
	@$(VECT2_BIN) || true
	@$(BIGINT_BIN) || true
	@$(POLYSET_BIN) || true
	@$(LIFE_BIN) || true
	@$(BSQ_BIN) || true

# ============================================================
#  Global Cleanup
# ============================================================

.PHONY: clean fclean re

clean:
	@echo "🧹 Cleaning all object files"
	@rm -f $(OBJS)

fclean: clean
	@echo "🗑  Removing all binaries"
	@rm -f $(BINS)

re: fclean all
	@echo "🔁 Rebuilt everything from scratch."