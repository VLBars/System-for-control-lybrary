#pragma once
#include <string>
#include <iostream>

class Book {
private:
    std::string title;
    std::string author;
    std::string genre;
    int year;
    int id;
    bool available;

public:
    Book(std::string title, std::string author, std::string genre, int year, int id);

    // Геттеры
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    int getYear() const;
    int getId() const;
    bool isAvailable() const;

    // Сеттеры
    void setAvailable(bool status);

    void displayInfo() const;
};