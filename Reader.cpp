#include "Reader.h"
#include <algorithm>
#include <iostream> 

Reader::Reader(std::string name, std::string contact, int id)
    : name(name), contact(contact), id(id) {
}

std::string Reader::getName() const { return name; }
std::string Reader::getContact() const { return contact; }
int Reader::getId() const { return id; }
const std::vector<int>& Reader::getBorrowedBooks() const { return borrowedBooks; }

void Reader::borrowBook(int bookId) {
    borrowedBooks.push_back(bookId);
}

void Reader::returnBook(int bookId) {
    borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), bookId), borrowedBooks.end());
}

void Reader::displayInfo() const {
    std::cout << "ID ��������: " << id << "\n";
    std::cout << "���: " << name << "\n";
    std::cout << "�������: " << contact << "\n";
    std::cout << "���������� ������ ����: " << borrowedBooks.size() << "\n";
    std::cout << "------------------------\n";
}