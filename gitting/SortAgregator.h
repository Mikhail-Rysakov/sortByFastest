#pragma once
#include <iostream>
#include "Sorts.h"
#include <vector>

extern const int initialN; //minimum sorting number (2)
class SortAgregator {
private:
    Insert insert;
    Merge merge;
    Heap heap;
    //Quick quick;
    std::vector<SortInterface*> sorts = { &insert, &merge, &heap/*, &quick*/};
    std::vector<int> intersects;
    //order sortings by "n" intervals (every sorting is the fastest on their own interval)
    void sortSorts();
public:
    //bisection method to find intersection of 2 functions
    int intersect(SortInterface* sort1, SortInterface* sort2) const;

    SortAgregator();
    
    void sortByFastest(std::vector<int>& numbers);
    //Testing method to check out correctness of final work
    void show() const;
};

//function signature for uså
void sortByFastest(std::vector<int>& numbers);