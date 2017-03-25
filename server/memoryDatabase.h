#ifndef MEMORYDATABASE_H
#define MEMORYDATABASE_H

#include "database.h"
#include <string>
#include <vector>
#include <map>

class MemoryDatabase : public Database {
	public:
		std::vector<NewsGroup> list_newsgroups() const;
		bool create_newsgroup(std::string name);
		bool delete_newsgroup(int id);
		Article read_article(int group, int article);
		bool create_article(int group, std::string title, std::string author, std::string text);
		int delete_article(int group, int article);
		std::vector<Article> list_articles(int group);
	private:
		std::map<int,NewsGroup> newsgroups;
		bool matchArticleId(Article a, int id) {
			return a.get_id() == id;
		}
		int id = 0;
};


#endif
