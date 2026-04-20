#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Game {
    string title;
    string genre;
    int year;
    float critic;
    float user;
    float total; 
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;
    while (true) {
        cout << "\n--- ТЕРМІНАЛ ---" << endl;
        cout << "1. Додати нову гру" << endl;
        cout << "2. Переглянути всі ігри" << endl;
        cout << "3. ТОП-3 найкращі гри (за сумою оцінок)" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cout << "Помилка! Введіть цифру." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            Game g;
            cin.ignore(); 

            cout << "Назва: "; getline(cin, g.title);
            cout << "Жанр: "; getline(cin, g.genre);
            cout << "Рік видання: "; cin >> g.year;
            cout << "Оцінка критиків (0-100): "; cin >> g.critic;
            cout << "Оцінка користувачів (0-10): "; cin >> g.user;

            ofstream f("games.txt", ios::app);
            f << g.title << endl << g.genre << endl << g.year << endl << g.critic << endl << g.user << endl;
            f.close();
            cout << "Збережено успішно!" << endl;
        }
        else if (choice == 2) {
            ifstream f("games.txt");
            if (!f.is_open()) {
                cout << "Файл порожній!" << endl;
                continue;
            }
            string t, gen; int r; float c, u;
            cout << "\nСПИСОК ІГОР:" << endl;
            while (getline(f, t)) {
                if (t.empty()) continue;
                getline(f, gen);
                f >> r >> c >> u;
                f.ignore(); 
                cout << "Гра: " << t << " | Рік: " << r << " | Оцінка: " << c << " / " << u << endl;
            }
            f.close();
        }

        else if (choice == 3) {
            ifstream f("games.txt");
            Game list[100]; 
            int n = 0;

            while (n < 100 && getline(f, list[n].title)) {
                if (list[n].title.empty()) continue;
                getline(f, list[n].genre);
                f >> list[n].year >> list[n].critic >> list[n].user;
                f.ignore();

                list[n].total = list[n].critic + (list[n].user * 10);
                n++;
            }
            f.close();

            if (n == 0) {
                cout << "Даних немає!" << endl;
                continue;
            }

            cout << "\n--- ТОП-3 НАЙКРАЩІ ГРИ ЗА СУМОЮ БАЛІВ ---" << endl;

            for (int k = 1; k <= 3; k++) {
                float maxScore = -1;
                int bestIdx = -1;

                for (int i = 0; i < n; i++) {
                    if (list[i].total > maxScore) {
                        maxScore = list[i].total;
                        bestIdx = i;
                    }
                }

                if (bestIdx != -1) {
                    cout << k << ". " << list[bestIdx].title << " (Сума: " << maxScore << ")" << endl;
                    list[bestIdx].total = -1;
                }
            }
        }
    }
    return 0;
}