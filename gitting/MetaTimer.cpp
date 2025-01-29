#include "MetaTimer.h"

MetaTimer::MetaTimer() {}
MetaTimer::MetaTimer(int cyclesNum) {
    metaString.resize(cyclesNum + 1);
}

void MetaTimer::set(int cyclesNum) {
    metaString.resize(cyclesNum + 1);
}

void MetaTimer::start() {
    for (int i = 0; i < metaString.size(); i++)
        metaString[i] = 0;
    startTime = std::chrono::high_resolution_clock::now();
}

void MetaTimer::stop() {
    stopTime = std::chrono::high_resolution_clock::now();
    metaString[metaString.size() - 1] = std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime - startTime).count();
}

void MetaTimer::increaseCycle(int index) {
    metaString[index]++;
}

void MetaTimer::increaseCycle(int index, int biggerThanOne) {
    metaString[index] += biggerThanOne;
}

std::vector<double> MetaTimer::getMetaString() const { return metaString; }