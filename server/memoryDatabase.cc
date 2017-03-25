#include "memoryDatabase.h"

std::vector<NewsGroup> MemoryDatabase::list_newsgroups() const {

}

bool MemoryDatabase::create_newsgroup(std::string name) {

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
