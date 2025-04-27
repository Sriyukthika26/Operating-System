#include<bits/stdc++.h>
using namespace std;

// Partition function (like in Quicksort)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // take last element as pivot
    int i = low;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

// Quickselect function to find kth smallest
int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low <= high) {
        int pi = partition(arr, low, high);

        if (pi == k) return arr[pi];
        else if (pi > k) return quickSelect(arr, low, pi - 1, k);
        else return quickSelect(arr, pi + 1, high, k);
    }
    return -1;
}

// kth smallest is at index k-1
int kthSmallest(vector<int> arr, int k) {
    return quickSelect(arr, 0, arr.size() - 1, k - 1);
}

// kth largest is at index n-k
int kthLargest(vector<int> arr, int k) {
    int n = arr.size();
    return quickSelect(arr, 0, n - 1, n - k);
}

int main() {
    vector<int> arr = {12, 3, 5, 7, 19, 4, 26};
    int k = 3;

    int smallest = kthSmallest(arr, k);
    int largest = kthLargest(arr, k);

    cout << k << "rd Smallest Element: " << smallest << endl;
    cout << k << "rd Largest Element: " << largest << endl;

    return 0;
}
