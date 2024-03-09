#pragma once
// Computer.h
#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>

using namespace std;

class Computer
{
private:
    wstring traceHistory;
    bool doTrace = false;

public:
    wstring calculate(wstring entry);
    wstring getTraceHistory();
    void activateTrace();
    void deactivateTrace();
    void clearTrace();
};

#endif // COMPUTER_H
