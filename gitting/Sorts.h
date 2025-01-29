#pragma once

#include "MetaTimer.h"
#include "LinearEquationsSystem.h"
#include <iostream>
extern const int ORDER;  //порядок СЛАУ по числу счетчиков

class SortInterface {
private:
    void init();
protected:
    void polymorphStarterForSon();
    MetaTimer timer;
public:
    std::vector<double> getTimerString() { return timer.getMetaString(); }
    LinearEquationsSystem constants;
    virtual void sort(std::vector<int>& numbers) = 0;
    virtual void sortWithTiming(std::vector<int>& numbers);
    virtual double getTime(double n) const = 0;   //double для корректной работы с большим n в полиморфах
    void work(std::vector<int>& numbers);
};


class Insert : public SortInterface {
private:
    //cycle zone
    void insert(std::vector<int>& numbers);
public:
    Insert();
    //sort without timing
    void sort(std::vector<int>& numbers) override;
    double getTime(double n) const override;
};

class Merge : public SortInterface {
private:
    //cycle zone
    void merge(std::vector<int>& numbers, int left, int mid, int right);
    void mergeSortRecursive(std::vector<int>& numbers, int left, int right);
public:
    Merge();

    void sort(std::vector<int>& numbers) override;
    double getTime(double n) const override;
};

class Heap : public SortInterface {
private:
    //cycle zone
    void maxHeapify(std::vector<int>& numbers, int index, int& heapSize);
    void buildMaxHeap(std::vector<int>& numbers, int& heapSize);
    void heap(std::vector<int>& numbers);
public:
    Heap();

    void sort(std::vector<int>& numbers) override;
    double getTime(double n) const override;
};

class Quick : public SortInterface {
private:
    //cycle zone
    int partition(std::vector<int>& numbers, int left, int right);
    void quickSortRecursive(std::vector<int>& numbers, int left, int right);
public:
    Quick();

    void sort(std::vector<int>& numbers) override;
    double getTime(double n) const override;
};