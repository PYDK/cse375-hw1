# C++ compiler flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Werror -pedantic -g

# Ensure that the out directory is created if it does not exist
IDIR = ./include
IFILES = Bank
SRC = ./src
ODIR := ./out
OUTFOLDER := $(shell mkdir -p $(ODIR))
IOFILES = $(patsubst %, $(ODIR)/%.o, $(IFILES))
MAIN_O = $(ODIR)/main.o

all: $(ODIR)/main.exe

# Clean all files in the out directory
clean:
	rm -rf $(ODIR)

# Build all C++ object files in the include directory
$(ODIR)/%.o: $(IDIR)/%.cpp
	@echo "Compiling $<"
	$(CXX) -c -o $@ $< $(CXXFLAGS)
$(ODIR)/%.o: $(SRC)/%.cpp
	@echo "Compiling $<"
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Compile the main executable
$(ODIR)/main.exe: $(IOFILES) $(MAIN_O) 
	@echo "Linking $@"
	$(CXX) -o $@ $^ $(CXXFLAGS)