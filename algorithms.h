#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include "process.h"

void firstComeFirstServe(vector<Process>& processes);
void priority(vector<Process>& processes);
void shortestJobNext(vector<Process>& processes);
void roundRobin(vector<Process>& processes);

#endif