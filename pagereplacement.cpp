#include<bits/stdc++.h>
using namespace std;

// FIFO
int FIFO(const vector<int>& pages, int frames) {
    unordered_set<int> memory;
    queue<int> order;
    int faults = 0;

    cout << "\n[FIFO] Page Replacement:\n";
    for (int page : pages) {
        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int old = order.front();
                order.pop();
                memory.erase(old);
            }
            memory.insert(page);
            order.push(page);
            cout << "Page " << page << " -> Fault\n";
        } else {
            cout << "Page " << page << " -> Hit\n";
        }
    }
    cout << "Total Page Faults (FIFO): " << faults << "\n";
    return faults;
}

// Optimal
int Optimal(const vector<int>& pages, int frames) {
    unordered_set<int> memory;
    int faults = 0;

    cout << "\n[Optimal] Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int farthest = i + 1, pageToRemove = -1;
                int maxIndex = -1;
                for (int memPage : memory) {
                    int j;
                    for (j = i + 1; j < pages.size(); j++) {
                        if (pages[j] == memPage)
                            break;
                    }
                    if (j > maxIndex) {
                        maxIndex = j;
                        pageToRemove = memPage;
                    }
                }
                memory.erase(pageToRemove);
            }
            memory.insert(page);
            cout << "Page " << page << " -> Fault\n";
        } else {
            cout << "Page " << page << " -> Hit\n";
        }
    }
    cout << "Total Page Faults (Optimal): " << faults << "\n";
    return faults;
}

// LRU
int LRU(const vector<int>& pages, int frames) {
    unordered_set<int> memory;
    unordered_map<int, int> recent;
    int faults = 0;

    cout << "\n[LRU] Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (memory.find(page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int lru = INT_MAX, pageToRemove;
                for (auto p : memory) {
                    if (recent[p] < lru) {
                        lru = recent[p];
                        pageToRemove = p;
                    }
                }
                memory.erase(pageToRemove);
            }
            memory.insert(page);
            cout << "Page " << page << " -> Fault\n";
        } else {
            cout << "Page " << page << " -> Hit\n";
        }
        recent[page] = i;
    }
    cout << "Total Page Faults (LRU): " << faults << "\n";
    return faults;
}

int main() {
    int n, frames;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> frames;

    FIFO(pages, frames);
    Optimal(pages, frames);
    LRU(pages, frames);

    return 0;
}