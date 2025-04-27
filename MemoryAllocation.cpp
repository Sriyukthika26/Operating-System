#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void bestFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1);
    for (int i = 0; i < processes.size(); i++) {
        int bestIndex = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                if (bestIndex == -1 || blocks[j] < blocks[bestIndex]) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blocks[bestIndex] -= processes[i];
        }
    }

    cout << "\nBest Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "Process " << i + 1 << " (size " << processes[i] << ") -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

void worstFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1);
    for (int i = 0; i < processes.size(); i++) {
        int worstIndex = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIndex == -1 || blocks[j] > blocks[worstIndex]) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blocks[worstIndex] -= processes[i];
        }
    }

    cout << "\nWorst Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "Process " << i + 1 << " (size " << processes[i] << ") -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

void nextFit(vector<int> blocks, vector<int> processes) {
    vector<int> allocation(processes.size(), -1);
    int lastPos = 0;
    int n = blocks.size();

    for (int i = 0; i < processes.size(); i++) {
        int j = lastPos;
        bool allocated = false;
        int count = 0;
        while (count < n) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                blocks[j] -= processes[i];
                lastPos = j;
                allocated = true;
                break;
            }
            j = (j + 1) % n;
            count++;
        }
    }

    cout << "\nNext Fit Allocation:\n";
    for (int i = 0; i < processes.size(); i++) {
        cout << "Process " << i + 1 << " (size " << processes[i] << ") -> ";
        if (allocation[i] != -1)
            cout << "Block " << allocation[i] + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

int main() {
    vector<int> memoryBlocks = {100, 500, 200, 300, 600};
    vector<int> processes = {212, 417, 112, 426};

    bestFit(memoryBlocks, processes);
    worstFit(memoryBlocks, processes);
    nextFit(memoryBlocks, processes);

    return 0;
}
