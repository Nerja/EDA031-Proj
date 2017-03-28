#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <sys/stat.h>
#include <errno.h>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>
#include "databaseExceptions.h"
#include "article.h"
#include "newsgroup.h"
#include "filedatabase.h"


const std::string PATH = "./newsgroups/";
const std::string GROUP_ID = ".groupID";
const std::string ARTICLE_ID = ".articleID";
const std::string LIST_NEWSGROUP = ".newsgrouplist";

std::vector<NewsGroup> FileDatabase::list_newsgroups() const
{
	// open file-path to list of news groups
	std::ifstream in(PATH + LIST_NEWSGROUP);
	std::vector<NewsGroup> groups;
	std::string line;
	while(getline(in, line)) {
			std::string name(line, 0, line.find('_'));
			std::string id(line, line.find('_')+1, line.size());
			int i = atoi(id.c_str());
			groups.push_back(NewsGroup(name, i));

	}
	sort(groups.begin(), groups.end());
	return groups;


}
// check if group with the name name exists
bool FileDatabase::group_exists(std::string name) const {
	std::ifstream in(PATH + LIST_NEWSGROUP);
	std::string line;
	while(std::getline(in, line)) {
		std::string token(line, 0, line.find('_'));
		if (token == name) {
				return true;
		}
	}
	return false;
}

// check if a group with the id id exists
bool FileDatabase::group_id_exists(std::string id) const {
	std::ifstream in(PATH + LIST_NEWSGROUP);
	std::string line;
	while(std::getline(in, line)) {
		std::string token(line, line.find('_')+1, line.size());
		if (token == id) {
				return true;
		}
	}
	return false;
}

// find the folder path to group with the id id, the id exists so the throw will never happen
std::string FileDatabase::find_group_path(std::string id) throw(invalid_group_id_exception) {
	std::ifstream in(PATH + LIST_NEWSGROUP);
	std::string line;
	while(std::getline(in, line)) {
		std::string name(line, 0, line.find('_'));
		std::string i(line, line.find('_')+1, line.size());
		if (i == id) {
				return line;
		}
	}
	throw invalid_group_id_exception();
}

void FileDatabase::create_newsgroup(std::string name) throw(invalid_group_name_exception)
{
	// fetch group id from file
	std::ifstream in(PATH + GROUP_ID);
	int group_id;
	in >> group_id;

	std::ofstream f(PATH+LIST_NEWSGROUP, std::ifstream::in | std::ifstream::app);

	std::string path = PATH;
	path.append(name);
	path.append("_"+std::to_string(group_id));
	if( group_exists(name) || mkdir(path.c_str(), 0777) == -1) {
		throw invalid_group_name_exception();
	}
	f << name+"_"+std::to_string(group_id) << "\n";
	f.close();

	// increment group id and replace it in file
	++group_id;
	std::ofstream out(PATH + GROUP_ID);
	out << group_id;
}

void FileDatabase::delete_newsgroup(int group_id) throw(invalid_group_id_exception) {
	std::string id = std::to_string(group_id);
	std::string target = find_group_path(id);
	if (group_id_exists(id)) {
			std::string path = PATH + target;
			// remove folder
			remove(path.c_str());
			// also need to remove in our newsgroup list file
			std::ifstream in(PATH + LIST_NEWSGROUP);
			// create a temp file, write what we want and the rename it
			std::ofstream out(PATH + "temp.txt");
			std::string line;

			while (getline(in, line)) {
					// if not the removed group write to temp file
					if (line != target) {
							out << line << "\n";
					}
			}
			// remove the old file
			remove((PATH + LIST_NEWSGROUP).c_str());
			// replace with temp file and rename it
			rename((PATH + "temp.txt").c_str(), (PATH + LIST_NEWSGROUP).c_str());
	} else {
			throw invalid_group_id_exception();
	}
}

Article FileDatabase::read_article(int group_id, int article_id)
	throw(invalid_group_id_exception, invalid_article_id_exception) {
		std::string id = std::to_string(group_id);
		if (group_id_exists(id)) {
			struct dirent *pDirent;
			DIR *pDir;
			std::string path = PATH + find_group_path(id);
			// open folder of correct news group
			pDir = opendir(path.c_str());

			while ((pDirent = readdir(pDir)) != NULL) {
					// get the file name
					std::string article_path = pDirent->d_name;
					if (article_path != "." && article_path != ".." ) {
							// if file name equals the id we want to read
							if (article_path == std::to_string(article_id)) {
								// read from file + extract info
								std::ifstream in(path + "/" + article_path);
								std::string author;
								std::string title;
								std::string text;
								getline(in, title);
								getline(in, author);
								std::string word;
								while(in >> word) {
										text += word + " ";
								}
								// create an article
								return Article(title, author, text, atoi(article_path.c_str()));
							}
					}
			}
			closedir(pDir);
			throw invalid_article_id_exception();
		} else {
				throw invalid_group_id_exception();
		}

}


void FileDatabase::create_article(int group_id, std::string title, std::string author, std::string text)
	throw(invalid_group_id_exception){

	if (group_id_exists(std::to_string(group_id))) {

		// fetch current article id from file
		std::ifstream in(PATH + ARTICLE_ID);
		int article_id;
		in >> article_id;

		std::string article_path = std::to_string(article_id);

		// create a file in correct folder
		std::ofstream article(PATH + find_group_path(std::to_string(group_id)) + "/" + article_path);
		// insert author + newline + text
		article << title << "\n" << author << "\n" << text;

		// increment article id and replace it in file
		++article_id;
		std::ofstream out(PATH + ARTICLE_ID);
		out << article_id;

	} else {
		throw invalid_group_id_exception();
	}

}


void FileDatabase::delete_article(int group_id, int article_id)
	throw(invalid_group_id_exception, invalid_article_id_exception) {
		std::string id = std::to_string(group_id);
		if (group_id_exists(id)) {
				std::string article_path = std::to_string(article_id);
				std::string path = PATH + find_group_path(id) + "/" + article_path;
				// removes file, if not equal 0, means that the article id doesn't exists
				if (remove(path.c_str()) != 0) {
						throw invalid_article_id_exception();
				}
		} else {
				throw invalid_group_id_exception();
		}
}

std::vector<Article> FileDatabase::list_articles(int group_id) throw(invalid_group_id_exception){
	std::string id = std::to_string(group_id);
	if (group_id_exists(id)) {
			struct dirent *pDirent;
			DIR *pDir;
			std::string path = PATH + find_group_path(id);
			// open folder
			pDir = opendir(path.c_str());
			std::vector<Article> articles;

			while ((pDirent = readdir(pDir)) != NULL) {
					// iterate through folder, pDirent->d_name gives the file name
					std::string article_path = pDirent->d_name;
					// weird symbols to skip
					if (article_path != "." && article_path != "..") {
							// open article file + fetch information
							std::ifstream in(path + "/" + article_path);
							std::string author;
							std::string title;
							std::string text;
							getline(in, author);
							getline(in, title);
							std::string word;
							while(in >> word) {
									text += word + " ";
							}
							// creates an Article and push it to the vector
							articles.push_back(Article(title, author, text, atoi(article_path.c_str())));
					}
			}
			// close folder and sort the vector
			closedir(pDir);
			sort(articles.begin(), articles.end());
			return articles;
	} else {
			throw invalid_group_id_exception();
	}

}
