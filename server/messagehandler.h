#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include "connection.h"
#include <string>
#include <memory>
int readNumber(const std::shared_ptr<Connection>& conn);
std::string readString_p(const std::shared_ptr<Connection>& conn);
int readNumber_p(const std::shared_ptr<Connection>& conn);
void writeNumber(const std::shared_ptr<Connection>& conn, int value);
unsigned char readByte(const std::shared_ptr<Connection>& conn);
void writeByte(const std::shared_ptr<Connection>& conn, unsigned char data);
void writeNumber_p(const std::shared_ptr<Connection>& conn, int n);
void writeString_p(const std::shared_ptr<Connection>& conn, const std::string& s);
#endif
