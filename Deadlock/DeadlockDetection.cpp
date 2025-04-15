#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m; // n = number of processes, m = number of resources
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> request(n, vector<int>(m));
    vector<int> available(m);

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "\nEnter Request (Need) Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> request[i][j];

    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> available[j];

    vector<bool> finish(n, false);
    bool changed = true;

    while (changed) {
        changed = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        available[j] += allocation[i][j];
                    finish[i] = true;
                    changed = true;
                }
            }
        }
    }

    bool deadlock = false;
    cout << "\nProcesses in Deadlock: ";
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            cout << "P" << i << " ";
            deadlock = true;
        }
    }

    if (!deadlock)
        cout << "None. System is in a safe state.\n";
    else
        cout << "\nDeadlock detected!\n";

    return 0;
}