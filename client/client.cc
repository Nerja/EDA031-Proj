#include "connection.h"
#include "../server/messagehandler.cc"
#include "protocol.h"
#include "protocolexception.h"

#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include <exception>

using namespace std;

int read_number() {
  int number = 0;
  string input;
  getline(cin, input);

  stringstream myStream(input);
  if (myStream >> number) {
    return number;
  }
  throw invalid_argument("Expected int");
}

string read_string() {
  int number = 0;
  string input;
  getline(cin, input);
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
      cout << to_string(artId) << "\t\t\t" << title;
    }
  }
}

void print_create_article(const shared_ptr<Connection>& conn){
  print_title("Create new article");

  /*string input;

  cout << "\nEnter newsgroup id to create article in: ";
  int groupId = 0;
  getline(cin, input);

  stringstream myStream(input);
  if (myStream >> groupId) {
    //all good
  }

  cin.ignore();
  cin.sync();

  cout << "Enter title: ";
  string title;
  getline(cin, title);
  cin.ignore();
  cin.sync();
  cout << "Enter author: ";
  string author;
  getline(cin, author);

  cout << "Enter text, end with ^D:" << endl;
  string line;
  string text;
  while (getline(cin, line)) {
    if (line == "^D") {
      break;
    }
    text += (line + '\n');
  }


    cin.ignore();
    cin.sync();

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

  cin.ignore();
  cin.sync();
  */
}

void print_delete_article(const shared_ptr<Connection>& conn){
  print_title("Delete article");
}

void print_get_article(const shared_ptr<Connection>& conn){
  print_title("List specific article");
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
