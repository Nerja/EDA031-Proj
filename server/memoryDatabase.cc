#include "memoryDatabase.h"
#include "article.h"
#include "newsgroup.h"
#include "databaseExceptions.h"
#include <vector>
#include <string>
#include <functional>
#include <utility>
#include <algorithm>

// List newsgroups. The reply contains the number of newsgroups followed by the identification
// numbers and titles of the groups.
std::vector<NewsGroup> MemoryDatabase::list_newsgroups() const {

      std::vector<NewsGroup> vec_ret;
	    auto it = newsgroups.begin();
	    for(; it != newsgroups.end(); ++it) {
		        NewsGroup t = it->second;
		        vec_ret.push_back(t);
	    }
	    return vec_ret;

}

// Create a newsgroup. The title of the group is sent as a parameter.
void MemoryDatabase::create_newsgroup(std::string name) throw(invalid_group_name_exception){

      std::hash<std::string> hash;
	    size_t hash_id = hash(name);

	    NewsGroup n(name, hash_id);

	    auto it = newsgroups.find(hash_id);
	    if(it != newsgroups.end() )
		      throw invalid_group_name_exception();

	    newsgroups.insert(std::make_pair(hash_id, n));
}

// Delete a newsgroup. The identification number of the group is sent as a parameter.
// throws invalid_group_id_exception
void MemoryDatabase::delete_newsgroup(int group_id) throw(invalid_group_id_exception) {

      auto it = newsgroups.find(group_id);
	    if(it != newsgroups.end() ) {
		        newsgroups.erase(it);
	    }
	    throw invalid_group_id_exception();
}

// Get an article. The group and article identification numbers are sent as parameters. The
// reply contains the title, author, and text of the article.
// throws invalid_group_id_exception / invalid_article_id_exception
Article MemoryDatabase::read_article(int group_id, int article_id)
    throw(invalid_group_id_exception, invalid_article_id_exception) {

	    auto it = newsgroups.find(group_id);
	    if(it != newsgroups.end() ) {
            std::vector<Article> v = it->second.get_articles();
            auto lam = [article_id](const Article& a) { return a.get_id() == article_id; };
		        auto itv = find_if(v.begin(), v.end(), lam);
		        if(itv != v.end()) {
                  return *itv;
            } else {
                  throw invalid_article_id_exception();
            }
	    }
	    throw invalid_group_id_exception();
}

// creates a article, generate a unique id for the article
// throws invalid_group_id_exception
void MemoryDatabase::create_article(int group_id, std::string title, std::string author, std::string text)
    throw(invalid_group_id_exception) {

      auto itr = newsgroups.find(group_id);
      if (itr != newsgroups.end()) {
            itr->second.add_articles(Article(title, author, text, id++));
      }
      throw invalid_group_id_exception();
}
// Delete an article. The group and article identification numbers are sent as parameters.
// throws invalid_group_id_exception / invalid_article_id_exception
void MemoryDatabase::delete_article(int group_id, int article_id)
    throw(invalid_group_id_exception, invalid_article_id_exception) {

      auto itr = newsgroups.find(group_id);
      if (itr != newsgroups.end()) {
            if(!itr->second.delete_article(article_id)) {
                  throw invalid_article_id_exception();
            }
      }
      throw invalid_group_id_exception();
}

// List articles in a newsgroup. The identification number of the group is sent as a parameter.
// The reply contains the number of articles, followed by the identification numbers and titles
// of the articles.
// returns a vector containing articles for a news group with id = group_id
// throw invalid_group_id_exception if group id doesn't exists
std::vector<Article> MemoryDatabase::list_articles(int group_id) throw(invalid_group_id_exception) {
      auto itr = newsgroups.find(group_id);
      if (itr != newsgroups.end()) {
            return itr->second.get_articles();
      }
      throw invalid_group_id_exception();
}
