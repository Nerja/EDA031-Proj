#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include <exception>

class invalid_group_id_exception : public std::exception {
public:
      virtual const char* what() const throw() {
            return "Group id does not exists";
      }

};

class invalid_article_id_exception : public std::exception {
public:
      virtual const char* what() const throw() {
            return "Article id does not exists";
      }
};

class invalid_group_name_exception : public std::exception {
public:
      virtual const char* what() const throw() {
            return "Group name already exists";
      }
};

#endif
