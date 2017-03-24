#include "messagehandler.h"
#include "connection.h"
#include <string>
#include <memory>
#include <iostream>

using namespace std;

void writeNumber(const Connection& conn, int value) {
  conn.write((value >> 24) & 0xFF);
  conn.write((value >> 16) & 0xFF);
  conn.write((value >> 8)  & 0xFF);
  conn.write(value & 0xFF);
}

std::string readString(const Connection& conn) {
  std::string s;
  char ch;
  while ((ch = conn.read()) != '$') {
    s += ch;
  }
  return s;
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