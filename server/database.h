#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "newsgroup.h"
#include "article.h"
#include "databaseExceptions.h"
#include <string>
class Database {
public:
	virtual std::vector<NewsGroup> list_newsgroups() const = 0;

	virtual void create_newsgroup(std::string name) throw(invalid_group_name_exception) = 0;

	virtual void delete_newsgroup(int id) throw(invalid_group_id_exception) = 0;

	virtual Article read_article(int group, int article)
	 		throw(invalid_group_id_exception, invalid_article_id_exception) = 0;

	virtual void create_article(int group, std::string title, std::string author, std::string text)
	 		throw(invalid_group_id_exception) = 0;

	virtual void delete_article(int group, int article)
			throw(invalid_group_id_exception, invalid_article_id_exception) = 0;
			
	virtual std::vector<Article> list_articles(int group) throw(invalid_group_id_exception) = 0;
};
#endif
