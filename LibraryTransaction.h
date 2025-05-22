#pragma once
#include <string>
#include <ctime>

class LibraryTransaction {
private:
    int bookId;
    int readerId;
    std::string issueDate;
    std::string returnDate;
    bool returned;

public:
    LibraryTransaction(int bookId, int readerId, std::string issueDate);

    // �������
    int getBookId() const;
    int getReaderId() const;
    std::string getIssueDate() const;
    std::string getReturnDate() const;
    bool isReturned() const;

    // �������
    void setReturned(std::string returnDate);

    void displayInfo() const;
};