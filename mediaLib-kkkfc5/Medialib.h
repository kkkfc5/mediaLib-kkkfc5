#pragma once
#ifndef MEDIALIB_H
#define MEDIALIB_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;




class Media
{
private:
	char type = '\t';
	string title = "\t";
	string keyName = "\t";
	int rating = 0;
	string genre = "\t";
	int length = 0;
	int yearReleased = 0000;

	int number = 0; // number in library


public:

	//constructors
	Media();
	Media(char typ, string titl, string keyR, int rati, string genr, int leng, int year);

	// accessors
	char getType() { return type; }
	string getTitle() { return title; }
	string getKeyName() { return keyName; }
	int getRating() { return rating; }
	string getGenre() { return genre; }
	int getLength() { return length; }
	int getYearReleased() { return yearReleased; }
	int getNumber() { return number; }

	// mutators
	void setType(char t) { type = t; }
	void setTitle(string t) { title = t; }
	void setKeyName(string k) { keyName = k; }
	void setRating(int r) { rating = r; }
	void setGenre(string g) { genre = g; }
	void setLength(int l) { length = l; }
	void setYearReleased(int y) { yearReleased = y; }
	void setNumber(int o) { number = o; }


	// static variables  
	static int totalMovies;
	static int totalBooks;
	static int totalSongs;

};





//PRE: Files are open in main & accessible
//POST:
//• Reads the data from csv file and loads the objects into a vector<Media>
//• Produces an error report of any records that have errors
int readMediaList(istream& i, ostream& o, vector<Media>& m);




/*
PRE: assumes media list is loaded with valid values and the first
character in the input stream has been read (A,M,B,S)
POST: Each of these functions will check to see if there is additional input in the record
		|  following the A,M,B,S characters (a comma followed by an integer) It will validate
		|  this additional input (the number is numeric and between the values of 1 and 10 inclusive).
Errors will be printed to the error file.
• If a rating is present, print the list for ratings greater than or equal
to the value provided
• If a rating is not present, it will print all entries in the list
*/
void printAllMedia(istream& in, ostream& out, ostream& outErr, vector <Media>& m);
void printMovieList(istream& in, ostream& out, ostream& outErr, vector <Media>& m);
void printBookList(istream& in, ostream& out, ostream& outErr, vector <Media>& m);
void printSongList(istream& in, ostream& out, ostream& outErr, vector <Media>& m);



/*
PRE: static array is initialized to 0
POST: Prints the total count of movies, books and songs in your
library
*/
void printTotals(ostream& out);




/*
PRE: assumes media list is loaded with valid values and the first character in the input stream has been read (N)
POST: It will read the input string and separate all values (as reading from csv file) into a vector<string> row.
Row[0] = empty (the N has been read and a comma is in the buffer)
Row[1][1] = media type (character, verify M, S, B)
Row[2] = title (string, no verification)
Row[3] = name (string, no verification)
Row[4] = rating (integer, verify numeric & between 1-10 inclusive)
Row[5] = genre (string, no verification)
Row [6] = length (integer, verify numeric)
Row[7] = year (integer, verify numeric & between 1500-2023 inclusive)
NOTE: there may be more information in the input file – you can
ignore this for now
Once all input is gathered, and record has no errors, media record
onto the vector and update the counts
*/
void addNewMedia(istream& inCommands, ostream& out, ostream& outErr, vector<Media>& m);





// PRE: static array is initialized to 0
// POST: Prints the total count of movies, books and songs in your library.
void printTotals(ostream& out);


#endif