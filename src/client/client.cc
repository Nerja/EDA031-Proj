#include "connection.h"
#include "../server/messagehandler.cc"
#include "protocol.h"
#include "protocolexception.h"

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <exception>
#include <algorithm>

using namespace std;

int read_number() {
  int number = 0;
  string input;
  getline(cin, input);

  if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  stringstream myStream(input);
  if (myStream >> number) {
    return number;
  }
  throw invalid_argument("Expected int");
}

string read_string() {
  string input;
  getline(cin, input);
  if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return input;
}

void clear(){
  cout << string(100, '\n' );
}

void clear(string msg){
  clear();
  cout << msg << endl;
}

void print_title(string msg) {
  clear();
  int nbr_chars = 45;
  int spaces = 2;
  int nbr_stars = (nbr_chars - spaces - msg.length()) / 2;
  cout << string(nbr_stars, '*') << " " << msg << " " << string(nbr_stars, '*');
  //För ojämnt antal tecken så lägg till en extra stjärna till höger
  if( (nbr_chars - spaces - msg.length()) % 2 > 0) {
    cout << "*";
  }
  cout << endl;
}

void print_list_newsgroups(const shared_ptr<Connection>& conn){
  print_title("List all newsgroups");
  writeByte(conn, Protocol::COM_LIST_NG);
  writeByte(conn, Protocol::COM_END);

  auto ans = readByte(conn);
  if(ans != Protocol::ANS_LIST_NG)
    throw wrong_anstype();

  int numberGroups = readNumber_p(conn);
  cout << "Group nbr:\t\t\tGroup name:" << endl;
  for(int i = 0; i != numberGroups; ++i) {
    int groupNbr = readNumber_p(conn);
    string groupName = readString_p(conn);
    cout << to_string(groupNbr) << "\t\t\t" << groupName << endl;
  }
}

void print_create_newsgroup(const shared_ptr<Connection>& conn){
  print_title("Create a newsgroup");
  cout << "Enter name of the newsgroup to create: ";
  string groupName = read_string();
  writeByte(conn, Protocol::COM_CREATE_NG);
  writeString_p(conn, groupName);
  writeByte(conn, Protocol::COM_END);
  if(readByte(conn) != Protocol::ANS_CREATE_NG)
    throw wrong_anstype();

  auto status = readByte(conn);
  if(status != Protocol::ANS_ACK) {
    cout << "Newsgroup already exists!" << endl;
    readByte(conn); //read trailing byte
  } else {
    cout << "Newsgroup was created" << endl;
  }
}

void print_delete_newsgroup(const shared_ptr<Connection>& conn){
  print_title("Delete a newsgroup");
  cout << "Enter newsgroup id to delete: ";
  int groupId = read_number();
  writeByte(conn, Protocol::COM_DELETE_NG);
  writeNumber_p(conn, groupId);
  writeByte(conn, Protocol::COM_END);

  if(readByte(conn) != Protocol::ANS_DELETE_NG)
    throw wrong_anstype();

  auto status = readByte(conn);
  if(status != Protocol::ANS_ACK) {
    cout << "No such newsgroup, check id!" << endl;
    readByte(conn); //read trailing byte
  } else {
    cout << "Newsgroup was deleted" << endl;
  }
}

void print_list_articles(const shared_ptr<Connection>& conn){
  print_title("List all articles in newsgroup");
  cout << "Enter newsgroup id to view: ";
  int groupId = read_number();
  writeByte(conn, Protocol::COM_LIST_ART);
  writeNumber_p(conn, groupId);
  writeByte(conn, Protocol::COM_END);

  if(readByte(conn) != Protocol::ANS_LIST_ART)
    throw wrong_anstype();

  if(readByte(conn) != Protocol::ANS_ACK) {
    cout << "No such newsgroup, check id!" << endl;
    readByte(conn); //read trailing byte
  } else {
    cout << "Article nbr:\t\t\tArticle name:" << endl;
    int numberArticles = readNumber_p(conn);
    for(int i = 0; i != numberArticles; ++i) {
      int artId = readNumber_p(conn);
      string title = readString_p(conn);
      cout << to_string(artId) << "\t\t\t" << title << endl;
    }
  }
}

