#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;


void CreateFile(const string& filename) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "�������: �� ������� �������� ����.\n";
        return;
    }
    cout << "������ ��� �������� � ������ (������� ������1 ������2 ������3).\n"
        << "��� ���������� �������� ������ 'exit':\n";
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
            cout << "������� ������ ��������. ��������� �� ���.\n";
        }
    }
    fout.close();
}


void ViewFile(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "�������: �� ������� ������� ����.\n";
        return;
    }
    cout << "\n������ ��������:\n";
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

void AppendToFile(const string& filename) {
    ofstream fout(filename, ios::app);
    if (!fout) {
        cerr << "�������: �� ������� ������� ����.\n";
        return;
    }
    cout << "������ ��� �������� � ������ (������� ������1 ������2 ������3):\n";
    string lastname;
    int grade1, grade2, grade3;

    cin >> lastname >> grade1 >> grade2 >> grade3;
    if (grade1 >= 0 && grade1 <= 5 &&
        grade2 >= 0 && grade2 <= 5 &&
        grade3 >= 0 && grade3 <= 5) {
        fout << lastname << " " << grade1 << " " << grade2 << " " << grade3 << endl;
        cout << "����� ������ ������.\n";
    }
    else {
        cout << "�������: ������ ����� ���� � ������� �� 0 �� 5.\n";
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
        cout << "\n����:\n"
            << "1. �������� ����� ������\n"
            << "2. ����������� ������\n"
            << "3. ������ �������� �� ������\n"
            << "4. �����\n"
            << "��� ����: ";
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
                cout << "���� �� ����. �������� ������� ������.\n";
            }
            break;
        case 3:
            if (FileExists(filename)) {
                AppendToFile(filename);
            }
            else {
                cout << "���� �� ����. �������� ������� ������.\n";
            }
            break;
        case 4:
            cout << "���������� ������ ��������.\n";
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }
    } while (choice != 4);
}

int main() {

    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ukr");
    string filename;
    cout << "������ ��'� ����� ��� ������: ";
    cin >> filename;
    cin.ignore();
    Menu(filename);
    return 0;
}
