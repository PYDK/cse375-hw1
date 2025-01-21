# C++ compiler flags
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -pedantic -g

# Ensure that the out directory is created if it does not exist
ODIR := ./out
OUTFOLDER := $(shell mkdir -p $(ODIR))

# Clean all files in the out directory
clean:
	rm -rf $(ODIR)

# Compile all C++ object files in the include directory
$(ODIR)/%.o: %.cpp
	@echo "Compiling $^"
	$(CXX) -c -o $@ $^ $(CXXFLAGS)