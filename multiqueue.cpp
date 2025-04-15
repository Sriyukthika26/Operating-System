#include <bits/stdc++.h>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int queue_type; // 1: FCFS, 2: SJF, 3: RR
};

void FCFS(vector<Process> &processque, int &current_time) {
    for (auto &p : processque) {
        if (current_time < p.arrival_time)
            current_time = p.arrival_time;

        p.waiting_time = current_time - p.arrival_time;
        p.completion_time = current_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        current_time = p.completion_time;
    }
}

void SJF(vector<Process> &processque, int &current_time) {
    vector<Process*> ready;
    int completed = 0;
    int n = processque.size();
    vector<bool> visited(n, false);

    while (completed < n) {
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && processque[i].arrival_time <= current_time) {
                ready.push_back(&processque[i]);
                visited[i] = true;
            }
        }

        if (!ready.empty()) {
            sort(ready.begin(), ready.end(), [](Process *a, Process *b) {
                return a->burst_time < b->burst_time;
            });

            Process *p = ready.front();
            ready.erase(ready.begin());

            p->waiting_time = current_time - p->arrival_time;
            current_time += p->burst_time;
            p->completion_time = current_time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            completed++;
        } else {
            current_time++;
        }
    }
}

void RoundRobin(vector<Process> &processque, int &current_time, int quantum) {
    queue<Process*> q;
    int n = processque.size();
    vector<bool> in_queue(n, false);
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; ++i) {
            if (!in_queue[i] && processque[i].arrival_time <= current_time) {
                q.push(&processque[i]);
                in_queue[i] = true;
            }
        }

        if (!q.empty()) {
            Process *p = q.front();
            q.pop();

            int exec_time = min(quantum, p->remaining_time);
            p->remaining_time -= exec_time;
            current_time += exec_time;

            for (int i = 0; i < n; ++i) {
                if (!in_queue[i] && processque[i].arrival_time <= current_time) {
                    q.push(&processque[i]);
                    in_queue[i] = true;
                }
            }

            if (p->remaining_time > 0) {
                q.push(p);
            } else {
                p->completion_time = current_time;
                p->turnaround_time = p->completion_time - p->arrival_time;
                p->waiting_time = p->turnaround_time - p->burst_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
}

void printResults(const vector<Process> &processes, const string &title) {
    cout << "\n" << title << ":\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t" << p.turnaround_time << "\t" << p.waiting_time << "\n";
    }
}

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> fcfs_q, sjf_q, rr_q;

    for (int i = 0; i < n; ++i) {
        Process p;
        p.pid = i + 1;
        cout << "Enter Arrival Time, Burst Time, Queue (1:FCFS, 2:SJF, 3:RR) for Process " << p.pid << ": ";
        cin >> p.arrival_time >> p.burst_time >> p.queue_type;
        p.remaining_time = p.burst_time;

        if (p.queue_type == 1)
            fcfs_q.push_back(p);
        else if (p.queue_type == 2)
            sjf_q.push_back(p);
        else
            rr_q.push_back(p);
    }

    cout << "Enter Time Quantum for Round Robin: ";
    cin >> quantum;

    int current_time = 0;

    FCFS(fcfs_q, current_time);
    SJF(sjf_q, current_time);
    RoundRobin(rr_q, current_time, quantum);

    printResults(fcfs_q, "FCFS Queue");
    printResults(sjf_q, "SJF Queue");
    printResults(rr_q, "Round Robin Queue");

    return 0;
}