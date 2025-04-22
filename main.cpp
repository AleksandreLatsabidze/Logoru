#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"  // ლოგერის ბიბლიოთეკა
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
using namespace std;
map<string, string> library;
// ფუნქცია წიგნის დასამატებლად
void addBook(const string& title, const string& author) {
    LOG_S(1) << "addBook() წელი\"" << title << "\", ავტორი=\"" << author << "\"";
    
    if (library.find(title) != library.end()) {
        LOG_F(ERROR, "წიგნი უკვე არსებობს: %s", title.c_str());
        return;
    }

    library[title] = author;
    LOG_F(INFO, "წიგნი დაემატა: %s ავტორი: %s", title.c_str(), author.c_str());
}
// ფუნქცია წიგნის მოსაძებნად
void findBook(const string& title) {
    LOG_S(1) << "findBook()  ფუნქცია გამოძახებულია \"" << title << "\"";

    if (library.find(title) != library.end()) {
        LOG_F(INFO, "წიგნი ნაპოვნია: %s ავტორი: %s", title.c_str(), library[title].c_str());
    } else {
        LOG_F(ERROR, "წიგნი არ მოიძებნა: %s", title.c_str());
    }
}
// ფუნქცია წიგნის გასაუქმებლად
void deleteBook(const string& title) {
    LOG_S(1) << "deleteBook()  ფუნქცია გამოძახებულია \"" << title << "\"";

    if (library.erase(title)) {
        LOG_F(INFO, "წიგნი წაიშალა: %s", title.c_str());
    } else {
        LOG_F(ERROR, "წიგნი არ მოიძებნა: %s", title.c_str());
    }
}

int main(int argc, char* argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("log.txt", loguru::Append, loguru::Verbosity_MAX);

    LOG_F(INFO, "პროგრამა დაწყებულია");

    addBook("1984", "George Orwell");
    addBook("The Hobbit", "J.R.R. Tolkien");
    addBook("1984", "George Orwell");

    findBook("The Hobbit");
    findBook("Unknown Book");

    deleteBook("1984");
    deleteBook("Unknown Book");

    LOG_F(INFO, "პროგრამა დასრულდა");
}
