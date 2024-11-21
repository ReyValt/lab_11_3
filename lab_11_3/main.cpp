#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;


void CreateFile(const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Помилка: не вдалося створити файл.\n";
        return;
    }
    cout << "Введіть дані студентів у форматі (Прізвище Оцінка1 Оцінка2 Оцінка3).\n"
        << "Для завершення введення введіть 'exit':\n";
    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);
        if (input == "exit") break;

        istringstream iss(input);
        string lastname;
        int grade1, grade2, grade3;

        if (iss >> lastname >> grade1 >> grade2 >> grade3 &&
            grade1 >= 0 && grade1 <= 5 &&
            grade2 >= 0 && grade2 <= 5 &&
            grade3 >= 0 && grade3 <= 5) {
            fout << lastname << " " << grade1 << " " << grade2 << " " << grade3 << endl;
        }
        else {
            cout << "Невірний формат введення. Спробуйте ще раз.\n";
        }
    }
    fout.close();
}


void ViewFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Помилка: не вдалося відкрити файл.\n";
        return;
    }
    cout << "\nСписок студентів:\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

void AppendToFile(const string& filename) {
    ofstream fout(filename, ios::app);
    if (!fout) {
        cerr << "Помилка: не вдалося відкрити файл.\n";
        return;
    }
    cout << "Введіть дані студента у форматі (Прізвище Оцінка1 Оцінка2 Оцінка3):\n";
    string lastname;
    int grade1, grade2, grade3;

    cin >> lastname >> grade1 >> grade2 >> grade3;
    if (grade1 >= 0 && grade1 <= 5 &&
        grade2 >= 0 && grade2 <= 5 &&
        grade3 >= 0 && grade3 <= 5) {
        fout << lastname << " " << grade1 << " " << grade2 << " " << grade3 << endl;
        cout << "Запис додано успішно.\n";
    }
    else {
        cout << "Помилка: оцінки мають бути в діапазоні від 0 до 5.\n";
    }
    fout.close();
}


bool FileExists(const string& filename) {
    ifstream fin(filename);
    return fin.good();
}


void Menu(const string& filename) {
    int choice;
    do {
        cout << "\nМеню:\n"
            << "1. Створити новий список\n"
            << "2. Переглянути список\n"
            << "3. Додати студента до списку\n"
            << "4. Вийти\n"
            << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            CreateFile(filename);
            break;
        case 2:
            if (FileExists(filename)) {
                ViewFile(filename);
            }
            else {
                cout << "Файл не існує. Спочатку створіть список.\n";
            }
            break;
        case 3:
            if (FileExists(filename)) {
                AppendToFile(filename);
            }
            else {
                cout << "Файл не існує. Спочатку створіть список.\n";
            }
            break;
        case 4:
            cout << "Завершення роботи програми.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (choice != 4);
}

int main() {

    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ukr");
    string filename;
    cout << "Введіть ім'я файлу для роботи: ";
    cin >> filename;
    cin.ignore();
    Menu(filename);
    return 0;
}
