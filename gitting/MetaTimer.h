#pragma once
#include <chrono>
#include <vector>

class MetaTimer {
private:
    std::vector<double> metaString;
    std::chrono::steady_clock::time_point startTime, stopTime;
public:
    MetaTimer();
    MetaTimer(int cyclesNum);
    void set(int cyclesNum);
    
    void start();
    void stop(); //return automatically
    //++
    void increaseCycle(int index);
    //a bit slower, but can add not ++, but += 
    void increaseCycle(int index, int biggerThanOne);

    std::vector<double> getMetaString() const;
};
