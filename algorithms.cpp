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
        int idx = -1;
        int minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0) {
                if (processes[i].priority < minPriority) {
                    minPriority = processes[i].priority;
                    idx = i;
                }
                if (processes[i].priority == minPriority) {
                    if (idx == -1 || processes[i].arrivalTime < processes[idx].arrivalTime) {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            if (processes[idx].startTime == -1) {
                processes[idx].startTime = currentTime;
            }
            processes[idx].remainingBurstTime -= 1;
            currentTime++;

            if (processes[idx].remainingBurstTime == 0) {
                processes[idx].completionTime = currentTime;
                processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
                completed++;
                executionOrder.push_back(processes[idx].name); // Add to execution order upon completion
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
        int idx = -1;
        int shortestBurst = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime < shortestBurst && processes[i].completionTime == 0) {
                shortestBurst = processes[i].burstTime;
                idx = i;
            }
        }
        if (idx != -1) {
            processes[idx].startTime = currentTime;
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            currentTime = processes[idx].completionTime;
            completed++;
            executionOrder.push_back(processes[idx].name); // Add to execution order upon completion
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
    int currentTime = processes.empty() ? 0 : processes[0].arrivalTime;
    queue<int> processQueue;
    vector<string> executionOrder; // Vector to store the order of execution

    // Enqueue processes based on arrival time
    for (int i = 0; i < processes.size(); ++i) {
        if (processes[i].arrivalTime <= currentTime) {
            processQueue.push(i);
        }
    }

    while (!processQueue.empty()) {
        int idx = processQueue.front();
        processQueue.pop();

        // Skip already completed processes
        if (processes[idx].remainingBurstTime <= 0) continue;

        if (processes[idx].startTime == -1) {
            processes[idx].startTime = currentTime;
        }

        // Record the execution order as the process gets the CPU
        executionOrder.push_back(processes[idx].name);

        int executionTime = min(quantum, processes[idx].remainingBurstTime);
        processes[idx].remainingBurstTime -= executionTime;
        currentTime += executionTime;

        // Enqueue other processes that have now arrived and are not completed
        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingBurstTime > 0 && i != idx) {
                processQueue.push(i);
            }
        }

        // Re-enqueue if not finished
        if (processes[idx].remainingBurstTime > 0) {
            processQueue.push(idx);
        }
        else {
            // Set completion time
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
        }
    }

    // Print the order of execution
    cout << "Order of execution: ";
    for (const auto& processName : executionOrder) {
        cout << processName << " -> ";
    }
    cout << "end" << endl;
}
