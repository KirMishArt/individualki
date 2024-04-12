#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void parallelShakerSort(vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    bool swapped = true;

    while (swapped) {
        swapped = false;

#pragma omp parallel default(none) shared(arr, left, right, swapped)
        {
            int localLeft = left;
            int localRight = right;

#pragma omp for schedule(static)
            for (int i = left; i < right; ++i) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                    localRight = i;
                }
            }

#pragma omp for schedule(static)
            for (int i = right; i > left; --i) {
                if (arr[i - 1] > arr[i]) {
                    swap(arr[i - 1], arr[i]);
                    swapped = true;
                    localLeft = i;
                }
            }

#pragma omp single
            {
                if (localLeft < localRight) {
                    left = localLeft;
                    right = localRight;
                }
                else {
                    left = 0;
                    right = arr.size() - 1;
                }
            }
        }
    }
}

int main() {
    vector<int> arr = { 5, 8, 3, 1, 6, 2, 9, 7, 4 };

    parallelShakerSort(arr);

    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }

    return 0;
}
