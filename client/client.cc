#include <iostream>
#include <string>

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

void print_list_newsgroups(){
  print_title("List all newsgroups");
  /*
  FETCH ALL NEWSGROUPS FROM SERVER HERE
  */
  char c;
  cin >> c;
}

void print_create_newsgroup(){
  print_title("Create a newsgroup");
  /*
  CREATE NEW NEWSGROUP HERE
  */
  char c;
  cin >> c;
}

void print_delete_newsgroup(){
  print_title("Delete a newsgroup");
  /*
  DELETE NEWSGROUP
  */
  char c;
  cin >> c;
}

void print_list_articles(){
  print_title("List all articles in newsgroup");
  char c;
  cin >> c;
}

void print_create_article(){
  print_title("Create new article");
  char c;
  cin >> c;
}

void print_delete_article(){
  print_title("Delete article");
  char c;
  cin >> c;
}

void print_get_article(){
  print_title("List specific article");
  char c;
  cin >> c;
}


void print_menu() {

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
    print_list_newsgroups();
		break;
	case 2:
    print_create_newsgroup();
		break;
	case 3:
    print_delete_newsgroup();
		break;
	case 4:
    print_list_articles();
		break;
	case 5:
    print_create_article();
		break;
	case 6:
    print_delete_article();
		break;
	case 7:
    print_get_article();
		break;
  case 8:
    clear();
    return;
	default:
    clear("ERROR IDIOT");
		break;
	}

  print_menu();

}


int main() {
  print_menu();
}
