#include "Sorts.h"

extern const int ORDER = 2;  //порядок СЛАУ по числу счетчиков
//
void SortInterface::sortWithTiming(std::vector<int>& numbers) {
    timer.start();
    sort(numbers);
    timer.stop();
}

void SortInterface::init() {
    int calibraionsNumber = 100;
    for (int i = 0; i < calibraionsNumber; i++) {
        //create vectors of random size with random numbers
        std::vector<int> testVector;
        int size = rand() % 1000 + 10;
        for (int index = 0; index < size; index++)
            testVector.push_back(rand() % 1000);

        //use random vectors for initial calibraition
        if (i < ORDER) {    //basic fulfill
            sortWithTiming(testVector);
            constants.replaceString(i, getTimerString());
            constants.calculateConstantsByGauss();
        }
        else    //extra fulfill for precise
            work(testVector);
        
    }
}
void SortInterface::polymorphStarterForSon() {
    timer.set(ORDER);
    constants.set(ORDER);
    std::string className = ((std::string)typeid(*this).name()).substr(6) + std::string(".txt");

    constants.file.setName(className);  //без этого заходит лишь в else
    if (constants.file.isExist())
        constants.read();
    else {
        init();
        constants.write();
    }
}
void SortInterface::work(std::vector<int>& numbers) {
    sortWithTiming(numbers);
    int insertionIndex = constants.isMorePrecise(getTimerString());
    if (insertionIndex > -1) {
        constants.replaceString(insertionIndex, getTimerString());
        constants.calculateConstantsByGauss();
        constants.write();
    }
}

//
void Insert::insert(std::vector<int>& numbers) {
    for (int j{ 1 }; j < numbers.size(); j++) { //c1 * n
        timer.increaseCycle(0);
        int key = numbers[j];   //c2 * (n - 1)
        int i = j - 1;  //с3 * (n - 1)
        while (i >= 0 && numbers[i] > key) {    //с4 * (n - 1) в наименьшем (в любом случае
            timer.increaseCycle(1);
            numbers[i + 1] = numbers[i];
            i--;
        }
        numbers[i + 1] = key;   //с7 * (n - 1)
    }
}
Insert::Insert() { polymorphStarterForSon(); }
void Insert::sort(std::vector<int>& numbers) {
    insert(numbers);
}
double Insert::getTime(double n) {
    return constants[0] * (n - 1) + constants[1] * (((n - 1) * n) / 4);
}

//
void Merge::merge(std::vector<int>& numbers, int left, int mid, int right) {//c1 * n
    timer.increaseCycle(0, right - left);

    int n1 = mid + 1 - left;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = numbers[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = numbers[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            numbers[k++] = L[i++];
        else
            numbers[k++] = R[j++];
    }

    while (i < n1)
        numbers[k++] = L[i++];
    while (j < n2)
        numbers[k++] = R[j++];
}
void Merge::mergeSortRecursive(std::vector<int>& numbers, int left, int right) {
    timer.increaseCycle(1);
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(numbers, left, mid);
        mergeSortRecursive(numbers, mid + 1, right);
        merge(numbers, left, mid, right);   //с1 * n, c1 * n/2, c1 * n/4 
    }
}
Merge::Merge() { polymorphStarterForSon(); }
void Merge::sort(std::vector<int>& numbers) {
    mergeSortRecursive(numbers, 0, numbers.size() - 1);
}
//функции среднего времени от данного n
double Merge::getTime(double n) {
    return constants[0] * n * log2(n) + constants[1] * n - 1;
}

//
void Heap::maxHeapify(std::vector<int>& numbers, int index, int& heapSize) {
    int left = (index + 1) * 2 - 1;
    int right = (index + 1) * 2;

    int largest = index;
    if (left < heapSize && numbers[left] > numbers[index])
        largest = left;
    if (right < heapSize && numbers[right] > numbers[largest])
        largest = right;

    if (largest != index) {
        std::swap(numbers[largest], numbers[index]);
        maxHeapify(numbers, largest, heapSize);
    }
}
void Heap::buildMaxHeap(std::vector<int>& numbers, int& heapSize) {
    for (int i = numbers.size() / 2 - 1; i >= 0; i--) {
        timer.increaseCycle(0);
        maxHeapify(numbers, i, heapSize);
    }
}

void Heap::heap(std::vector<int>& numbers) {
    int heapSize = numbers.size();
    buildMaxHeap(numbers, heapSize);
    for (int i = numbers.size() - 1; i > 0; i--) {
        timer.increaseCycle(1);
        std::swap(numbers[0], numbers[i]);
        heapSize--;
        maxHeapify(numbers, 0, heapSize);
    }
}

Heap::Heap() { polymorphStarterForSon(); }
void Heap::sort(std::vector<int>& numbers) {
    heap(numbers);
}
double Heap::getTime(double n) {
    return constants[0] * (n / 2) + constants[1] * (n - 1);   //ускоритель относ.quick
}

//
int Quick::partition(std::vector<int>& numbers, int left, int right) {
    timer.increaseCycle(0);
    int x = numbers[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (numbers[j] <= x) {
            i++;
            std::swap(numbers[i], numbers[j]);	//вроде может быть самозамена
        }
    }
    std::swap(numbers[i + 1], numbers[right]);	//можно упростить без ошибок
    return i + 1;
}
void Quick::quickSortRecursive(std::vector<int>& numbers, int left, int right) {
    timer.increaseCycle(1);
    if (left < right) {
        int mid = partition(numbers, left, right);
        quickSortRecursive(numbers, left, mid - 1);
        quickSortRecursive(numbers, mid + 1, right);	//c +2 ошибка
    }
}
Quick::Quick() { polymorphStarterForSon(); }
void Quick::sort(std::vector<int>& numbers) {
    quickSortRecursive(numbers, 0, numbers.size() - 1);
}
double Quick::getTime(double n) {
    return constants[0] * n + constants[1] * n;
}