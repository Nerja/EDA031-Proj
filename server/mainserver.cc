#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include "messagehandler.h"
#include "protocol.h"
#include "commandparser.h"
#include "database.h"
#include "memoryDatabase.h"

using namespace std;

int main(int argc, char* argv[]){
  if (argc != 2) {
    cerr << "Usage: myserver port-number" << endl;
    exit(1);
  }
  int port = -1;
  try {
    port = stoi(argv[1]);
  } catch (exception& e) {
    cerr << "Wrong port number. " << e.what() << endl;
    exit(1);
  }
  Server server(port);
  if (!server.isReady()) {
    cerr << "Server initialization error." << endl;
    exit(1);
  }
  MemoryDatabase db;
  CommandParser command_parser(db);
  while (true) {
    auto conn = server.waitForActivity();
    if (conn != nullptr) {
      try {
        auto command = readByte(conn);
        switch(command) {
          case Protocol::COM_LIST_NG:
            command_parser.list_newsgroup(conn);
          break;
          case Protocol::COM_CREATE_NG:
            command_parser.create_newsgroup(conn);
          break;
          case Protocol::COM_DELETE_NG:
            command_parser.delete_newsgroup(conn);
          break;
          case Protocol::COM_LIST_ART:
            command_parser.list_articles(conn);
          break;
          case Protocol::COM_CREATE_ART:
            command_parser.create_article(conn);
          break;
          case Protocol::COM_DELETE_ART:
            command_parser.delete_article(conn);
          break;
          case Protocol::COM_GET_ART:
            command_parser.get_article(conn);
          break;
          default:
            cout << "Violation of protocol, idiot" << endl;
            break;
        }
        auto end = readByte(conn);
        if(end != Protocol::COM_END) {
            cout << "Protocol problems, client disconnected!" << endl;
            server.deregisterConnection(conn);
        } else {
          cout << "Command done" << endl;
        }
      } catch (ConnectionClosedException&) {
        server.deregisterConnection(conn);
        cout << "Client closed connection" << endl;
      }
    } else {
      conn = make_shared<Connection>();
      server.registerConnection(conn);
      cout << "New client connects" << endl;
    }
  }
}
