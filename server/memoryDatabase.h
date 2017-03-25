#ifndef MEMORYDATABASE_H
#define MEMORYDATABASE_H

#include "database.h"
#include "databaseExceptions.h"
#include <string>
#include <vector>
#include <map>

class MemoryDatabase : public Database {
	public:
		std::vector<NewsGroup> list_newsgroups() const;

		void create_newsgroup(std::string name) throw(invalid_group_name_exception);

		void delete_newsgroup(int id) throw(invalid_group_id_exception);

		Article read_article(int group, int article)
				throw(invalid_group_id_exception, invalid_article_id_exception);

		void create_article(int group, std::string title, std::string author, std::string text)
				throw(invalid_group_id_exception);

		void delete_article(int group, int article)
				throw(invalid_group_id_exception, invalid_article_id_exception);

		std::vector<Article> list_articles(int group) throw(invalid_group_id_exception);
	private:
		std::map<int,NewsGroup> newsgroups;
		int id = 0;
};


#endif
