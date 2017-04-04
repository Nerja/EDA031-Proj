#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H
#include "connection.h"
#include <memory>
#include "database.h"

class CommandParser {
public:
  CommandParser(Database& db) : database(db) {} //inline
  void list_newsgroup(const std::shared_ptr<Connection>& conn);
  void create_newsgroup(const std::shared_ptr<Connection>& conn);
  void delete_newsgroup(const std::shared_ptr<Connection>& conn);
  void list_articles(const std::shared_ptr<Connection>& conn);
  void create_article(const std::shared_ptr<Connection>& conn);
  void delete_article(const std::shared_ptr<Connection>& conn);
  void get_article(const std::shared_ptr<Connection>& conn);
private:
  Database& database;
};



#endif