void print_create_article(const shared_ptr<Connection>& conn){
  print_title("Create new article");

  cout << "\nEnter newsgroup id to create article in: ";
  int groupId = read_number();

  cout << "Enter title: ";
  string title = read_string();

  cout << "Enter author: ";
  string author = read_string();

  cout << "Enter text, end with ^D:" << endl;
  string line;
  string text;
  while (getline(cin, line)) {
    if (line == "^D") {
      break;
    }
    text += (line + '\n');
  }

  writeByte(conn, Protocol::COM_CREATE_ART);
  writeNumber_p(conn, groupId);
  writeString_p(conn, title);
  writeString_p(conn, author);
  writeString_p(conn, text);
  writeByte(conn, Protocol::COM_END);

  if(readByte(conn) != Protocol::ANS_CREATE_ART)
    throw wrong_anstype();

  if(readByte(conn) != Protocol::ANS_ACK) {
    cout << "No such newsgroup, check id!" << endl;
    readByte(conn); //read trailing byte
  }
  else {
    cout << "Article was successfully created!" << endl;
  }
}

void print_delete_article(const shared_ptr<Connection>& conn){
  print_title("Delete article");

  cout << "Enter newsgroup id containing article: ";
  int groupId = read_number();
  cout << "Enter article id to delete: ";
  int articleId = read_number();


  writeByte(conn, Protocol::COM_DELETE_ART);
  writeNumber_p(conn, groupId);
  writeNumber_p(conn, articleId);
  writeByte(conn, Protocol::COM_END);

  if(readByte(conn) != Protocol::ANS_DELETE_ART)
    throw wrong_anstype();

  auto status = readByte(conn);
  if(status != Protocol::ANS_ACK) {
    auto error = readByte(conn);
    if(error == Protocol::ERR_NG_DOES_NOT_EXIST) {
      cout << "No such newsgroup, check id!" << endl;
    }
    else {
      cout << "No such article, check id!" << endl;
    }
  } else {
    cout << "Article was deleted" << endl;
  }
}

void print_get_article(const shared_ptr<Connection>& conn){
  print_title("List specific article");

  cout << "Enter newsgroup id containing article: ";
  int groupId = read_number();
  cout << "Enter article id to list: ";
  int articleId = read_number();

  writeByte(conn, Protocol::COM_GET_ART);
  writeNumber_p(conn, groupId);
  writeNumber_p(conn, articleId);
  writeByte(conn, Protocol::COM_END);

  if(readByte(conn) != Protocol::ANS_GET_ART)
    throw wrong_anstype();

  auto status = readByte(conn);
  if (status != Protocol::ANS_ACK) {
    auto error = readByte(conn);
    if(error == Protocol::ERR_NG_DOES_NOT_EXIST) {
      cout << "No such newsgroup, check id!" << endl;
    }
    else {
      cout << "No such article, check id!" << endl;
    }
  }
  else {
    string title = readString_p(conn);
    string author = readString_p(conn);
    string text = readString_p(conn);

    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Text:\n" << text << endl;
  }
}


void print_menu(const shared_ptr<Connection>& conn) {


  print_title("Main Menu");
	cout << "[1]: List all newsgroups" << endl;
	cout << "[2]: Create a newsgroup" << endl;
	cout << "[3]: Delete a newsgroup" << endl;
	cout << "[4]: List all articles in newsgroup" << endl;
	cout << "[5]: Create new article" << endl;
	cout << "[6]: Delete article" << endl;
	cout << "[7]: List specific article" << endl;
	cout << "[8]: Exit" << endl;
  cout << "Please enter option: ";
	int choice = read_number();

	switch(choice) {
	case 1:
    print_list_newsgroups(conn);
		break;
	case 2:
    print_create_newsgroup(conn);
		break;
	case 3:
    print_delete_newsgroup(conn);
		break;
	case 4:
    print_list_articles(conn);
		break;
	case 5:
    print_create_article(conn);
		break;
	case 6:
    print_delete_article(conn);
		break;
	case 7:
    print_get_article(conn);
		break;
  case 8:
    clear();
    return;
	default:
    clear("ERROR IDIOT");
		break;
	}
  auto endByte = readByte(conn);
  if(endByte != Protocol::ANS_END)
    throw missing_ans_end();
  cout << "Enter a letter and press enter to continue:";
  read_string();

  print_menu(conn);

}


int main(int argc, char* argv[]) {
  if(argc != 3) {
    cerr << "Please enter host IP-address and port" << endl;
    exit(1);
  }
  shared_ptr<Connection> conn(new Connection(argv[1], stoi(argv[2])));
  if(!conn->isConnected()) {
    cerr << "Could not connect, check IP-address and port" << endl;
    exit(1);
  }
  print_menu(conn);
}
