#include <string>
#include <functional>
#include <vector>

#include "memoryDatabase.h"
#include "newsgroup.h"
#include "article.h"

std::vector<NewsGroup> MemoryDatabase::list_newsgroups() const {

}

boolean MemoryDatabase::create_newsgroup(std::string name) {
	hash<std::string> hash_id(name);
	Newsgroup n(name, hash_id);
		
}

boolean delete_newsgroup(int id) {

}

Article read_article(int group, int article) {

}

void create_article(int group, std::string title, std::string author, std::string text) {

}
boolean delete_article(int group, int article) {

}

std::vector<Article> list_articles(int group) {

}
