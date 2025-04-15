#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int start, completion, turnaround, waiting;
};

// For sorting
bool cmpArr(Process a, Process b) {
    return a.arrival < b.arrival;
}
bool cmpBur(Process a, Process b) {
    return a.burst < b.burst;
}
bool cmpPriority(Process a, Process b) {
    return a.priority < b.priority;
}


void printResults(vector<Process>& processes) {
    float totalTurnaround = 0, totalWaiting = 0;
    cout << "\nPID\tArrival\tBurst\tPriority\tStart\tCompletion\tTurnaround\tWaiting\n";
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority
             << "\t\t" << p.start << "\t" << p.completion << "\t\t"
             << p.turnaround << "\t\t" << p.waiting << endl;
        totalTurnaround += p.turnaround;
        totalWaiting += p.waiting;
    }
    cout << "\nAverage Turnaround Time: " << totalTurnaround / processes.size();
    cout << "\nAverage Waiting Time: " << totalWaiting / processes.size() << endl;
}

// FCFS Scheduling
void fcfs(vector<Process> processes) {
    cout << "\n--- FCFS Scheduling ---\n";
    sort(processes.begin(), processes.end(), cmpArr);
    int currentTime = 0;
    for (auto& p : processes) {
        if (currentTime < p.arrival)
            currentTime = p.arrival;
        p.start = currentTime;
        p.completion = p.start + p.burst;
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;
        currentTime = p.completion;
    }

    printResults(processes);
}

// SJF Scheduling (Non-preemptive)
void sjf(vector<Process> processes) {
    cout << "\n--- SJF (Non-preemptive) Scheduling ---\n";
    int n = processes.size(), completed = 0, currentTime = 0;

    while (completed < n) {
        vector<Process> ready;
        for (const auto& p : processes) {
            if (p.arrival <= currentTime && p.completion == 0)
                ready.push_back(p);
        }
        if (ready.empty()) {
            currentTime++;
            continue;
        }

        sort(ready.begin(), ready.end(), cmpBur);
        for (auto& p : processes) {
            if (p.pid == ready[0].pid) {
                p.start = currentTime;
                p.completion = p.start + p.burst;
                p.turnaround = p.completion - p.arrival;
                p.waiting = p.turnaround - p.burst;
                currentTime = p.completion;
                completed++;
                break;
            }
        }
    }

    printResults(processes);
}

// Priority Scheduling (Non-preemptive)
void priorityScheduling(vector<Process> processes) {
    cout << "\n--- Priority Based Scheduling ---\n";
    int n = processes.size(), completed = 0, currentTime = 0;

    while (completed < n) {
        vector<Process> ready;
        for (const auto& p : processes) {
            if (p.arrival <= currentTime && p.completion == 0)
                ready.push_back(p);
        }
        if (ready.empty()) {
            currentTime++;
            continue;
        }

        sort(ready.begin(), ready.end(), cmpPriority);
        for (auto& p : processes) {
            if (p.pid == ready[0].pid) {
                p.start = currentTime;
                p.completion = p.start + p.burst;
                p.turnaround = p.completion - p.arrival;
                p.waiting = p.turnaround - p.burst;
                currentTime = p.completion;
                completed++;
                break;
            }
        }
    }

    printResults(processes);
}

// SRTF (Shortest Remaining Time First) - Preemptive
void srtf(vector<Process> processes) {
    cout << "\n--- SRTF (Preemptive SJF) Scheduling ---\n";
    int n = processes.size(), completed = 0, currentTime = 0, minRemaining = 1e9;
    vector<int> remainingTime(n);
    for (int i = 0; i < n; i++) remainingTime[i] = processes[i].burst;
    while (completed < n) {
        int idx = -1;
        minRemaining = 1e9;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minRemaining) {
                minRemaining = remainingTime[i];
                idx = i;
            }
        }

        if (idx != -1) {
            if (remainingTime[idx] == processes[idx].burst)
                processes[idx].start = currentTime;
            remainingTime[idx]--;
            currentTime++;

            if (remainingTime[idx] == 0) {
                processes[idx].completion = currentTime;
                processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                completed++;
            }
        } else {
            currentTime++;
        }
    }

    printResults(processes);
}

// Round Robin Scheduling
void roundRobin(vector<Process> processes, int timeQuantum) {
    cout << "\n--- Round Robin Scheduling ---\n";
    int n = processes.size(); int currentTime = 0, completed = 0;
    vector<int> remainingTime(n);
    for (int i = 0; i < n; i++)
        remainingTime[i] = processes[i].burst;

    vector<bool> isStarted(n, false);

    queue<int> readyQueue;

    sort(processes.begin(), processes.end(), cmpArr);
    int idx = 0;

    // Push first arrived processes
    while (idx < n && processes[idx].arrival <= currentTime)
        readyQueue.push(idx++);

    while (completed < n) {
        if (readyQueue.empty()) {
            currentTime = processes[idx].arrival;
            while (idx < n && processes[idx].arrival <= currentTime)
                readyQueue.push(idx++);
            continue;
        }

        int i = readyQueue.front();
        readyQueue.pop();

        if (!isStarted[i]) {
            processes[i].start = max(currentTime, processes[i].arrival);
            isStarted[i] = true;
        }

        int execTime = min(timeQuantum, remainingTime[i]);
        currentTime = max(currentTime, processes[i].arrival) + execTime;
        remainingTime[i] -= execTime;

        // Enqueue newly arrived processes
        while (idx < n && processes[idx].arrival <= currentTime)
            readyQueue.push(idx++);

        if (remainingTime[i] > 0) {
            readyQueue.push(i); // Put it back for future execution
        } else {
            processes[i].completion = currentTime;
            processes[i].turnaround = processes[i].completion - processes[i].arrival;
            processes[i].waiting = processes[i].turnaround - processes[i].burst;
            completed++;
        }
    }

    printResults(processes);
}

// HRRN Scheduling (Non-preemptive)
void hrrn(vector<Process> processes) {
    cout << "\n--- HRRN (Highest Response Ratio Next) Scheduling ---\n";
    int n = processes.size(), completed = 0, currentTime = 0;
    vector<bool> done(n, false);

    while (completed < n) {
        int idx = -1;
        double highestRR = -1.0;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && !done[i]) {
                int waitingTime = currentTime - processes[i].arrival;
                double responseRatio = (waitingTime + processes[i].burst) / (double)processes[i].burst;

                if (responseRatio > highestRR) {
                    highestRR = responseRatio;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            processes[idx].start = currentTime;
            processes[idx].completion = processes[idx].start + processes[idx].burst;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            currentTime = processes[idx].completion;
            done[idx] = true;
            completed++;
        } else {
            currentTime++; // No process is ready, move forward
        }
    }

    printResults(processes);
}

// Main Program
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter Arrival Time, Burst Time, and Priority for each process:\n";
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Process " << processes[i].pid << ": ";
        cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
    }

    fcfs(processes);
    sjf(processes);
    priorityScheduling(processes);
    srtf(processes); 

    return 0;
}
