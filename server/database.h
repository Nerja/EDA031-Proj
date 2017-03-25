#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "newsgroup.h"
#include "article.h"
#include <string>
class Database {
	virtual std::vector<NewsGroup> list_newsgroups() const = 0;
	virtual boolean create_newsgroup(std::string name) = 0;
	virtual boolean delete_newsgroup(int int) = 0;
	virtual Article read_article(int group, int article) = 0;
	virtual void create_article(int group, std::string title, std::string author, std::string text) = 0;
	virtual boolean delete_article(int group, int article) = 0;
	virtual std::vector<Article> list_articles(int group) = 0; 
};
#endif
