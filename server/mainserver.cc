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
  while (true) {
    auto conn = server.waitForActivity();
    if (conn != nullptr) {
      try {
        auto command = readByte(conn);
        switch(command) {
          case Protocol::COM_LIST_NG:
            cout << "yay" << endl;
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
