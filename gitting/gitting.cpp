
#include <iostream>
#include "LinearEquationsSystem.h"


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


int main()
{
    for (int varyConstants = 0; varyConstants < 1000; varyConstants++)
        isPreciserCorrect();
}

