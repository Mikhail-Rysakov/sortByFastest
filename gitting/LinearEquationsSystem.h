#pragma once
#include <vector>
#include "File.h"

extern const int MIN_LENGTH;

class LinearEquationsSystem {
private:
    std::vector<std::vector<double>> strings; //[string][column], last column is scalar
    std::vector<double> constants;          //[column]
    //universal read/write format
    void fileStructure(bool type);
    ////(documented in docx)
    void narrowTimeAccuracy();
public:
    File file;

    LinearEquationsSystem();
    LinearEquationsSystem(short int order);
    void set(short int order);

    double operator[](unsigned int index) const;

    void read();
    void write();

    void replaceString(int strNum, std::vector<double> newString);
    ////(documented in docx)
    int isMorePrecise(std::vector<double> string);
    
    void calculateConstantsByGauss();
};

