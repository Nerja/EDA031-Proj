#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>
#include "article.h"
#include <vector>

class NewsGroup {
public:
    NewsGroup(std::string name, int id);
    std::string get_name() const;
    int get_id() const;
    std::vector<Article> get_articles() const;
    void add_articles(Article a);
    bool delete_article(int article_id);
    friend bool operator<(const NewsGroup& ng1, const NewsGroup& ng2);
private:
    std::string name;
    int group_id;
    std::vector<Article> articles;
};

#endif
