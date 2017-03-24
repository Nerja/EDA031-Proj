#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include "connection.h"
#include <string>
#include <memory>
void writeString(const std::shared_ptr<Connection>& conn, const std::string& s);
int readNumber(const std::shared_ptr<Connection>& conn);
std::string readString(const Connection& conn);
void writeNumber(const Connection& conn, int value);
unsigned char readByte(const std::shared_ptr<Connection>& conn);
void writeByte(const std::shared_ptr<Connection>& conn, unsigned char data);
#endif
