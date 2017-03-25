#include "messagehandler.h"
#include "commandparser.h"
#include "connection.h"
#include "protocol.h"

#include <memory>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void CommandParser::list_newsgroup(const shared_ptr<Connection>& conn) {
  writeByte(conn, Protocol::ANS_LIST_NG);
  vector<NewsGroup> groups = database.list_newsgroups();
  writeNumber_p(conn, groups.size());

  for(const NewsGroup& group : groups) {
    writeNumber_p(conn, group.get_id());
    writeString_p(conn, group.get_name());
  }

  writeByte(conn, Protocol::ANS_END);
}
void CommandParser::create_newsgroup(const shared_ptr<Connection>& conn) {
  string group_name = readString_p(conn);
  bool created = database.create_newsgroup(group_name);
  writeByte(conn, Protocol::ANS_CREATE_NG);
  if(created)
    writeByte(conn, Protocol::ANS_ACK);
  else {
    writeByte(conn, Protocol::ANS_NAK);
    writeByte(conn, Protocol::ERR_NG_ALREADY_EXISTS);
  }
  writeByte(conn, Protocol::ANS_END);
}
void CommandParser::delete_newsgroup(const shared_ptr<Connection>& conn) {
  int group_id = readNumber_p(conn);
  writeByte(conn, Protocol::ANS_DELETE_NG);
  bool removed = database.delete_newsgroup(group_id);
  if(removed)
    writeByte(conn, Protocol::ANS_ACK);
  else {
    writeByte(conn, Protocol::ANS_NAK);
    writeByte(conn, Protocol::ERR_NG_DOES_NOT_EXIST);
  }
  writeByte(conn, Protocol::ANS_END);
}

//Fix if group id does not exists should answer negative according to protocol
void CommandParser::list_articles(const shared_ptr<Connection>& conn) {
  int group_id = readNumber_p(conn);
  writeByte(conn, Protocol::ANS_LIST_ART);
  vector<Article> articles = database.list_articles(group_id);
  writeByte(conn, Protocol::ANS_ACK);
  writeNumber_p(conn, articles.size());
  for(Article& article : articles) {
    writeNumber_p(conn, article.get_id());
    writeString_p(conn, article.get_title());
  }
  writeByte(conn, Protocol::ANS_END);
}
void CommandParser::create_article(const shared_ptr<Connection>& conn) {
  //int group_id = readNumber_p(conn);
  //string title = readString_p(conn);
  //string author = readString_p(conn);
  //string text = readString_p(conn);
  cout << "Create article" << endl;
  writeByte(conn, Protocol::ANS_END);
}
void CommandParser::delete_article(const shared_ptr<Connection>& conn) {
  //int group_id = readNumber_p(conn);
  //int article_id = readNumber_p(conn);
  cout << "Delete article" << endl;
  writeByte(conn, Protocol::ANS_END);
}
void CommandParser::get_article(const shared_ptr<Connection>& conn) {
  //int group_id = readNumber_p(conn);
  //int article_id = readNumber_p(conn);
  cout << "Get article" << endl;
  writeByte(conn, Protocol::ANS_END);
}
