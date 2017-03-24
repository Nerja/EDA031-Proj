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
  CommandParser command_parser;
  while (true) {
    auto conn = server.waitForActivity();
    if (conn != nullptr) {
      try {
        auto command = readByte(conn);
        switch(command) {
          case Protocol::COM_LIST_NG:
            command_parser.list_newsgroup();
          break;
          case Protocol::COM_CREATE_NG:
            command_parser.create_newsgroup();
          break;
          case Protocol::COM_DELETE_NG:
            command_parser.delete_newsgroup();
          break;
          case Protocol::COM_LIST_ART:
            command_parser.list_articles();
          break;
          case Protocol::COM_CREATE_ART:
            command_parser.create_article();
          break;
          case Protocol::COM_DELETE_ART:
            command_parser.delete_article();
          break;
          case Protocol::COM_GET_ART:
            command_parser.get_article();
          break;
          default:
            cout << "Violation of protocol, idiot" << endl;
            break;
        }
        auto end = readByte(conn);
        cout << to_string(end) << endl;
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
