#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "Reader.h"
#include "LibraryTransaction.h"

class LibraryManager {
private:
    std::vector<Book> books;
    std::vector<Reader> readers;
    std::vector<LibraryTransaction> transactions;
    int nextBookId;
    int nextReaderId;

    void saveData();
    void loadData();

    std::string getCurrentDate() const;

public:
    LibraryManager();

    // ������ ��� ������ � �������
    void addBook();
    void displayAllBooks() const;
    void searchBooks() const;
    Book* findBookById(int id);

    // ������ ��� ������ � ����������
    void addReader();
    void displayAllReaders() const;
    Reader* findReaderById(int id);

    // ������ ��� ������ � ������������
    void issueBook();
    void returnBook();
    void displayAllTransactions() const;

    // �������� ����
    void run();
};