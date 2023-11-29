#include <climits>
#include "algorithms.h"
#include "process.h"

void firstComeFirstServe(vector<Process>& processes) {
    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
        });

    int currentTime = 0;
    vector<string> executionOrder; // Vector to store the order of execution

    for (auto& process : processes) {
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }
        process.startTime = currentTime;
        process.completionTime = process.startTime + process.burstTime;
        process.turnaroundTime = process.completionTime - process.arrivalTime;
        currentTime = process.completionTime;
        executionOrder.push_back(process.name); // Add to execution order
    }

    // Print the order of execution
    cout << "Order of execution: ";
    for (const auto& processName : executionOrder) {
        cout << processName << " -> ";
    }
    cout << "end" << endl;
}

void priority(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    vector<string> executionOrder; // Vector to store the order of execution

    while (completed != n) {
        int index = -1;
        int minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0) {
                if (processes[i].priority < minPriority) {
                    minPriority = processes[i].priority;
                    index = i;
                }
                if (processes[i].priority == minPriority) {
                    if (index == -1 || processes[i].arrivalTime < processes[index].arrivalTime) {
                        index = i;
                    }
                }
            }
        }
        if (index != -1) {
            if (processes[index].startTime == -1) {
                processes[index].startTime = currentTime;
            }
            processes[index].remainingBurstTime -= 1;
            currentTime++;

            if (processes[index].remainingBurstTime == 0) {
                processes[index].completionTime = currentTime;
                processes[index].turnaroundTime = processes[index].completionTime - processes[index].arrivalTime;
                completed++;
                executionOrder.push_back(processes[index].name); // Add to execution order upon completion
            }
        }
        else {
            currentTime++;
        }
    }

    // Print the order of execution
    cout << "Order of execution: ";
    for (const auto& processName : executionOrder) {
        cout << processName << " -> ";
    }
    cout << "end" << endl;
}


void shortestJobNext(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    vector<string> executionOrder; // Vector to store the order of execution

    while (completed != n) {
        int index = -1;
        int shortestBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime < shortestBurst && processes[i].completionTime == 0) {
                shortestBurst = processes[i].burstTime;
                index = i;
            }
        }
        if (index != -1) {
            processes[index].startTime = currentTime;
            processes[index].completionTime = currentTime + processes[index].burstTime;
            processes[index].turnaroundTime = processes[index].completionTime - processes[index].arrivalTime;
            currentTime = processes[index].completionTime;
            completed++;
            executionOrder.push_back(processes[index].name); // Add to execution order upon completion
        }
        else {
            currentTime++;
        }
    }
    // Print the order of execution
    cout << "Order of execution: ";
    for (const auto& processName : executionOrder) {
        cout << processName << " -> ";
    }
    cout << "end" << endl;
}

void roundRobin(vector<Process>& processes, int quantum) {
    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    queue<int> processQueue;
    vector<string> executionOrder;
    size_t processIndex = 0; // Tracks the next process to be enqueued

    while (processIndex < processes.size() || !processQueue.empty()) {
        // Enqueue processes that have arrived
        while (processIndex < processes.size() && processes[processIndex].arrivalTime <= currentTime) {
            processQueue.push(processIndex++);
        }

        if (processQueue.empty()) {
            currentTime = processes[processIndex].arrivalTime;
            continue;
        }

        int index = processQueue.front();
        processQueue.pop();
        Process& proc = processes[index];

        if (proc.startTime == -1) {
            proc.startTime = currentTime;
        }

        executionOrder.push_back(proc.name);
        int executionTime = min(quantum, proc.remainingBurstTime);
        proc.remainingBurstTime -= executionTime;
        currentTime += executionTime;

        // Re-enqueue if not finished
        if (proc.remainingBurstTime > 0) {
            processQueue.push(index);
        }
        else {
            proc.completionTime = currentTime;
            proc.turnaroundTime = proc.completionTime - proc.arrivalTime;
            proc.waitingTime = proc.turnaroundTime - proc.burstTime;
        }
    }

    // Print the order of execution
    cout << "Order of execution: ";
    for (const auto& processName : executionOrder) {
        cout << processName << " -> ";
    }
    cout << "end\n";
}