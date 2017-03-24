#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

class CommandParser {
public:
  CommandParser(/* database attribute */);
  void list_newsgroup();
  void create_newsgroup();
  void delete_newsgroup();
  void list_articles();
  void create_article();
  void delete_article();
  void get_article();
private:
  //Add Database Attribute here
};



#endif
