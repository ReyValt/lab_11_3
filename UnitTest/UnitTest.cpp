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
            // ������ ���������� ��� ����� istringstream
            string input_data = "Ivanov 5 4 3\nPetrov 3 4 2\nexit\n";
            stringstream input_stream(input_data);
            cin.rdbuf(input_stream.rdbuf()); // ����������� ����� �� ��� ���������� ����

            string filename = "testfile.txt";

            // ��������� ������� CreateFile
            CreateFile(filename);

            // �������� ����� �����
            ifstream fin(filename);
            Assert::IsTrue(fin.is_open(), L"�� ������� ������� ���� ��� ��������.");

            string line;
            getline(fin, line);
            Assert::AreEqual(string("Ivanov 5 4 3"), line, L"������� ���� ������� ����� �����.");

            getline(fin, line);
            Assert::AreEqual(string("Petrov 3 4 2"), line, L"������� ���� ������� ����� �����.");

            fin.close();
            // ��������� ����� ���� �����
            Assert::IsTrue(remove(filename.c_str()) == 0, L"�� ������� �������� ���� ���� �����.");
        }


        TEST_METHOD(Test_AppendToFile)
        {
            string filename = "testfile.txt";

            // ��������� ��������� �����
            ofstream fout(filename);
            fout << "Student1 5 4 3\n";
            fout.close();

            // ��������� ������
            istringstream input("Student2 3 3 3\n");
            cin.rdbuf(input.rdbuf()); // ϳ���� �����
            AppendToFile(filename);

            // �������� ����� �����
            ifstream fin(filename);
            string content((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
            fin.close();

            Assert::IsTrue(content.find("Student2 3 3 3") != string::npos, L"����� �� ������ �� �����.");

            // ��������� ��������� �����
            remove(filename.c_str());
        }
        TEST_METHOD(Test_ViewFile)
        {
            string filename = "testfile.txt";

            // ��������� ��������� �����
            ofstream fout(filename);
            fout << "Student1 5 4 3\nStudent2 3 3 3\n";
            fout.close();

            // �������� ��������� �����
            Assert::IsTrue(FileExists(filename), L"�������� ���� �� ��������.");

            // ������ ������� ��������� (����������, �� �������� �� ����������� ��������)
            try
            {
                ViewFile(filename);
            }
            catch (...)
            {
                Assert::Fail(L"������� ViewFile ������� �������.");
            }

            // ��������� ��������� �����
            remove(filename.c_str());
        }
	};
}
