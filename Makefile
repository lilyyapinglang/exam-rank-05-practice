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
BSQ_SRCS     := $(BSQ_DIR)/main.c

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

# Link each project

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
#  Run helpers (build + run)
# ============================================================

.PHONY: run_vect2 run_bigint run_polyset run_life run_bsq run_all

run_vect2: vect2
	@echo "🚀 Running vect2\n"
	@$(VECT2_BIN)

run_bigint: bigint
	@echo "🚀 Running bigint\n"
	@$(BIGINT_BIN)

run_polyset: polyset
	@echo "🚀 Running polyset\n"
	@$(POLYSET_BIN) 1 2 3 4 5 5 3

run_life: life
	@echo "🚀 Running Life\n"
	@$(LIFE_BIN)

run_bsq: bsq
	@echo "🚀 Running BSQ\n"
	@$(BSQ_BIN)

run_all: all
	@echo "🚀 Running all binaries (in order)"
	@$(VECT2_BIN)   || true
	@$(BIGINT_BIN)  || true
	@$(POLYSET_BIN) || true
	@$(LIFE_BIN)    || true
	@$(BSQ_BIN)     || true

# ============================================================
#  Cleanup
# ============================================================

.PHONY: clean fclean re

clean:
	@echo "🧹 Cleaning object files"
	@rm -f $(OBJS)

fclean: clean
	@echo "🗑  Removing binaries"
	@rm -f $(BINS)

re: fclean all
	@echo "🔁 Rebuilt everything from scratch."