#include "messagehandler.h"
#include "commandparser.h"
#include "connection.h"

#include <memory>
#include <iostream>
#include <string>

using namespace std;

CommandParser::CommandParser() {

}

void CommandParser::list_newsgroup(const shared_ptr<Connection>& conn) {
  cout << "List newsgroup name is " << endl;
}
void CommandParser::create_newsgroup(const shared_ptr<Connection>& conn) {
  string group_name = readString_p(conn);
  cout << "Create newsgroup " << group_name << endl;
}
void CommandParser::delete_newsgroup(const shared_ptr<Connection>& conn) {
  int group_id = readNumber_p(conn);
  cout << "Delete newsgroup " << to_string(group_id) << endl;
}
void CommandParser::list_articles(const shared_ptr<Connection>& conn) {
  int group_id = readNumber_p(conn);
  cout << "List articles" << endl;
}
void CommandParser::create_article(const shared_ptr<Connection>& conn) {
  int group_id = readNumber_p(conn);
  string title = readString_p(conn);
  string author = readString_p(conn);
  string text = readString_p(conn);
  cout << "Create article" << endl;
}
void CommandParser::delete_article(const shared_ptr<Connection>& conn) {
  int group_id = readNumber_p(conn);
  int article_id = readNumber_p(conn);
  cout << "Delete article" << endl;
}
void CommandParser::get_article(const shared_ptr<Connection>& conn) {
  int group_id = readNumber_p(conn);
  int article_id = readNumber_p(conn);
  cout << "Get article" << endl;
}
