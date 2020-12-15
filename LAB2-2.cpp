#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Book {
	wchar_t author[200];
	wchar_t name[100]; // ФИО студента
	unsigned int pages; // Средний балл
	unsigned int year; // Доход на члена семьи
};

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "russian");
	cout << "Count of parametrs: " << argc << endl;
	stringstream convert(argv[1]); // создаем переменную stringstream с именем convert, инициализируя её значением argv[1]

	int n;
	if (!(convert >> n)) // выполняем конвертацию
		n = 0; // если конвертация терпит неудачу, то присваиваем myint значение по умолчанию

	cout << "Got integer: " << n << '\n';

	// Имя файла с данными
	LPCTSTR fn = "D:\\Лабы на плюсахахах\\CПО 5 сем\\SPO_lab1\\SPO_lab1\\input.dat";

	// Дискриптор файла с данными
	HANDLE NewFile = CreateFile(fn, GENERIC_READ |
		GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// Количество rкниг в файле
	DWORD count = GetFileSize(NewFile, NULL) / sizeof(Book);

	// Получение данных из файла
	Book tmp;
	vector<Book> books;
	DWORD j = 0;

	for (DWORD i = 0; i < count; i++) {
		ReadFile(NewFile, &tmp, sizeof(tmp), &j, NULL);
		books.push_back(tmp);
	}

	cout << "ФИО Автора: ";
	wcout << wstring(books[n].author);
	cout << "Название книги: ";
	wcout<< wstring(books[n].name);
	cout << ", Кол-во страниц: " << books[n].pages << ", Год написания: " << books[n].year << endl;

	cout << "Изменение данных" << endl;
	cout << "Введите ФИО автора: ";
	wcin.getline(books[n].author, 200);
	cout << "Введите название книги: ";
	wcin.getline(books[n].name, 200);
	cout << "Введите кол-во страниц: ";
	cin >> books[n].pages;
	cout << "Введите год написания: ";
	cin >> books[n].year;

	cout << "После изменений" << endl;
	cout << "ФИО автора: ";
	wcout << wstring(books[n].author);
	cout << "Название книги:";
	wcout << wstring(books[n].author);
	cout << ", Кол-во страниц: " << books[n].pages << ", Год написания: " << books[n].year << endl;

	// Запись в файл
	SetFilePointer(NewFile, 0, 0, FILE_BEGIN);
	for (auto now : books) {
		WriteFile(NewFile, &now, sizeof(now), &j, NULL);
	}
	FlushFileBuffers(NewFile);
	CloseHandle(NewFile);
	return 0;
}