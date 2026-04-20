#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    ifstream file("text.txt");

    string sentences[100]; 
    int count = 0;
    string line;


    while (getline(file, line)) {
        sentences[count] = line;
        count++;
    }
    file.close();

    bool foundMatch = false;
    bool isDuplicate[100] = { false }; 

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i == j) continue;

            int common = 0;
            stringstream ssI(sentences[i]);
            string wordI;

           
            while (ssI >> wordI) {
                if (ispunct(wordI.back())) wordI.pop_back();

                stringstream ssJ(sentences[j]);
                string wordJ;
                while (ssJ >> wordJ) {
                    if (ispunct(wordJ.back())) wordJ.pop_back();

                    if (wordI == wordJ) {
                        common++;
                        break;
                    }
                }
            }

            if (common >= 3) {
                isDuplicate[i] = true;
                foundMatch = true;
            }
        }
    }

    ofstream out("output.txt");
    if (foundMatch) {
        for (int i = 0; i < count; i++) {
            if (isDuplicate[i]) {
                out << sentences[i] << endl;
            }
        }
    }
    else {
        out << sentences[0] << endl;
    }
    out.close();

    cout << "Gotovo! Perevir output.txt" << endl;

    return 0;
}