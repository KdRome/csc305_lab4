#include "algorithms.h"
#include "process.h"

void firstComeFirstServe(vector<Process>& processes) {
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0;
    for (auto& process : processes) {
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }
        process.startTime = currentTime;
        process.completionTime = process.startTime + process.burstTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        currentTime = process.completionTime;
    }
}
