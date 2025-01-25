#include "SortAgregator.h"

extern const int initialN = 2; 

void SortAgregator::sortSorts() {
    
    for (int i = 1; i < sorts.size(); i++)
        if (sorts[i]->getTime(initialN) < sorts[0]->getTime(initialN))
            std::swap(sorts[i], sorts[0]);

    intersects.clear();
    for (int i = 1; i < sorts.size(); i++) {
        int minN = INT_MAX;
        for (int j = i; j < sorts.size(); j++) { 
            int n = intersect(sorts[i - 1], sorts[j]);
            if (n <= initialN) { 
                sorts.erase(sorts.begin() + j);
                j--;
            }
            else if (n < minN) {
                minN = n;
                std::swap(sorts[j], sorts[i]);
            }
        }
        intersects.push_back(minN);
    }
    intersects.push_back(INT_MAX);
}

int SortAgregator::intersect(SortInterface* sort1, SortInterface* sort2) {
    //Настройка
    const int LEFT = 0, MIDDLE = 1, RIGHT = 2;
    const double eps = 1;
    double interval[] = { initialN, -1, 100000 };
    double funcs[] = { 0,0,0 };

    //Узнаем, пересекаются ли наши монотонные функции на начальном интервале поиска
    funcs[LEFT] = sort1->getTime(interval[LEFT]) - sort2->getTime(interval[LEFT]);
    funcs[RIGHT] = sort1->getTime(interval[RIGHT]) - sort2->getTime(interval[RIGHT]);
    bool isDifferentSigns = funcs[LEFT] * funcs[RIGHT] < 0;

    //Если песекаются (разные знаки на краях), то алгоритм половинного деления
    if (isDifferentSigns) {
        while ((interval[RIGHT] - interval[LEFT]) / 2 > eps) {
            interval[MIDDLE] = (interval[LEFT] + interval[RIGHT]) / 2;
            funcs[LEFT] = sort1->getTime(interval[LEFT]) - sort2->getTime(interval[LEFT]);
            funcs[MIDDLE] = sort1->getTime(interval[MIDDLE]) - sort2->getTime(interval[MIDDLE]);
            isDifferentSigns = funcs[LEFT] * funcs[MIDDLE] < 0;
            interval[isDifferentSigns * 2] = interval[MIDDLE];
        }
    }
    return interval[MIDDLE];    //-1, если нет пересечения
}
SortAgregator::SortAgregator() {
    sortSorts();
}
void SortAgregator::sortByFastest(std::vector<int>& numbers) {

    int fastestIter;
    for (fastestIter = 0; fastestIter < intersects.size(); fastestIter++)
        if (numbers.size() < intersects[fastestIter])
            break;

    int precConstants = sorts[fastestIter]->constants[0] + sorts[fastestIter]->constants[1];
    sorts[fastestIter]->work(numbers);
    int postConstants = sorts[fastestIter]->constants[0] + sorts[fastestIter]->constants[1];
    bool isConstantsChanged = (precConstants != postConstants);
    if (isConstantsChanged)
        sortSorts();
}
void SortAgregator::show() {
    for (int i = 0; i < sorts.size(); i++) {
        std::cout << (std::string)typeid(*sorts[i]).name() << "=>" << intersects[i] << ",  ";
    }
    std::cout << std::endl;
}


void sortByFastest(std::vector<int>& numbers) {
    static SortAgregator sa;
    sa.sortByFastest(numbers);
}