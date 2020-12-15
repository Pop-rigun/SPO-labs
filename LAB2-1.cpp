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
		cout << "ФИО автора: ";
		wcout << wstring(now.author);
		cout << "Название книги: ";
		wcout << wstring(now.name);
		cout << ", Кол-во страниц: " << now.pages << ", Год написания: " << now.year<< endl;
	}
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "russian");

	// Имя файла с данными
	LPCTSTR fn = L"D:\\Лабы на плюсахахах\\CПО 5 сем\\SPO_lab1\\SPO_lab1\\input.dat";

	// Дискриптор файла с данными
	HANDLE NewFile = CreateFile(fn, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// Количество книг в файле
	DWORD count = GetFileSize(NewFile, NULL) / sizeof(Book);

	// Структура, которая устанавливает оконный режим терминала, рабочий стол, стандартные дескрипторы и внешний вид главного окна для нового процесса.
	STARTUPINFO start_main;
	ZeroMemory(&start_main, sizeof(start_main));
	start_main.cb = sizeof(start_main);

	// Структура, в которую помещаются возвращаемые функцией значения дескрипторов и глобальных идентификаторов процесса.
	PROCESS_INFORMATION main_proc;
	ZeroMemory(&main_proc, sizeof(main_proc));

	// Вывод данных из файла
	show_info(get_info(NewFile));
	CloseHandle(NewFile);

	char ch;
	do {
		
		unsigned int n;
		do {
			cout << "Введите номер книги (от 0 до " << count - 1 << "): ";
			cin >> n;
		} while (n < 0 && n >= count);

		// Составление имени процесса и параметры для cmd
		wchar_t AppName[200], tmp[5];
		wcscpy(AppName, L"D:\\Лабы на плюсахахах\\CПО 5 сем\\dghtproc\\Debug\\dghtproc.exe ");
		swprintf_s(tmp, L"%d", n);
		wcscat(AppName, tmp);
		wcout << wstring(AppName) << endl;

		// Создание процесса
		if (!CreateProcess(NULL, AppName, NULL, NULL, FALSE, 0,
			NULL, NULL, &start_main, &main_proc)) return 0;

		// Дожидаемся выполнения процесса
		WaitForSingleObject(main_proc.hProcess, INFINITE);
		cout << "Хотите продолжить вносить изменения? (Y/N)";
		cin >> ch;
		CloseHandle(main_proc.hProcess);
		CloseHandle(main_proc.hThread);
	} while (ch == 'Y' || ch == 'y');
	return 0;
}