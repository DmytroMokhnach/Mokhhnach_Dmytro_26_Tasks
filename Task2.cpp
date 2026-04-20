#include <iostream>
#include <vector>
using namespace std;

double average(vector<double> y, vector<double> x) {
    double sumYX = 0;
    double sumY = 0;

    for (int i = 0; i < y.size(); i++) {
        sumYX += y[i] * x[i];
        sumY += y[i];
    }

    return sumYX / sumY;
}

int main() {
    vector<double> Y = { 4, 1, 8, 5, 6, 3, 7, 5, 4 };
    vector<double> T = { 70, 60, 80, 65, 50, 45, 85, 44, 68 };
    vector<double> P = { 0, 12, 15, 11, 14, 10, 13, 16, 19 };

    double Pkp = average(Y, P);
    double Tkp = average(Y, T);

    cout << "Pkp: " << Pkp << endl;
    cout << "Tkp: " << Tkp << endl;

    return 0;
}