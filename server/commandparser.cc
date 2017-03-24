#include "commandparser.h"

#include <iostream>

using namespace std;

CommandParser::CommandParser() {

}

void CommandParser::list_newsgroup() {
  cout << "List newsgroup" << endl;
}
void CommandParser::create_newsgroup() {
  cout << "Create newsgroup" << endl;
}
void CommandParser::delete_newsgroup() {
  cout << "Delete newsgroup" << endl;
}
void CommandParser::list_articles() {
  cout << "List articles" << endl;
}
void CommandParser::create_article() {
  cout << "Create article" << endl;
}
void CommandParser::delete_article() {
  cout << "Delete article" << endl;
}
void CommandParser::get_article() {
  cout << "Get article" << endl;
}
