#include <iostream>
#include "process.h"
#include "algorithms.h"

using namespace std;

vector<Process> inputProcesses();
void displayResults(const vector<Process>& processes);
void userSelection(vector<Process>& processes);
void resetProcessStates(vector<Process>& processes);

int main() {
    vector<Process> processes = inputProcesses();
    userSelection(processes);
    return 0;
}

void userSelection(vector<Process>& processes) {
    
    int userInput = 0;
    int quantum = 0;

    do {
        cout << "\nSelect which algorithm you would like to run\n" << endl;
        
        cout << "1. First Come - First Serve: Non-preemptive" << endl;
        cout << "2. Priority: Pre-emptive" << endl;
        cout << "3. Shortest Job Next: Non-preemptive" << endl;
        cout << "4. Round Robin: Non-preemptive\n" << endl;
        cin >> userInput;

        resetProcessStates(processes);

        switch (userInput) {
            case 1:
                firstComeFirstServe(processes);
                displayResults(processes);
                break;
            case 2:
                priority(processes);
                displayResults(processes);
                break;
            case 3:
                shortestJobNext(processes);
                displayResults(processes);
                break;
            case 4:
                cout << "Enter the Time Quantum: " << endl;
                cin >> quantum;
                roundRobin(processes, quantum);
                displayResults(processes);
                break;
            default:
                cout << "Select one of the options" << endl;
                break;
        }
        userSelection(processes);
    }while (userInput > 4 || userInput < 1);
}

void resetProcessStates(vector<Process>& processes) {
    for (auto& process : processes) {
        process.startTime = -1;
        process.completionTime = 0;
        process.turnaroundTime = 0;
        process.remainingBurstTime = process.burstTime;
    }
}

void displayResults(const vector<Process>& processes) {
    double totalTurnaroundTime = 0;
    cout << "Name\tStart Time\tCompletion Time\tTurn Around Time\n";
    for (const auto& process : processes) {
        cout << process.name << "\t" << process.startTime << "\t\t"
            << process.completionTime << "\t\t" << process.turnaroundTime << "\n";
        totalTurnaroundTime += process.turnaroundTime;
    }
    cout << "Average Turn Around Time: " << (totalTurnaroundTime / processes.size()) << "\n";
}

vector<Process> inputProcesses() {
    int numberOfProcesses;
    cout << "Enter the number of processes: ";
    cin >> numberOfProcesses;

    vector<Process> processes;
    for (int i = 0; i < numberOfProcesses; ++i) {
        string name;
        int priority, burstTime, arrivalTime;

        cout << "Enter process name, arrival time, priority, and burst time (seperated by a space): ";
        cin >> name >> arrivalTime >> priority >> burstTime;

        processes.emplace_back(name, priority, burstTime, arrivalTime);
    }
    return processes;
}
