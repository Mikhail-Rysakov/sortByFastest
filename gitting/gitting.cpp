
#include <iostream>
#include "Sorts.h"


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

int main()
{

    for (int testNumber = 0; testNumber < 1000; testNumber++) {
        //isPreciserCorrect();  //vary constants
        //isSortCorrect(&sorting);
    }
        
}

