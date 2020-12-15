#pragma warning(disable : 4996)

#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Book {
	wchar_t author[200];
	wchar_t name[200]; 
	unsigned int pages;
	unsigned int year; 
};

vector<Book> get_info(HANDLE& info) {
	vector<Book> res;
	DWORD j = 0;
	Book tmp;
	DWORD c = GetFileSize(info, NULL) / sizeof(Book);
	for (DWORD i = 0; i < c; i++) {
		ReadFile(info, &tmp, sizeof(tmp), &j, NULL);
		res.push_back(tmp);
	}
	return res;
}

void show_info(vector<Book> books) {
	for (auto now : books) {
		cout << "��� ������: ";
		wcout << wstring(now.author);
		cout << "�������� �����: ";
		wcout << wstring(now.name);
		cout << ", ���-�� �������: " << now.pages << ", ��� ���������: " << now.year<< endl;
	}
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "russian");

	// ��� ����� � �������
	LPCTSTR fn = L"D:\\���� �� ����������\\C�� 5 ���\\SPO_lab1\\SPO_lab1\\input.dat";

	// ���������� ����� � �������
	HANDLE NewFile = CreateFile(fn, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// ���������� ���� � �����
	DWORD count = GetFileSize(NewFile, NULL) / sizeof(Book);

	// ���������, ������� ������������� ������� ����� ���������, ������� ����, ����������� ����������� � ������� ��� �������� ���� ��� ������ ��������.
	STARTUPINFO start_main;
	ZeroMemory(&start_main, sizeof(start_main));
	start_main.cb = sizeof(start_main);

	// ���������, � ������� ���������� ������������ �������� �������� ������������ � ���������� ��������������� ��������.
	PROCESS_INFORMATION main_proc;
	ZeroMemory(&main_proc, sizeof(main_proc));

	// ����� ������ �� �����
	show_info(get_info(NewFile));
	CloseHandle(NewFile);

	char ch;
	do {
		
		unsigned int n;
		do {
			cout << "������� ����� ����� (�� 0 �� " << count - 1 << "): ";
			cin >> n;
		} while (n < 0 && n >= count);

		// ����������� ����� �������� � ��������� ��� cmd
		wchar_t AppName[200], tmp[5];
		wcscpy(AppName, L"D:\\���� �� ����������\\C�� 5 ���\\dghtproc\\Debug\\dghtproc.exe ");
		swprintf_s(tmp, L"%d", n);
		wcscat(AppName, tmp);
		wcout << wstring(AppName) << endl;

		// �������� ��������
		if (!CreateProcess(NULL, AppName, NULL, NULL, FALSE, 0,
			NULL, NULL, &start_main, &main_proc)) return 0;

		// ���������� ���������� ��������
		WaitForSingleObject(main_proc.hProcess, INFINITE);
		cout << "������ ���������� ������� ���������? (Y/N)";
		cin >> ch;
		CloseHandle(main_proc.hProcess);
		CloseHandle(main_proc.hThread);
	} while (ch == 'Y' || ch == 'y');
	return 0;
}