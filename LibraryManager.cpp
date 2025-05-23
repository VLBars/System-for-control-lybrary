#define _CRT_SECURE_NO_WARNINGS
#include "LibraryManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <clocale>

LibraryManager::LibraryManager() : nextBookId(1), nextReaderId(1) {
    loadData();
}

std::string LibraryManager::getCurrentDate() const {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y");
    return oss.str();
}

void LibraryManager::saveData() {
    std::ofstream booksFile("books.txt");
    for (const auto& book : books) {
        booksFile << book.getId() << "|" << book.getTitle() << "|"
            << book.getAuthor() << "|" << book.getGenre() << "|"
            << book.getYear() << "|" << book.isAvailable() << "\n";
    }
    booksFile.close();

    std::ofstream readersFile("readers.txt");
    for (const auto& reader : readers) {
        readersFile << reader.getId() << "|" << reader.getName() << "|"
            << reader.getContact() << "|";
        for (int bookId : reader.getBorrowedBooks()) {
            readersFile << bookId << ",";
        }
        readersFile << "\n";
    }
    readersFile.close();

    std::ofstream transactionsFile("transactions.txt");
    for (const auto& transaction : transactions) {
        transactionsFile << transaction.getBookId() << "|" << transaction.getReaderId() << "|"
            << transaction.getIssueDate() << "|" << transaction.getReturnDate() << "|"
            << transaction.isReturned() << "\n";
    }
    transactionsFile.close();
}

