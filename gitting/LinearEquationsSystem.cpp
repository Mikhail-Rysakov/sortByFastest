#include "LinearEquationsSystem.h"
#include <fstream>

extern const int MIN_LENGTH = 10;

void LinearEquationsSystem::fileStructure(bool type) {
    file.setMode(type);
    for (int i = 0; i < strings.size(); i++) {
        file.rw<double>(constants[i]);
        for (int j = 0; j < strings.size() + 1; j++)
            file.rw<double>(strings[i][j]);
    }
}
//(documented in docx)
void LinearEquationsSystem::narrowTimeAccuracy() {
    //use algorithm if strings intersect on negative quarter (2 or 4 sector)
    if (constants[0] * constants[1] < 0) {
        const int TIME = 2;
        bool axis = constants[1] > 0;   //axis where we will lift down the string
        //less accurate and much accurate indexes of string
        bool biggest = strings[0][TIME] / strings[0][axis] < strings[1][TIME] / strings[1][axis];
        bool smallest = !biggest;
        //reducing the less accurate to much accurate into positive sector (1)
        strings[biggest][TIME] = strings[biggest][axis] * (strings[smallest][TIME] / strings[smallest][axis]);
        constants[axis] = strings[smallest][TIME] / strings[smallest][axis];
        constants[!axis] = 0;
    }
}
LinearEquationsSystem::LinearEquationsSystem() {}
LinearEquationsSystem::LinearEquationsSystem(short int order) {
    constants.resize(order);
    std::vector<double> zero(order + 1);
    strings.resize(order, zero);
}
void LinearEquationsSystem::set(short int order) {
    constants.resize(order);
    std::vector<double> zero(order + 1);
    strings.resize(order, zero);
}

double LinearEquationsSystem::operator[](unsigned int index) const { return constants[index]; }
void LinearEquationsSystem::read() { fileStructure(READ); }
void LinearEquationsSystem::write() { fileStructure(WRITE); }
void LinearEquationsSystem::replaceString(int strNum, std::vector<double> newString) {
    strings[strNum] = newString;
}
//(documented in docx)
int LinearEquationsSystem::isMorePrecise(std::vector<double> string) const {
    //don't take too short cycles for accuracy and correctness
    if (string[0] < MIN_LENGTH || string[1] < MIN_LENGTH)   //слишком короткие не уточняют, можно вынести в константы
        return -1;
    //find out, if new string intersect axis closer to 0,0 cordinates, then one of current strings
    double longX[2]{ strings[0][2] / strings[0][0], strings[1][2] / strings[1][0] };
    double longY[2]{ strings[0][2] / strings[0][1], strings[1][2] / strings[1][1] };
    bool minY = (longY[0] > longY[1]);
    bool minX = (longX[0] > longX[1]);
    double mx = string[2] / string[0], my = string[2] / string[1];
    //return insert index, if condition is true, and -1 when false
    if (mx < longX[minX])
        return minX;
    else if (my < longY[minY])
        return minY;
    return -1;
}
//decide linear equations system by famous Gauss method
void LinearEquationsSystem::calculateConstantsByGauss() {
    int order = strings.size();
    std::vector<std::vector<double>> stringsCopy = strings;
    const int TIME = order;
    //go from bottom string to upper
    for (int str = order - 1; str >= 0; str--) {
        for (int upperStr = str - 1; upperStr >= 0; upperStr--) {
            //diagonal '/' or '\' choosen by multiplier order
            double multiplier = stringsCopy[str][str] / stringsCopy[upperStr][str];
            for (int clmn = 0; clmn < order; clmn++)
                stringsCopy[upperStr][clmn] = stringsCopy[upperStr][clmn] * multiplier - stringsCopy[str][clmn];
            stringsCopy[upperStr][TIME] = stringsCopy[upperStr][TIME] * multiplier - stringsCopy[str][TIME];
        }
    }
    //calculate constants
    for (int str = 0; str < order; str++) {
        for (int clmn = str - 1; clmn >= 0; clmn--)
            stringsCopy[str][TIME] -= stringsCopy[str][clmn] * constants[clmn];
        constants[str] = stringsCopy[str][TIME] / stringsCopy[str][str];
    }
           
    narrowTimeAccuracy();
}