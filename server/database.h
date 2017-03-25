#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "newsgroup.h"
#include "article.h"
#include <string>
class Database {
public:
	virtual std::vector<NewsGroup> list_newsgroups() const = 0;
	virtual bool create_newsgroup(std::string name) = 0;
	virtual bool delete_newsgroup(int id) = 0;
	virtual Article read_article(int group, int article) = 0;
	virtual bool create_article(int group, std::string title, std::string author, std::string text) = 0;
	virtual int delete_article(int group, int article) = 0;
	virtual std::vector<Article> list_articles(int group) = 0;
};
#endif
