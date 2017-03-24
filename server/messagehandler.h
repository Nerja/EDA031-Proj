#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include "Connection.h"
#include <string>
#include <memory>
void writeString(const std::shared_ptr<Connection>& conn, const std::string& s);
int readNumber(const std::shared_ptr<Connection>& conn);
std::string readString(const Connection& conn);
void writeNumber(const Connection& conn, int value);
#endif
