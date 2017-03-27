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
#include <stdio.h>

#include "databaseExceptions.h"
#include "article.h"
#include "newsgroup.h"
#include "filedatabase.h"


const std::string PATH = "./newsgroups/";
const std::string LIST_NEWSGROUP = ".newsgrouplist";

std::vector<NewsGroup> FileDatabase::list_newsgroups() const 
{
	std::ofstream f(PATH+LIST_NEWSGROUP, std::ifstream::in);
	std::vector<std::string> vec;
	std::string line;
	while(getline(f,line)) {
		vec.push_back(line);
	}
	return vec;
}

void FileDatabase::create_newsgroup(std::string name) throw(invalid_group_name_exception) 
{


	std::hash<std::string> hash;
	size_t hash_id = hash(name);
	std::ofstream f(PATH+LIST_NEWSGROUP, std::ifstream::in | std::ifstream::app); 

	std::string path = PATH;
	path.append(name);
	path.append("_"+std::to_string(hash_id));
	if( mkdir(path.c_str(), 0777) == -1) {
		throw invalid_group_name_exception();
	}
	f << name+"_"+std::to_string(hash_id) << "\n";
	f.close();


}

void FileDatabase::delete_newsgroup(size_t id) throw(invalid_group_id_exception)
{
	std::fstream f(PATH+LIST_NEWSGROUP, std::ifstream::in | std::ifstream::out);
	std::string rm;
	std::string line;
	std::string string_id = std::to_string(id);
	std::vector<std::string> new_list;
	size_t p;
	int count = 0;

	while( getline(f, line) ) {
		new_list.push_back(line);
		p = line.find_last_of("_");
			std::cout << line << std::endl;
			if(line.substr(p+1) == string_id ) {
				std::string path = PATH;
				path.append(line);
				rm = path;
				rmdir(path.c_str(););	
				new_list.erase(new_list.begin()+count);
			}
		++count;
	}
	if(rm.empty() )
		throw invalid_group_id_exception();
	f.close();
	remove(rm.c_str());
	std::fstream in(PATH+LIST_NEWSGROUP, std::ifstream::out);
	auto it = new_list.begin();
	while(it != new_list.end() ) {
		in << *it <<"\n";		
		++it;
	}
	in.close();
		
}

Article FileDatabase::read_article(int group, int article)
	throw(invalid_group_id_exception, invalid_article_id_exception) { 
				
}

void FileDatabase::create_article(int group, std::string title, std::string author, std::string text)
	throw(invalid_group_id_exception){
	std::fstream f(PATH+LIST_NEWSGROUP, std::ifstream::in);
	std::string line;
	while( getline(f, line) ) {
		size_t p = line.find_last_of("_");
		if( line.substr(p+1) == group ) {
			std::fstream article(PATH+LINE
		}
	}
	
}

void FileDatabase::delete_article(int group, int article)
	throw(invalid_group_id_exception, invalid_article_id_exception) {

}

std::vector<Article> FileDatabase::list_articles(int group) throw(invalid_group_id_exception){
	
}


int main() {
	std::string newsgroup = "test3";
	FileDatabase db;
	std::hash<std::string> hash;
	size_t hash_id = hash(newsgroup);
	db.create_newsgroup(newsgroup);
	db.create_newsgroup("test1");
	std::cout << hash_id << std::endl;
	db.delete_newsgroup(hash_id);
	return 0;
}
