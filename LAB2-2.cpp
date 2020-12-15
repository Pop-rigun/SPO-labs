#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Book {
	wchar_t author[200];
	wchar_t name[100]; // ��� ��������
	unsigned int pages; // ������� ����
	unsigned int year; // ����� �� ����� �����
};

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "russian");
	cout << "Count of parametrs: " << argc << endl;
	stringstream convert(argv[1]); // ������� ���������� stringstream � ������ convert, ������������� � ��������� argv[1]

	int n;
	if (!(convert >> n)) // ��������� �����������
		n = 0; // ���� ����������� ������ �������, �� ����������� myint �������� �� ���������

	cout << "Got integer: " << n << '\n';

	// ��� ����� � �������
	LPCTSTR fn = "D:\\���� �� ����������\\C�� 5 ���\\SPO_lab1\\SPO_lab1\\input.dat";

	// ���������� ����� � �������
	HANDLE NewFile = CreateFile(fn, GENERIC_READ |
		GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// ���������� r���� � �����
	DWORD count = GetFileSize(NewFile, NULL) / sizeof(Book);

	// ��������� ������ �� �����
	Book tmp;
	vector<Book> books;
	DWORD j = 0;

	for (DWORD i = 0; i < count; i++) {
		ReadFile(NewFile, &tmp, sizeof(tmp), &j, NULL);
		books.push_back(tmp);
	}

	cout << "��� ������: ";
	wcout << wstring(books[n].author);
	cout << "�������� �����: ";
	wcout<< wstring(books[n].name);
	cout << ", ���-�� �������: " << books[n].pages << ", ��� ���������: " << books[n].year << endl;

	cout << "��������� ������" << endl;
	cout << "������� ��� ������: ";
	wcin.getline(books[n].author, 200);
	cout << "������� �������� �����: ";
	wcin.getline(books[n].name, 200);
	cout << "������� ���-�� �������: ";
	cin >> books[n].pages;
	cout << "������� ��� ���������: ";
	cin >> books[n].year;

	cout << "����� ���������" << endl;
	cout << "��� ������: ";
	wcout << wstring(books[n].author);
	cout << "�������� �����:";
	wcout << wstring(books[n].author);
	cout << ", ���-�� �������: " << books[n].pages << ", ��� ���������: " << books[n].year << endl;

	// ������ � ����
	SetFilePointer(NewFile, 0, 0, FILE_BEGIN);
	for (auto now : books) {
		WriteFile(NewFile, &now, sizeof(now), &j, NULL);
	}
	FlushFileBuffers(NewFile);
	CloseHandle(NewFile);
	return 0;
}