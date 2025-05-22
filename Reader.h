#pragma once
#include <string>
#include <vector>

class Reader {
private:
    std::string name;
    std::string contact;
    int id;
    std::vector<int> borrowedBooks;

public:
    Reader(std::string name, std::string contact, int id);

    // �������
    std::string getName() const;
    std::string getContact() const;
    int getId() const;
    const std::vector<int>& getBorrowedBooks() const;

    // ������ ��� ������ � �������
    void borrowBook(int bookId);
    void returnBook(int bookId);

    void displayInfo() const;
};