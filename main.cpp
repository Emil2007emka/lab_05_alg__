#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

// Класс "Книга" по заданию
class Book {
private:
    string author;      // ФИО автора
    string title;       // Название
    string publisher;   // Издательство
    int year;           // Год издания
    int pages;          // Число страниц

public:
    // Обычный конструктор
    Book(string a = "", string t = "", string p = "", int y = 0, int pg = 0)
        : author(a), title(t), publisher(p), year(y), pages(pg) {}

    // Конструктор копирования
    Book(const Book& other) {
        author = other.author;
        title = other.title;
        publisher = other.publisher;
        year = other.year;
        pages = other.pages;
    }

    // Оператор присваивания (копированием)
    Book& operator=(const Book& other) {
        if (this != &other) {
            author = other.author;
            title = other.title;
            publisher = other.publisher;
            year = other.year;
            pages = other.pages;
        }
        return *this;
    }

    // Конструктор перемещения и оператор присваивания перемещением
    Book(Book&& other) noexcept
        : author(move(other.author)), title(move(other.title)),
          publisher(move(other.publisher)), year(other.year), pages(other.pages) {}

    Book& operator=(Book&& other) noexcept {
        if (this != &other) {
            author = move(other.author);
            title = move(other.title);
            publisher = move(other.publisher);
            year = other.year;
            pages = other.pages;
        }
        return *this;
    }

    // Перегрузка оператора < для сортировки по ФИО автора
    bool operator<(const Book& other) const {
        return author < other.author;
    }

    string getAuthor() const { return author; }

    // Перегрузка вывода в поток
    friend ostream& operator<<(ostream& os, const Book& b) {
        os << b.author << "|" << b.title << "|" << b.publisher
           << "|" << b.year << "|" << b.pages;
        return os;
    }
};

int main() {
    // 1. Создаем исходный контейнер deque
    deque<Book> sourceDeque;

    // 2. Читаем данные из input.txt
    ifstream inFile("input.txt");
    if (!inFile) {
        cerr << "Ошибка: файл input.txt не найден!" << endl;
        return 1;
    }

    string a, t, p;
    int y, pg;
    // Считываем данные
    while (inFile >> ws && getline(inFile, a) && getline(inFile, t) && getline(inFile, p) && inFile >> y >> pg) {
        sourceDeque.emplace_back(a, t, p, y, pg);
    }
    inFile.close();

    // 3. Вывод исходного контейнера в output.txt
    ofstream outFile("output.txt");
    outFile << "--- Исходный контейнер (deque) ---" << endl;
    for (const auto& b : sourceDeque) {
        outFile << b << endl;
    }

    // 4. Сортировка исходного контейнера по ФИО автора
    // Для deque используем алгоритм std::sort
    sort(sourceDeque.begin(), sourceDeque.end());

    outFile << "\n--- После сортировки по ФИО ---" << endl;
    for (const auto& b : sourceDeque) {
        outFile << b << endl;
    }

    // 5. Копирование в list с помощью std::copy
    list<Book> targetList;
    // Используем back_inserter, чтобы динамически наполнять список при копировании
    copy(sourceDeque.begin(), sourceDeque.end(), back_inserter(targetList));

    // 6. Вывод скопированного контейнера
    outFile << "\n--- Скопированный контейнер (list) ---" << endl;
    for (const auto& b : targetList) {
        outFile << b << endl;
    }

    outFile.close();
    cout << "Работа завершена. Проверьте output.txt" << endl;

    return 0;
}