void LibraryManager::loadData() {
    // Загрузка книг
    std::ifstream booksFile("books.txt");
    if (booksFile) {
        std::string line;
        while (std::getline(booksFile, line)) {
            size_t pos = 0;
            std::vector<std::string> tokens;
            while ((pos = line.find('|')) != std::string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 6) {
                int id = std::stoi(tokens[0]);
                Book book(tokens[1], tokens[2], tokens[3], std::stoi(tokens[4]), id);
                book.setAvailable(tokens[5] == "1");
                books.push_back(book);
                if (id >= nextBookId) nextBookId = id + 1;
            }
        }
        booksFile.close();
    }

    // Загрузка читателей
    std::ifstream readersFile("readers.txt");
    if (readersFile) {
        std::string line;
        while (std::getline(readersFile, line)) {
            size_t pos = 0;
            std::vector<std::string> tokens;
            while ((pos = line.find('|')) != std::string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }

            if (tokens.size() >= 3) {
                int id = std::stoi(tokens[0]);
                Reader reader(tokens[1], tokens[2], id);

                if (!line.empty()) {
                    std::istringstream iss(line);
                    std::string bookIdStr;
                    while (std::getline(iss, bookIdStr, ',')) {
                        if (!bookIdStr.empty()) {
                            reader.borrowBook(std::stoi(bookIdStr));
                        }
                    }
                }

                readers.push_back(reader);
                if (id >= nextReaderId) nextReaderId = id + 1;
            }
        }
        readersFile.close();
    }

    // Загрузка транзакций
    std::ifstream transactionsFile("transactions.txt");
    if (transactionsFile) {
        std::string line;
        while (std::getline(transactionsFile, line)) {
            size_t pos = 0;
            std::vector<std::string> tokens;
            while ((pos = line.find('|')) != std::string::npos) {
                tokens.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            tokens.push_back(line);

            if (tokens.size() == 5) {
                LibraryTransaction transaction(std::stoi(tokens[0]), std::stoi(tokens[1]), tokens[2]);
                if (tokens[4] == "1") {
                    transaction.setReturned(tokens[3]);
                }
                transactions.push_back(transaction);
            }
        }
        transactionsFile.close();
    }
}

void LibraryManager::addBook() {
    std::cin.ignore();
    std::string title, author, genre;
    int year;

    std::cout << "Добавление новой книги\n";
    std::cout << "Введите название: ";
    std::getline(std::cin, title);
    std::cout << "Введите автора: ";
    std::getline(std::cin, author);
    std::cout << "Введите жанр: ";
    std::getline(std::cin, genre);
    std::cout << "Введите год издания: ";
    std::cin >> year;

    books.emplace_back(title, author, genre, year, nextBookId++);
    saveData();
    std::cout << "Книга успешно добавлена!\n";
}

void LibraryManager::displayAllBooks() const {
    if (books.empty()) {
        std::cout << "В библиотеке нет книг.\n";
        return;
    }

    std::cout << "Список всех книг:\n";
    for (const auto& book : books) {
        book.displayInfo();
    }
}

void LibraryManager::searchBooks() const {
    std::cin.ignore();
    std::cout << "Поиск книг по:\n";
    std::cout << "1. Названию\n";
    std::cout << "2. Автору\n";
    std::cout << "3. Жанру\n";
    std::cout << "Выберите вариант: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    std::string searchTerm;
    std::cout << "Введите поисковый запрос: ";
    std::getline(std::cin, searchTerm);

    bool found = false;
    for (const auto& book : books) {
        bool match = false;
        switch (choice) {
        case 1: match = book.getTitle().find(searchTerm) != std::string::npos; break;
        case 2: match = book.getAuthor().find(searchTerm) != std::string::npos; break;
        case 3: match = book.getGenre().find(searchTerm) != std::string::npos; break;
        default: std::cout << "Неверный выбор.\n"; return;
        }

        if (match) {
            book.displayInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "Книги по вашему запросу не найдены.\n";
    }
}

Book* LibraryManager::findBookById(int id) {
    for (auto& book : books) {
        if (book.getId() == id) {
            return &book;
        }
    }
    return nullptr;
}

void LibraryManager::addReader() {
    std::cin.ignore();
    std::string name, contact;

    std::cout << "Добавление нового читателя\n";
    std::cout << "Введите имя: ";
    std::getline(std::cin, name);
    std::cout << "Введите контактную информацию: ";
    std::getline(std::cin, contact);

    readers.emplace_back(name, contact, nextReaderId++);
    saveData();
    std::cout << "Читатель успешно добавлен!\n";
}

void LibraryManager::displayAllReaders() const {
    if (readers.empty()) {
        std::cout << "В библиотеке нет зарегистрированных читателей.\n";
        return;
    }

    std::cout << "Список всех читателей:\n";
    for (const auto& reader : readers) {
        reader.displayInfo();
    }
}

Reader* LibraryManager::findReaderById(int id) {
    for (auto& reader : readers) {
        if (reader.getId() == id) {
            return &reader;
        }
    }
    return nullptr;
}

void LibraryManager::issueBook() {
    if (books.empty()) {
        std::cout << "В библиотеке нет книг для выдачи.\n";
        return;
    }

    if (readers.empty()) {
        std::cout << "В библиотеке нет зарегистрированных читателей.\n";
        return;
    }

    displayAllBooks();
    std::cout << "Введите ID книги для выдачи: ";
    int bookId;
    std::cin >> bookId;

    Book* book = findBookById(bookId);
    if (!book) {
        std::cout << "Книга с таким ID не найдена.\n";
        return;
    }

    if (!book->isAvailable()) {
        std::cout << "Эта книга уже выдана.\n";
        return;
    }

    displayAllReaders();
    std::cout << "Введите ID читателя: ";
    int readerId;
    std::cin >> readerId;

    Reader* reader = findReaderById(readerId);
    if (!reader) {
        std::cout << "Читатель с таким ID не найден.\n";
        return;
    }

    book->setAvailable(false);
    reader->borrowBook(bookId);
    transactions.emplace_back(bookId, readerId, getCurrentDate());
    saveData();
    std::cout << "Книга успешно выдана!\n";
}

void LibraryManager::returnBook() {
    if (transactions.empty()) {
        std::cout << "Нет активных выдач книг.\n";
        return;
    }

    displayAllReaders();
    std::cout << "Введите ID читателя: ";
    int readerId;
    std::cin >> readerId;

    Reader* reader = findReaderById(readerId);
    if (!reader) {
        std::cout << "Читатель с таким ID не найден.\n";
        return;
    }

    const auto& borrowedBooks = reader->getBorrowedBooks();
    if (borrowedBooks.empty()) {
        std::cout << "У этого читателя нет взятых книг.\n";
        return;
    }

    std::cout << "Список взятых книг:\n";
    for (int bookId : borrowedBooks) {
        Book* book = findBookById(bookId);
        if (book) {
            book->displayInfo();
        }
    }

    std::cout << "Введите ID книги для возврата: ";
    int bookId;
    std::cin >> bookId;

    if (std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) == borrowedBooks.end()) {
        std::cout << "Этот читатель не брал книгу с таким ID.\n";
        return;
    }

    Book* book = findBookById(bookId);
    if (book) {
        book->setAvailable(true);
    }

    reader->returnBook(bookId);

    for (auto& transaction : transactions) {
        if (transaction.getBookId() == bookId && transaction.getReaderId() == readerId && !transaction.isReturned()) {
            transaction.setReturned(getCurrentDate());
            break;
        }
    }

    saveData();
    std::cout << "Книга успешно возвращена!\n";
}

void LibraryManager::displayAllTransactions() const {
    if (transactions.empty()) {
        std::cout << "Нет данных о выдачах книг.\n";
        return;
    }

    std::cout << "История выдачи книг:\n";
    for (const auto& transaction : transactions) {
        transaction.displayInfo();
    }
}

void LibraryManager::run() {
    while (true) {
        std::cout << "\nСистема управления библиотекой\n";
        std::cout << "1. Добавить книгу\n";
        std::cout << "2. Показать все книги\n";
        std::cout << "3. Поиск книг\n";
        std::cout << "4. Добавить читателя\n";
        std::cout << "5. Показать всех читателей\n";
        std::cout << "6. Выдать книгу\n";
        std::cout << "7. Вернуть книгу\n";
        std::cout << "8. Показать историю выдачи\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: displayAllBooks(); break;
        case 3: searchBooks(); break;
        case 4: addReader(); break;
        case 5: displayAllReaders(); break;
        case 6: issueBook(); break;
        case 7: returnBook(); break;
        case 8: displayAllTransactions(); break;
        case 0:
            saveData();
            std::cout << "Данные сохранены. Выход из программы.\n";
            return;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}