#include "memoryDatabase.h"
#include "article.h"
#include "newsgroup.h"
#include <vector>
#include <string>
#include <functional>
#include <utility>

std::vector<NewsGroup> MemoryDatabase::list_newsgroups() const {
  std::vector<NewsGroup> vec_ret;
	auto it = newsgroups.begin();
	for( it; it != newsgroups.end(); ++it) {
		NewsGroup t = it->second;
		vec_ret.push_back(t);
	}
	return vec_ret;

}

bool MemoryDatabase::create_newsgroup(std::string name) {
  std::hash<std::string> hash;
	size_t hash_id = hash(name);

	NewsGroup n(name, hash_id);

	auto it = newsgroups.find(hash_id);
	if(it != newsgroups.end() )
		return false;

	newsgroups.insert(std::make_pair(hash_id, n));
	return true;
}

bool MemoryDatabase::delete_newsgroup(int group_id) {
  auto it = newsgroups.find(group_id);
	if(it != newsgroups.end() ) {
		newsgroups.erase(it);
		return true;
	}
	return false;

}

Article MemoryDatabase::read_article(int group_id, int article) {

}

// creates a article, generate a unique id for the article
bool MemoryDatabase::create_article(int group_id, std::string title, std::string author, std::string text) {
      auto itr = newsgroups.find(group_id);
      if (itr != newsgroups.end()) {
            itr->second.add_articles(Article(title, author, text, id++));
            return true;
      }
      return false;
}
// Delete an article. The group and article identification numbers are sent as parameters.
// 0 = all went well,
// 1 = group_id doesn't exists,
// 2 = article_id doesn't exists
int MemoryDatabase::delete_article(int group_id, int article_id) {
      auto itr = newsgroups.find(group_id);
      if (itr != newsgroups.end()) {
            return itr->second.delete_article(article_id) ? 0 : 2;
      }
      return 1;
}

// List articles in a newsgroup. The identification number of the group is sent as a parameter.
// The reply contains the number of articles, followed by the identification numbers and titles
// of the articles.
// returns a vector containing articles for a news group with id = group_id
// return an empty vector if group id doesn't exists
std::vector<Article> MemoryDatabase::list_articles(int group_id) {
      auto itr = newsgroups.find(group_id);
      if (itr != newsgroups.end()) {
            return itr->second.get_articles();
      }
      std::vector<Article> no_articles;
      return no_articles;
}
