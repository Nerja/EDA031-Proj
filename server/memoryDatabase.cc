#include <string>
#include <functional>
#include <vector>
#include <utility>

#include "memoryDatabase.h"
#include "newsgroup.h"
#include "article.h"

std::vector<NewsGroup> MemoryDatabase::list_newsgroups() const {

}

bool MemoryDatabase::create_newsgroup(std::string name) {
	std::hash<std::string> hash;
	size_t hash_id = hash(name);
	
	NewsGroup n(name, hash_id);

	auto it = newsgroups.find(hash_id);
	if(it == newsgroups.end() )
		return false;

	newsgroups.insert(std::make_pair(hash_id, n));
	return true;	
}


bool MemoryDatabase::delete_newsgroup(int group_id) {

}

Article MemoryDatabase::read_article(int group_id, int article) {

}

// creates a article, generate a unique id for the article
bool MemoryDatabase::create_article(int group_id, std::string title, std::string author, std::string text) {

}

bool MemoryDatabase::delete_article(int group_id, int article) {

}

std::vector<Article> MemoryDatabase::list_articles(int group_id) {

}
