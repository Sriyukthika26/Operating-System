#include<bits/stdc++.h>
using namespace std;

void LOOK(vector<int> tracks, int head) {
    vector<int> left, right;
    int seekCount = 0;

    for (int i = 1; i < tracks.size(); i++) {
        if (tracks[i] < head)
            left.push_back(tracks[i]);
        else
            right.push_back(tracks[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\n[LOOK] Sequence: ";
    // Going Right
    for (int track : right) {
        cout << track << " ";
        seekCount += abs(head - track);
        head = track;
    }

    // Going Left
    for (int i = left.size() - 1; i >= 0; i--) {
        cout << left[i] << " ";
        seekCount += abs(head - left[i]);
        head = left[i];
    }

    cout << "\nTotal Seek Operations: " << seekCount << "\n";
}

void CLOOK(vector<int> tracks, int head) {
    vector<int> left, right;
    int seekCount = 0;

    for (int i = 1; i < tracks.size(); i++) {
        if (tracks[i] < head)
            left.push_back(tracks[i]);
        else
            right.push_back(tracks[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    cout << "\n[C-LOOK] Sequence: ";
    // Going Right
    for (int track : right) {
        cout << track << " ";
        seekCount += abs(head - track);
        head = track;
    }

    // Jump to the beginning of the left
    if (!left.empty()) {
        seekCount += abs(head - left[0]);
        head = left[0];
        cout << left[0] << " ";

        for (int i = 1; i < left.size(); i++) {
            cout << left[i] << " ";
            seekCount += abs(head - left[i]);
            head = left[i];
        }
    }

    cout << "\nTotal Seek Operations: " << seekCount << "\n";
}

// SSTF Algorithm
void sstf(vector<int> requests, int head) {
    cout << "\n--- SSTF ---\n";
    vector<int> sequence;
    vector<bool> visited(requests.size(), false);
    int total = 0;
    int current = head;

    for (int i = 0; i < requests.size(); ++i) {
        int minDist = INT_MAX, index = -1;
        for (int j = 0; j < requests.size(); ++j) {
            if (!visited[j] && abs(requests[j] - current) < minDist) {
                minDist = abs(requests[j] - current);
                index = j;
            }
        }
        visited[index] = true;
        total += minDist;
        current = requests[index];
        sequence.push_back(current);
    }

    cout << "Sequence: " << head << " -> ";
    for (int r : sequence) cout << r << " -> ";
    cout << "End\n";
    cout << "Total Head Movement = " << total << " cylinders\n";
}
int main() {
    int n;
    cout << "Enter Number of Tracks: ";
    cin >> n;

    vector<int> tracks(n + 1);
    cout << "Enter Track Positions (first is head position): ";
    for (int i = 0; i <= n; i++) {
        cin >> tracks[i];
    }

    int head = tracks[0];

    LOOK(tracks, head);
    CLOOK(tracks, head);
    sstf(tracks, head);

    return 0;
}