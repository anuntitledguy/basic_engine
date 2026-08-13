# ============================================
# Compiler
# ============================================

CXX = g++

# ============================================
# Directories
# ============================================

INCLUDES = -Iinclude
    
# ============================================
# Raylib libraries
# ============================================

LIBS = -lraylib -lGLESv2 -lEGL -lm -lpthread -ldl -lrt -lX11

# ============================================
# Sources
# ============================================

SRC := $(shell find src -type f -name "*.cpp")
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)

TARGET = main

# ============================================
# Build type
# ============================================

DEBUG_FLAGS = \
	-std=c++17 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Wshadow \
	-Wconversion \
	-Wnull-dereference \
	-g3 \
	-O0 \
	-fsanitize=address,undefined \
	-fno-omit-frame-pointer \
	-MMD -MP

RELEASE_FLAGS = \
	-std=c++17 \
	-O2 \
	-DNDEBUG \
	-MMD -MP

CXXFLAGS = $(DEBUG_FLAGS)

# Les sanitizers doivent être présents au link également
LDFLAGS = -fsanitize=address,undefined

# ============================================
# Build rules
# ============================================

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ============================================
# Utilities
# ============================================

debug:
	$(MAKE) CXXFLAGS="$(DEBUG_FLAGS)" LDFLAGS="-fsanitize=address,undefined" clean all

release:
	$(MAKE) CXXFLAGS="$(RELEASE_FLAGS)" LDFLAGS="" clean all

gdb: $(TARGET)
	gdb ./$(TARGET)

valgrind: $(TARGET)
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--verbose \
		./$(TARGET)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(TARGET)

re: fclean all

# Inclure automatiquement les dépendances
-include $(DEP)

.PHONY: all clean fclean re debug release valgrind gdb