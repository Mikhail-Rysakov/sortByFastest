#pragma once
#include <fstream>
#include <vector>
#include <iostream>

extern const bool READ;
extern const bool WRITE;

class File {
private:
    std::string name;
    std::fstream file;
    bool type;  //READ or WRITE from const above
public:
    void setName(std::string fileName);

    void setMode(bool type);

    bool isExist() const;

    //potential amount of types is huge (double, int, string ...), so there is template
    template<typename T>
    void rw(double& data) {
        static const std::vector<void(*)(std::fstream&, T&)> readWrite = {
        [](std::fstream& file, T& data) { file >> data; },
        [](std::fstream& file, T& data) { file << data << " ";}
        };
        readWrite[type](file, data);
    }

};