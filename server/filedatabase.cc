#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <map>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "databaseExceptions.h"
#include "article.h"
#include "newsgroup.h"
#include "filedatabase.h"


const std::string PATH = "./newsgroups/";
const std::string LIST_NEWSGROUP = "newsgrouplist";

std::vector<NewsGroup> FileDatabase::list_newsgroups() const {}

void FileDatabase::create_newsgroup(std::string name) throw(invalid_group_name_exception) {

	std::hash<std::string> hash;
	size_t hash_id = hash(name);
	std::ofstream f;
	f.open(PATH+LIST_NEWSGROUP);

	std::string path = PATH;
	path.append(name);
	path.append("_"+std::to_string(hash_id));
	const char* c = path.c_str();
	if( mkdir(c, 0777) == -1) {
		throw invalid_group_name_exception();
	}
	f << name+"_"+std::to_string(hash_id) << "\n";
	f.close();


}

void FileDatabase::delete_newsgroup(int id) throw(invalid_group_id_exception){
	std::ifstream f(PATH+LIST_NEWSGROUP, std::ifstream::in);
	std::string line;
	std::string string_id = std::to_string(id);
	size_t p;

	while( getline(f, line) ) {
		p = line.find_last_of("_");
			if(line.substr(p) == string_id ) {
				std::string path = PATH;
				path.append(line);
				const char* c = path.c_str();
				rmdir(c);
				line.replace(line.find(line), line.length(), "");			
			}
	}
		
}

Article FileDatabase::read_article(int group, int article)
	throw(invalid_group_id_exception, invalid_article_id_exception) {}

void FileDatabase::create_article(int group, std::string title, std::string author, std::string text)
	throw(invalid_group_id_exception){}

void FileDatabase::delete_article(int group, int article)
	throw(invalid_group_id_exception, invalid_article_id_exception) {}

std::vector<Article> FileDatabase::list_articles(int group) throw(invalid_group_id_exception){}


int main() {
	std::string newsgroup = "test3";
	FileDatabase db;
	db.create_newsgroup(newsgroup);
	return 0;
}
