#include "connection.h"
#include "../server/messagehandler.cc"
#include "protocol.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;

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
  writeByte(conn, Protocol::ANS_ACK);
  /*
  FETCH ALL NEWSGROUPS FROM SERVER HERE
  */
}

void print_create_newsgroup(const shared_ptr<Connection>& conn){
  print_title("Create a newsgroup");
  /*
  CREATE NEW NEWSGROUP HERE
  */
}

void print_delete_newsgroup(const shared_ptr<Connection>& conn){
  print_title("Delete a newsgroup");
  /*
  DELETE NEWSGROUP
  */
}

void print_list_articles(const shared_ptr<Connection>& conn){
  print_title("List all articles in newsgroup");
}

void print_create_article(const shared_ptr<Connection>& conn){
  print_title("Create new article");
}

void print_delete_article(const shared_ptr<Connection>& conn){
  print_title("Delete article");
}

void print_get_article(const shared_ptr<Connection>& conn){
  print_title("List specific article");
}


void print_menu(const shared_ptr<Connection>& conn) {

  int choice = 0;
  print_title("Main Menu");
	cout << "[1]: List all newsgroups" << endl;
	cout << "[2]: Create a newsgroup" << endl;
	cout << "[3]: Delete a newsgroup" << endl;
	cout << "[4]: List all articles in newsgroup" << endl;
	cout << "[5]: Create new article" << endl;
	cout << "[6]: Delete article" << endl;
	cout << "[7]: List specific article" << endl;
	cout << "[8]: Exit" << endl;
	cin >> choice;

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
  cout << "Enter a letter to continue:";
  char c;
  cin >> c;

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
