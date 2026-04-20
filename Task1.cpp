#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include <future>
#include <iomanip>
#include <algorithm>
#include <windows.h>

using namespace std;
using namespace std::chrono;

void printArray(int arr[], int n, string message) {
    cout << message << " (first 15 elements): " << endl;
    for (int i = 0; i < min(n, 15); i++) {
        cout << arr[i] << " ";
    }
    if (n > 15) cout << "...";
    cout << endl;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void comparePerformance(void (*sortFunc)(int*, int), string name, int n) {
    int* sArr = new int[n];
    int* aArr = new int[n];
    for (int i = 0; i < n; i++) sArr[i] = aArr[i] = rand() % 10000;

    auto start = high_resolution_clock::now();
    sortFunc(sArr, n);
    double tSync = duration<double>(high_resolution_clock::now() - start).count();

    start = high_resolution_clock::now();
    future<void> fut = async(launch::async, sortFunc, aArr, n);
    fut.get();
    double tAsync = duration<double>(high_resolution_clock::now() - start).count();

    cout << left << setw(15) << name << setw(15) << tSync << setw(15) << tAsync << endl;

    delete[] sArr; delete[] aArr;
}

int main() {
    int n;
    cout << "Enter the number of items: ";
    cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = rand() % 2000;

    printArray(arr, n, "\nGenerated massif");

    cout << "\nChoose method (1-Buble, 2-Insertion, 3-Shell): ";
    int choice; cin >> choice;

    if (choice == 1) bubbleSort(arr, n);
    else if (choice == 2) insertionSort(arr, n);
    else shellSort(arr, n);

    printArray(arr, n, "Sorted massif");

    int key;
    cout << "\nEnter the number for binary search: ";
    cin >> key;
    int pos = binarySearch(arr, n, key);
    if (pos != -1) cout << "Found at position: " << pos << endl;
    else cout << "Item not found." << endl;

    cout << "\n" << string(60, '-') << endl;
    cout << "DEPENDENCE OF TIME ON THE NUMBER OF ELEMENTS (sec)" << endl;
    cout << string(60, '-') << endl;
    cout << setw(10) << "n" << setw(15) << "Bubble" << setw(15) << "Insertion" << setw(15) << "Shell" << endl;

    int sizes[] = { 10, 100, 1000, 8000, 50000, 150000 };
    for (int size : sizes) {
        int* a = new int[size], * b = new int[size], * c = new int[size];
        for (int i = 0; i < size; i++) a[i] = b[i] = c[i] = rand() % 1000;

        auto s = high_resolution_clock::now();
        if (size <= 50000) bubbleSort(a, size); 
        double t1 = duration<double>(high_resolution_clock::now() - s).count();

        s = high_resolution_clock::now();
        insertionSort(b, size);
        double t2 = duration<double>(high_resolution_clock::now() - s).count();

        s = high_resolution_clock::now();
        shellSort(c, size);
        double t3 = duration<double>(high_resolution_clock::now() - s).count();

        cout << setw(10) << size << setw(15) << (size > 50000 ? "Skip" : to_string(t1))
            << setw(15) << t2 << setw(15) << t3 << endl;

        delete[] a; delete[] b; delete[] c;
    }

    // --- Порівняння Sync/Async ---
    cout << "\n" << string(60, '-') << endl;
    cout << "COMPARISON OF SYNCHRONOUS AND ASYNCHRONOUS CODE (n=50000)" << endl;
    cout << string(60, '-') << endl;
    cout << left << setw(15) << "Method" << setw(15) << "Sync (s)" << setw(15) << "Async (s)" << endl;

    comparePerformance(insertionSort, "Insertion", 50000);
    comparePerformance(shellSort, "Shell", 50000);

    delete[] arr;
    return 0;
}