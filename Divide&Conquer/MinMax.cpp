#include<bits/stdc++.h>
using namespace std;

struct MinMax {
    int min;
    int max;
};

MinMax findMinMax(const vector<int>& arr, int low, int high) {
    MinMax result, left, right;

    // If only one element
    if (low == high) {
        result.min = result.max = arr[low];
        return result;
    }

    // If two elements
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    // More than two elements, divide the array
    int mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    // Combine results
    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);
    return result;
}

int main() {
    vector<int> arr = {4, 8, 1, 9, 2, 10, 3, 7};

    MinMax result = findMinMax(arr, 0, arr.size() - 1);

    cout << "Minimum element: " << result.min << endl;
    cout << "Maximum element: " << result.max << endl;

    return 0;
}
