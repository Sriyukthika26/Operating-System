#include <bits/stdc++.h>
using namespace std;

void FCFS(vector<int> requests, int head) {
    int seekCount = 0;
    cout << "\n[FCFS] Sequence: ";
    for (int i = 0; i < requests.size(); i++) {
        cout << requests[i] << " ";
        seekCount += abs(head - requests[i]);
        head = requests[i];
    }
    cout << "\nTotal Seek Operations: " << seekCount << endl;
}

void SCAN(vector<int> requests, int head, int diskSize, string direction) {
    vector<int> left, right;
    int seekCount = 0;
    vector<int> sequence;

    if (direction == "left")
        left.push_back(0);
    else if (direction == "right")
        right.push_back(diskSize - 1);

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\n[SCAN] Sequence: ";

    if (direction == "left") {
        for (int i = left.size() - 1; i >= 0; i--) {
            cout << left[i] << " ";
            seekCount += abs(head - left[i]);
            head = left[i];
        }
        for (int i = 0; i < right.size(); i++) {
            cout << right[i] << " ";
            seekCount += abs(head - right[i]);
            head = right[i];
        }
    } else {
        for (int i = 0; i < right.size(); i++) {
            cout << right[i] << " ";
            seekCount += abs(head - right[i]);
            head = right[i];
        }
        for (int i = left.size() - 1; i >= 0; i--) {
            cout << left[i] << " ";
            seekCount += abs(head - left[i]);
            head = left[i];
        }
    }

    cout << "\nTotal Seek Operations: " << seekCount << endl;
}

void CSCAN(vector<int> requests, int head, int diskSize) {
    vector<int> left, right;
    int seekCount = 0;
    right.push_back(diskSize - 1);
    left.push_back(0);

    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] < head)
            left.push_back(requests[i]);
        else
            right.push_back(requests[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\n[C-SCAN] Sequence: ";

    for (int i = 0; i < right.size(); i++) {
        cout << right[i] << " ";
        seekCount += abs(head - right[i]);
        head = right[i];
    }

    // Jump to beginning
    head = 0;
    seekCount += (diskSize - 1);  // Simulate jump

    for (int i = 0; i < left.size(); i++) {
        cout << left[i] << " ";
        seekCount += abs(head - left[i]);
        head = left[i];
    }

    cout << "\nTotal Seek Operations: " << seekCount << endl;
}

int main() {
    int n, head, diskSize;
    cout << "Enter number of disk requests: ";
    cin >> n;

    vector<int> requests(n);
    cout << "Enter disk requests (in terms of cylinder numbers):\n";
    for (int i = 0; i < n; i++)
        cin >> requests[i];

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter total disk size (number of cylinders): ";
    cin >> diskSize;

    FCFS(requests, head);
    SCAN(requests, head, diskSize, "left");
    CSCAN(requests, head, diskSize);

    return 0;
}