CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic

TESTS=test_merge_sort test_graph_search test_knapsack

all: $(TESTS)

$(TESTS): %: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

test: $(TESTS)
	@./test_merge_sort
	@./test_graph_search
	@./test_knapsack

clean:
	rm -f $(TESTS)

.PHONY: all test clean
