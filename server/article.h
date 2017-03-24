#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <ctime>

class Article {
public:
    //database generate a unique id
    //article generate a time_t for comparing articles
    Article(std::string title, std::string author, std::string text, int id);
    std::string get_title() const;
    std::string get_author() const;
    std::string get_text() const;
    int get_id() const;
    friend bool operator<(const Article& a1, const Article& a2);
private:
    std::string title;
    std::string author;
    std::string text;
    int article_id;
    time_t time_of_creation;
};

#endif
