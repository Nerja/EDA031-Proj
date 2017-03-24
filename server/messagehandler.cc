#include "messagehandler.h"
#include "connection.h"
#include <string>
#include <memory>
#include <iostream>
#include "protocol.h"

using namespace std;

void writeNumber(const shared_ptr<Connection>& conn, int value) {
  conn->write((value >> 24) & 0xFF);
  conn->write((value >> 16) & 0xFF);
  conn->write((value >> 8)  & 0xFF);
  conn->write(value & 0xFF);
}

std::string readString_p(const shared_ptr<Connection>& conn) {
  string s;
  unsigned char byte = conn->read();
  if(byte != Protocol::PAR_STRING)
    throw invalid_argument("protocol violation");
  int number_chars = readNumber(conn);
  for(int i = 0; i != number_chars; ++i)
    s += static_cast<char>(conn->read());
  return s;
}

int readNumber_p(const shared_ptr<Connection>& conn) {
  unsigned char p_byte = conn->read();
  if(p_byte != Protocol::PAR_NUM)
    throw invalid_argument("protocol violation");
  return readNumber(conn);
}

int readNumber(const shared_ptr<Connection>& conn) {
  unsigned char byte1 = conn->read();
  unsigned char byte2 = conn->read();
  unsigned char byte3 = conn->read();
  unsigned char byte4 = conn->read();
  return (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;
}

unsigned char readByte(const shared_ptr<Connection>& conn) {
  return conn->read();
}

void writeByte(const shared_ptr<Connection>& conn, unsigned char data) {
  conn->write(data);
}

void writeString(const std::shared_ptr<Connection>& conn, const std::string& s) {
  for (char c : s) {
    conn->write(c);
  }
  conn->write('$');
}
