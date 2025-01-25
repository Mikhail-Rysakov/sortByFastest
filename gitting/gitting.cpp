
#include <iostream>
#include "SortAgregator.h"


bool isPreciserCorrect() {
    //CONFIG (func = c1 * (n-1) + c2 * (n-1) * n / 2);
    int numberOfTests = 1000000;
    int maxN = SHRT_MAX / 10;
    int maxC = INT_MAX / (maxN * maxN / 2 + maxN / 2 - 1);
    int err = 2;    //precise
    int order = 2;

    //MULTIPLE TESTS
    //vary constants
    LinearEquationsSystem equations(order);
    int c1 = rand() % maxC, c2 = rand() % maxC;
    for (int testNumber = 0; true; testNumber++) {
        //TEST INPUT
        int n = rand() % maxN;
        double x = (n - 1), y = (n - 1) * n / 2;
        int realTime = c1 * x + c2 * y;
        double noiseTime = realTime + rand() % (realTime + 1);

        //ALGORITHM
        std::vector<double> string{ x, y, noiseTime };
        int insertionIndex = equations.isMorePrecise(string);
        if (testNumber < 2) {
            equations.replaceString(testNumber, string);
            equations.calculateConstantsByGauss();
        }
        else if (insertionIndex > -1) {
            equations.replaceString(insertionIndex, string);
            equations.calculateConstantsByGauss();

            //OUTPUT
            if (equations[0] - c1 < err && equations[1] - c2 < err) {
                std::cout << c1 << "&" << c2 << " = " << equations[0] << "&" << equations[1] << std::endl;
                return 1;
            }

        }


    }
    std::cout << "INCORRECT = " << c1 << "&" << c2 << " = " << equations[0] << "&" << equations[1] << std::endl;
    return 0;
}
bool isSortCorrect(SortInterface* sort) {
    //TEST INPUT
    std::vector<int> numbers;
    int size = rand() % SHRT_MAX;
    for (int i = 0; i < size; i++)
        numbers.push_back(rand() % SHRT_MAX);

    int precSum = numbers[0];
    for (int i = 1; i < numbers.size(); i++)
        precSum += numbers[i];

    //TEST OUTPUT (ALGORITHM)
    sort->sort(numbers);

    int postSum = numbers[0];
    for (int i = 1; i < numbers.size(); i++)
        postSum += numbers[i];

    if (precSum != postSum) {
        std::cout << "ERROR1 IN SORTING" << std::endl;
        return 0;
    }

    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i - 1] > numbers[i]) {//проверка на неубывание слева направо
            std::cout << "ERROR2 IN SORTING " << std::endl;
            system("pause");
            return 0;
        }

    }
    std::cout << "SORTING IS CORRECT" << std::endl;
    return 1;
}
#include <iomanip>
void isCorrectTime(SortInterface* sorting) {
    //OPTIONS
    int step = 10;
    int range[]{ initialN, initialN + 100 };   //100 проходов

    //INPUT (внедрить prolonger), но реально ли?
    std::cout << " [" << std::setw(3) << "n" << "] " << std::setw(3) << "cycle1" << " " << std::setw(4)
        << "cycle2" << " = " << "time" << std::endl;
    for (int n = range[0]; n <= range[1]; n += step) {
        //взятие среднего значения времени и цикловых переменных
        std::vector<double> minTimeString{ 0,0,INT_MAX }, maxTimeString{ 0,0,0 };
        for (int randomizer = 0; randomizer < 100; randomizer++) {
            //взятие реального фактического значения (в крайне низких значениях ниже точность)
            std::vector<int> testVector;
            for (int i = 0; i < n; i++)
                testVector.push_back(rand() % 10000);

            int minimizingRetests = 1000;
            std::vector<std::vector<int>> testVectors(minimizingRetests, testVector);   //эта 100 и следующая 100 единые числа
            std::vector<double> actualTimeString{ 0,0,INT_MAX };
            for (int minimizer = 0; minimizer < minimizingRetests; minimizer++) {
                sorting->sortWithTiming(testVectors[minimizer]);
                if (sorting->getTimerString()[2] < actualTimeString[2])
                    actualTimeString = sorting->getTimerString();
            }

            if (actualTimeString[2] < minTimeString[2])
                minTimeString = actualTimeString;
            if (actualTimeString[2] > maxTimeString[2])
                maxTimeString = actualTimeString;
        }

        std::vector<int> average;
        for (int i = 0; i < minTimeString.size(); i++)
            average.push_back((int)(minTimeString[i] + maxTimeString[i]) / 2);

        std::cout << " [" << std::setw(3) << n << "] " << std::setw(3) << average[0] << " " << std::setw(4)
            << average[1] << " = " << average[2] << std::endl;

    }

}

int main()
{
    Insert sorting; //all types
    isCorrectTime(&sorting);
    for (int testNumber = 0; testNumber < 1000; testNumber++) {
        //isPreciserCorrect();  //vary constants
        //isSortCorrect(&sorting);
    }
        
}

