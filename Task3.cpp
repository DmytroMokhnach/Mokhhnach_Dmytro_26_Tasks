#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

void fillMatrix(int** a, int n, int v) {
    int min = -10 - v;
    int max = 10 + v;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void printMatrix(int** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }
}

void sector1(int** a, int n) {
    int sum = 0;

    cout << "\nSector 1\\:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i <= j && i + j <= n - 1) {
                cout << a[i][j] << " ";

                if (a[i][j] % 2 != 0) {
                    sum += a[i][j];
                }
            }
        }
    }

    cout << "\nSum of odd number: " << sum << endl;
}

void sector9(int** a, int n) {
    int maxAbs = abs(a[0][0]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(a[i][j]) > maxAbs) {
                maxAbs = abs(a[i][j]);
            }
        }
    }

    int count = 0;

    cout << "\nSector *9:\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i >= n / 2) {
                cout << a[i][j] << " ";
                a[i][j] = maxAbs;
                count++;
            }
        }
    }

    cout << "\nNumber: " << count << endl;
    cout << "MAX: " << maxAbs << endl;
}

int main() {
    srand(time(0));

    int n;
    int v = 26;

    cout << "Enter n: ";
    cin >> n;

    int** a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }

    fillMatrix(a, n, v);

    cout << "\nMatrix:\n";
    printMatrix(a, n);

    sector1(a, n);
    sector9(a, n);

    cout << "\nAfter changes:\n";
    printMatrix(a, n);

    return 0;
}