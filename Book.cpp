#include "Book.h"
#include <iostream> 

Book::Book(std::string title, std::string author, std::string genre, int year, int id)
    : title(title), author(author), genre(genre), year(year), id(id), available(true) {
}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getGenre() const { return genre; }
int Book::getYear() const { return year; }
int Book::getId() const { return id; }
bool Book::isAvailable() const { return available; }

void Book::setAvailable(bool status) { available = status; }

void Book::displayInfo() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Название: " << title << "\n";
    std::cout << "Автор: " << author << "\n";
    std::cout << "Жанр: " << genre << "\n";
    std::cout << "Год издания: " << year << "\n";
    std::cout << "Статус: " << (available ? "Доступна" : "Выдана") << "\n";
    std::cout << "------------------------\n";
}