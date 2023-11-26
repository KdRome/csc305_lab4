#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Process {
public:
    string name;
    int priority;
    int burstTime;
    int arrivalTime;
    int startTime;
    int completionTime;
    int turnaroundTime;

    Process(string n, int p, int bt, int at)
        : name(n), priority(p), burstTime(bt), arrivalTime(at),
        startTime(0), completionTime(0), turnaroundTime(0) {}
};
#endif