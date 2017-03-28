#include <string>
#include "article.h"
#include <ctime>

// creates a article with title, author, text, id and generate a timestamp
// timestamp is used for sorting oldest -> youngest
Article::Article(std::string ti, std::string a, std::string te, int id) :
    title(ti), author(a), text(te), article_id(id) {}

// getters
std::string Article::get_title() const { return title; }
std::string Article::get_author() const { return author; }
std::string Article::get_text() const { return text; }
int Article::get_id() const { return article_id; }

// for sorting articles by time of creation oldest -> youngest
bool operator<(const Article& a1, const Article& a2) {
    return a1.article_id < a2.article_id;
}
