#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include "connection.h"
#include <memory>

class CommandParser {
public:
  CommandParser(/* database attribute */);
  void list_newsgroup(const std::shared_ptr<Connection>& conn);
  void create_newsgroup(const std::shared_ptr<Connection>& conn);
  void delete_newsgroup(const std::shared_ptr<Connection>& conn);
  void list_articles(const std::shared_ptr<Connection>& conn);
  void create_article(const std::shared_ptr<Connection>& conn);
  void delete_article(const std::shared_ptr<Connection>& conn);
  void get_article(const std::shared_ptr<Connection>& conn);
private:
  //Add Database Attribute here
};



#endif
