#include "database.h"
#include <string>
#include <vector>
#include <map>

class MemoryDatabase : public Database {
	public:
		std::vector<NewsGroup> list_newsgroups() const;
		boolean create_newsgroup(std::string name);
		boolean delete_newsgroup(int id);
		Article read_article(int group, int article);
		void create_article(int group, std::string title, std::string author, std::string text);
		boolean delete_article(int group, int article);
		std::vector<Article> list_articles(int group);
	private:
		std::map<int,NewsGroup> newsgroups;
}
