#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> avail(m);

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> alloc[i][j];

    cout << "\nEnter Maximum Requirement Matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> max[i][j];

    // Calculate Need = Max - Allocation
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            need[i][j] = max[i][j] - alloc[i][j];

    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < m; ++j)
        cin >> avail[j];

    vector<bool> finish(n, false);
    vector<int> safeSeq;
    bool found;

    for (int count = 0; count < n; ++count) {
        found = false;

        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canExecute = true;

                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > avail[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (int j = 0; j < m; ++j)
                        avail[j] += alloc[i][j];

                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) break;
    }

    bool safe = true;
    for (bool f : finish)
        if (!f) safe = false;

    if (safe) {
        cout << "\nSystem is in a SAFE state.\nSafe sequence: ";
        for (int i : safeSeq)
            cout << "P" << i << " ";
        cout << endl;
    } else {
        cout << "\nSystem is in an UNSAFE state. Deadlock may occur.\n";
    }

    return 0;
}