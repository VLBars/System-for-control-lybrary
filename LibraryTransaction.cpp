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
    std::cout << "ID книги: " << bookId << "\n";
    std::cout << "ID читателя: " << readerId << "\n";
    std::cout << "Дата выдачи: " << issueDate << "\n";
    if (returned) {
        std::cout << "Дата возврата: " << returnDate << "\n";
    }
    else {
        std::cout << "Статус: не возвращена\n";
    }
    std::cout << "------------------------\n";
}