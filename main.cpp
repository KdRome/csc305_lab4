#include <iostream>
#include "process.h"
#include "algorithms.h"

using namespace std;


vector<Process> inputProcesses();
void displayResults(const vector<Process>& processes);

int main() {
    vector<Process> processes = inputProcesses();
    firstComeFirstServe(processes);
    displayResults(processes);
    return 0;
}

void displayResults(const vector<Process>& processes) {
    double totalTurnaroundTime = 0;
    cout << "Name\tStart Time\tCompletion Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.name << "\t" << process.startTime << "\t\t"
            << process.completionTime << "\t\t" << process.turnaroundTime << "\n";
        totalTurnaroundTime += process.turnaroundTime;
    }
    cout << "Average Turnaround Time: " << (totalTurnaroundTime / processes.size()) << "\n";
}

vector<Process> inputProcesses() {
    int numberOfProcesses;
    cout << "Enter the number of processes: ";
    cin >> numberOfProcesses;

    vector<Process> processes;
    for (int i = 0; i < numberOfProcesses; ++i) {
        string name;
        int priority, burstTime, arrivalTime;

        cout << "Enter process name, priority, burst time, and arrival time: ";
        cin >> name >> priority >> burstTime >> arrivalTime;

        processes.emplace_back(name, priority, burstTime, arrivalTime);
    }
    return processes;
}
