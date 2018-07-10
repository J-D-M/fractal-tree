# Compiler options
CC       = clang++
CFLAGS   = -Wall -Wextra -pedantic-errors -std=c++17
LFLAGS   = -LSDL2 #-pthread

# Directories
SRCDIR   = ./src
BINDIR   = ./bin
OBJDIR   = ./obj

# Make objects
SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJS     = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCFILES))

ONAME    = fractalTree

# Build target
default: $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $(BINDIR)/$(ONAME)

# Compile intermediate objects
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

# Delete object files
clean:
	rm $(OBJDIR)/*.o
