#include "../includes_usr/fileIO.h"

#include <fstream>
#include <string>
#include "../includes_usr/constants.h"

using namespace std;
book bookObject;
patron patronObject;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	books.clear();
	std::string line;
	fstream myfile;
	string readLine;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	else{
		getline(myfile, line);
		if(line.length() == 0) {
			return NO_BOOKS_IN_LIBRARY;
		}
		else {
			int comma = line.find(',');
			readLine = line.substr(0,comma);
			bookObject.book_id = std::stoi(readLine);
			line = line.substr(comma +1);
			comma = line.find(',');
			readLine = line.substr(0,comma);
			bookObject.title = readLine;
			line = line.substr(comma +1);
			comma = line.find(',');
			readLine = line.substr(0,comma);
			bookObject.author = readLine;
			line = line.substr(comma +1);
			comma = line.find(',');
			readLine = line.substr(0,comma);
			bookObject.state = IN;
			line = line.substr(comma +1);
			comma = line.find(',');
			readLine= line.substr(0,comma);
			bookObject.loaned_to_patron_id = std::stoi(readLine);
			books.push_back(bookObject);

			while (!myfile.eof()){
				getline(myfile, line);
				if(line.length() != 0) {
					comma = line.find(',');
					readLine = line.substr(0,comma);
					bookObject.book_id = std::stoi(readLine);
					line = line.substr(comma +1);
					comma = line.find(',');
					readLine = line.substr(0,comma);
					bookObject.title = readLine;
					line = line.substr(comma +1);
					comma = line.find(',');
					readLine = line.substr(0,comma);
					bookObject.author = readLine;
					line = line.substr(comma +1);
					comma = line.find(',');
					readLine = line.substr(0,comma);
					bookObject.state = IN;
					line = line.substr(comma +1);
					comma = line.find(',');
					readLine= line.substr(0,comma);
					bookObject.loaned_to_patron_id = std::stoi(readLine);
					books.push_back(bookObject);
				}
			}
		}
	}
	myfile.close();
	return SUCCESS;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	book bookObject;
	std::string line;
	ofstream myfile;
	myfile.open(filename);
	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	else {
		if (books.size() == 0) {
			return NO_BOOKS_IN_LIBRARY;
		}
		else {
			int lengOfVector = books.size();
			for (int i = 0; i < lengOfVector; i++){
				bookObject = books[i];
				line = std::to_string(bookObject.book_id);
				line = line + "," + bookObject.title;
				line = line + "," + bookObject.author + ",";
				if (bookObject.state == UNKNOWN){
					line = line + "0,";
				}
				else if (bookObject.state == IN){
					line = line + "1,";
				}
				else{
					line = line + "2,";
				}
				line = line + std::to_string(bookObject.loaned_to_patron_id) + "\n";
				myfile << line;
			}
		}
	}
	myfile.close();
	return SUCCESS;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	std::string line;
	fstream myfile;
	string readLine;
	patrons.clear();
	myfile.open(filename);
	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	else{
		getline(myfile, line);
		if(line.length() == 0) {
			return NO_PATRONS_IN_LIBRARY;
		}
		else {
			int comma = line.find(',');
			readLine = line.substr(0,comma);
			patronObject.patron_id = std::stoi(readLine);
			line = line.substr(comma +1);
			comma = line.find(',');
			readLine = line.substr(0,comma);
			patronObject.name = readLine;
			line = line.substr(comma +1);
			comma = line.find(',');
			readLine = line.substr(0,comma);
			patronObject.number_books_checked_out = std::stoi(readLine);
			patrons.push_back(patronObject);
			while (!myfile.eof()){
				getline(myfile, line);
				if(line.length() != 0) {
					comma = line.find(',');
					readLine = line.substr(0,comma);
					patronObject.patron_id = std::stoi(readLine);
					line = line.substr(comma +1);
					comma = line.find(',');
					readLine = line.substr(0,comma);
					patronObject.name = readLine;
					line = line.substr(comma +1);
					comma = line.find(',');
					readLine = line.substr(0,comma);
					patronObject.number_books_checked_out = std::stoi(readLine);
					patrons.push_back(patronObject);
				}
		}
		}
	}
	myfile.close();
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	patron patronObject;
	std::string line;
	ofstream myfile;
	myfile.open(filename);

	if (!myfile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	else {
		if (patrons.size() == 0) {
			return NO_PATRONS_IN_LIBRARY;
		}
		else{
			int lengOfVector = patrons.size();
			for (int i = 0; i < lengOfVector; i++){
				patronObject = patrons[i];
				line = std::to_string(patronObject.patron_id);
				line = line + "," + patronObject.name + ",";
				line = line + std::to_string(patronObject.number_books_checked_out) +"\n";
				myfile << line;
			}
	myfile.close();
	return SUCCESS;
	}
}
}
