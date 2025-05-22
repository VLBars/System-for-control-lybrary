#include "LibraryTransaction.h"
#include <iostream>

LibraryTransaction::LibraryTransaction(int bookId, int readerId, std::string issueDate)
    : bookId(bookId), readerId(readerId), issueDate(issueDate), returned(false), returnDate("") {
}

int LibraryTransaction::getBookId() const { return bookId; }
int LibraryTransaction::getReaderId() const { return readerId; }
std::string LibraryTransaction::getIssueDate() const { return issueDate; }
std::string LibraryTransaction::getReturnDate() const { return returnDate; }
bool LibraryTransaction::isReturned() const { return returned; }

void LibraryTransaction::setReturned(std::string returnDate) {
    returned = true;
    this->returnDate = returnDate;
}

void LibraryTransaction::displayInfo() const {
    std::cout << "ID �����: " << bookId << "\n";
    std::cout << "ID ��������: " << readerId << "\n";
    std::cout << "���� ������: " << issueDate << "\n";
    if (returned) {
        std::cout << "���� ��������: " << returnDate << "\n";
    }
    else {
        std::cout << "������: �� ����������\n";
    }
    std::cout << "------------------------\n";
}