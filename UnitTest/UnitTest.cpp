#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_11_3/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
        TEST_METHOD(Test_CreateFile)
        {
            // Імітуємо консольний ввід через istringstream
            string input_data = "Ivanov 5 4 3\nPetrov 3 4 2\nexit\n";
            stringstream input_stream(input_data);
            cin.rdbuf(input_stream.rdbuf()); // Перемикання вводу на наш фіксований потік

            string filename = "testfile.txt";

            // Викликаємо функцію CreateFile
            CreateFile(filename);

            // Перевірка вмісту файлу
            ifstream fin(filename);
            Assert::IsTrue(fin.is_open(), L"Не вдалося відкрити файл для перевірки.");

            string line;
            getline(fin, line);
            Assert::AreEqual(string("Ivanov 5 4 3"), line, L"Невірний вміст першого рядка файлу.");

            getline(fin, line);
            Assert::AreEqual(string("Petrov 3 4 2"), line, L"Невірний вміст другого рядка файлу.");

            fin.close();
            // Видалення файлу після тесту
            Assert::IsTrue(remove(filename.c_str()) == 0, L"Не вдалося видалити файл після тесту.");
        }


        TEST_METHOD(Test_AppendToFile)
        {
            string filename = "testfile.txt";

            // Створення тестового файлу
            ofstream fout(filename);
            fout << "Student1 5 4 3\n";
            fout.close();

            // Додавання запису
            istringstream input("Student2 3 3 3\n");
            cin.rdbuf(input.rdbuf()); // Підміна вводу
            AppendToFile(filename);

            // Перевірка вмісту файлу
            ifstream fin(filename);
            string content((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
            fin.close();

            Assert::IsTrue(content.find("Student2 3 3 3") != string::npos, L"Запис не додано до файлу.");

            // Видалення тестового файлу
            remove(filename.c_str());
        }
        TEST_METHOD(Test_ViewFile)
        {
            string filename = "testfile.txt";

            // Створення тестового файлу
            ofstream fout(filename);
            fout << "Student1 5 4 3\nStudent2 3 3 3\n";
            fout.close();

            // Перевірка існування файлу
            Assert::IsTrue(FileExists(filename), L"Тестовий файл не створено.");

            // Виклик функції перегляду (перевіряємо, що програма не завершується помилкою)
            try
            {
                ViewFile(filename);
            }
            catch (...)
            {
                Assert::Fail(L"Функція ViewFile викликає помилку.");
            }

            // Видалення тестового файлу
            remove(filename.c_str());
        }
	};
}
