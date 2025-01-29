#include "File.h"

void File::setName(std::string fileName) {
    name = fileName;
    file.open(name);
}

extern const bool READ = 0;
extern const bool WRITE = 1;
void File::setMode(bool type) {
    this->type = type;
    if (this->type == 1)
        std::ofstream createEmptyFile(name);
    file.close();   //without that string "open" realizes double with setName and setMode methods  
    file.open(name);
}

bool File::isExist() const {
    return file.is_open();
}