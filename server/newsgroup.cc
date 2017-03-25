#include "newsgroup.h"
#include "article.h"
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

// constructor name + unique id
NewsGroup::NewsGroup(std::string s, size_t i) : name(s), group_id(i), time_of_creation(time(0)) {}
// get name
std::string NewsGroup::get_name() const { return name; }
// get group id
int NewsGroup::get_id() const { return group_id; }
// get articles
std::vector<Article> NewsGroup::get_articles() const {
    std::vector<Article> art_copy(articles.begin(), articles.end());
    sort(art_copy.begin(), art_copy.end());
    return art_copy;
}

// add article to article list
void NewsGroup::add_articles(Article a) { articles.push_back(a); }

// find article with id article_id delete it
bool NewsGroup::delete_article(int article_id) {
    auto lam = [article_id](const Article& art){return art.get_id() == article_id;};
    auto itr = find_if(articles.begin(), articles.end(), lam);
    // if article is found delete it, else return false
    if (itr != articles.end()) {
        articles.erase(itr);
        return true;
    }
    return false;
}

// for sorting news groups oldest --> youngest
bool operator<(const NewsGroup& ng1, const NewsGroup& ng2) {
    return ng1.time_of_creation < ng2.time_of_creation;
}
