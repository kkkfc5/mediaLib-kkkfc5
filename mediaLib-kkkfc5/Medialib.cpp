#include "Medialib.h"


int Media::totalMovies;
int Media::totalBooks;
int Media::totalSongs;


Media::Media() {
    type = '\t';
    title = "\t";
    rating = 0;
    genre = "\t";
    length = 0;
    yearReleased = 0000;
}


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
void addNewMedia(istream& inCommands, ostream& out, ostream& outErr, vector<Media>& m) {
    int iteration = m[m.size() - 1].getNumber() + 1; // the number this record will be in the last record's number + 1
    
    bool goodRec = true;
    Media tempMedia;

    string inRec;

    getline(inCommands, inRec);


    if (inRec[0] == ',') { // if user inputted somehting other than just the choice char
        inRec.erase(inRec.begin()); // erase the ','

        stringstream inSS(inRec); // creates SS using input.

        vector<string> row;
        string tempString;

        string trash = "\0";
        row.push_back(trash); // because i dont want to go back and -1 to each index.

        while (getline(inSS, tempString, ',')) { // separates ss on ,
            row.push_back(tempString); // push each element of input onto a string vector
        }


        for (int i = 0; i < 1; i++) { // needs to be in a for loop so it can break once the first error is reached
            try {
                if (row[1][0] != 'M' && row[1][0] != 'S' && row[1][0] != 'B') { // Row[1][at char 0] = media type (character, verify M, S, B)
                    outErr << "\nUnable to process command. Type: " << row[1][0] << " is invalid.\n\n";
                    goodRec = false;
                    break;
                }
            }
            catch (logic_error) {
                outErr << "\nUnable to process command. \n\n";
                goodRec = false;
                break;
            }



            try {
                if (stoi(row[4]) > 10 || stoi(row[4]) < 1) {// Row[4] = rating (integer, verify numeric & between 1-10 inclusive)
                    outErr << "\nUnable to process command. There was an invalid value entered for rating: " << row[2] << "\n\n";
                    goodRec = false;
                    break;
                }
            }
            catch (logic_error) { // if it can't stoi
                outErr << "\nUnable to process command. There was an invalid value entered for rating: " << row[2] << "\n\n";
                goodRec = false;
                break;
            }



            try {
                if (stoi(row[6]) < 0) { // Row [6] = length (integer, verify numeric)
                    outErr << "\nUnable to process command. There was an invalid value entered for item: " << row[2] << "\n\n";
                    goodRec = false;
                    break;
                }
            }
            catch (logic_error) {
                outErr << "\nUnable to process command. There was an invalid value entered for item: " << row[2] << "\n\n";
                goodRec = false;
                break;
            }



            try {
                if (stoi(row[7]) < 1500 || stoi(row[7]) > 2023) {  // Row[7] = year (integer, verify numeric & between 1500-2023 inclusive)
                    outErr << "\nUnable to process command. There was an invalid value entered for year: " << row[2] << "\n\n";
                    goodRec = false;
                    break;
                }
            }
            catch (logic_error) {
                outErr << "\nUnable to process command. There was an invalid value entered for year: " << row[2] << "\n\n";
                goodRec = false;
                break;
            }
        } // end for


        // error checks ^



        if (goodRec) {

            //     ----- null ------      // Row[0] = empty (the N has been read and a comma is in the buffer)
            tempMedia.setType(row[1][0]); // Row[1][0] = media type (character, verify M, S, B)
            tempMedia.setTitle(row[2]);   // Row[2] = title (string, no verification)
            tempMedia.setKeyName(row[3]); // Row[3] = name (string, no verification)
            tempMedia.setRating(stoi(row[4])); // Row[4] = rating (integer, verify numeric & between 1-10 inclusive)
            tempMedia.setGenre(row[5]);        // Row[5] = genre (string, no verification)
            tempMedia.setLength(stoi(row[6])); // Row [6] = length (integer, verify numeric)
            tempMedia.setYearReleased(stoi(row[7])); // Row[7] = year (integer, verify numeric & between 1500-2023 inclusive)

            tempMedia.setNumber(iteration); // set the number to be the iteration (how many media have been created)
            iteration++;

            switch (tempMedia.getType()) { // increments total amount of the media types. 
            case 'M':
                Media::totalMovies++;
                break;
            case 'B':
                Media::totalBooks++;
                break;
            case 'S':
                Media::totalSongs++;
                break;
            }
            // NOTE :: Doesn't need default, because previous code checks type.



            m.push_back(tempMedia);


            out << "\n\n" << tempMedia.getTitle() << " has been added to your list\n\n";
        }
    }
}





//PRE: Files are open in main & accessible
//POST:
//• Reads the data from csv file and loads the objects into a vector<Media>
//• Produces an error report of any records that have errors

int readMediaList(istream& i, ostream& o, vector<Media>& m) {
    int iteration = 1;// will be used to give records their number in the library
    Media tempMedia;
    vector<string> row;
    string inRec, tempString;
    bool endLoop = false;

    getline(i, inRec); // reading the record from the file, one line at a time
    
    while (i.good() && !endLoop) { // for every record in the input file

        bool goodRec = true; // flag used for if the record doesn't have an error in it

        stringstream inSS(inRec); // create string stream
        
        row.clear();

        string trash = "\0";
        row.push_back(trash); // because i dont want to go back and -1 to each index.

        while (getline(inSS, tempString, ',')) { // separates ss on ,
            row.push_back(tempString); // push each element onto a string vector
        }




        if (row[1][0] == 'Q') { // IF THE INPUT FILE WANTS TO QUIT:
            endLoop = true;    // RAISE THE FLAG
        }

        if (!endLoop) { // A GUARD TO MAKE SURE IT DOESNT RUN 'Q' AS IF IT IS AN ACTUAL COMMAND AND PRODUCE AN ERROR

            
            
            // error checks v 

            for (int i = 0; i < 1; i++) { // needs to be in a for loop so it can break once the first error is reached
                try {
                    if (row[1][0] != 'M' && row[1][0] != 'S' && row[1][0] != 'B') { // Row[1][at char 0] = media type (character, verify M, S, B)
                        o << "ERROR: " << inRec;
                        o << "\nThere was an invalid value entered for media type.\n\n";
                        goodRec = false;
                        break;
                    }
                }
                catch (logic_error) {
                    o << "ERROR: " << inRec;
                    o << "\nPrevious record had an error.\n\n";
                    goodRec = false;
                    break;
                }



                try {
                    if (stoi(row[4]) > 10 || stoi(row[4]) < 1) {// Row[4] = rating (integer, verify numeric & between 1-10 inclusive)
                        o << "ERROR: " << inRec;
                        o << "\nThere was an invalid value entered for the rating.\n\n";
                        goodRec = false;
                        break;
                    }
                }
                catch (logic_error) { // if it can't stoi
                    o << "ERROR: " << inRec;
                    o << "\nPrevious record has an invalid stoi argument error.\n\n";
                    goodRec = false;
                    break;
                }



                try {
                    if (stoi(row[6]) < 0) { // Row [6] = length (integer, verify numeric)
                        o << "ERROR: " << inRec;
                        o << "\nThere was an invalid value entered for the length.\n\n";
                        goodRec = false;
                        break;
                    }
                }
                catch (logic_error) {
                    o << "ERROR: " << inRec;
                    o << "\nPrevious record has an invalid stoi argument error.\n\n";
                    goodRec = false;
                    break;
                }



                try {
                    if (stoi(row[7]) < 1500 || stoi(row[7]) > 2023) {  // Row[7] = year (integer, verify numeric & between 1500-2023 inclusive)
                        o << "ERROR: " << inRec;
                        o << "\nThere was an invalid value entered for the year.\n\n";
                        goodRec = false;
                        break;
                    }
                }
                catch (logic_error) {
                    o << "ERROR: " << inRec;
                    o << "\nPrevious record has an invalid stoi argument error.\n\n";

                    goodRec = false;
                    break;
                }
            } // end for


            // error checks ^



            if (goodRec) {


                //     ----- null ------      // Row[0] = empty (the N has been read and a comma is in the buffer)
                tempMedia.setType(row[1][0]); // Row[1][0] = media type (character, verify M, S, B)
                tempMedia.setTitle(row[2]);   // Row[2] = title (string, no verification)
                tempMedia.setKeyName(row[3]); // Row[3] = name (string, no verification)
                tempMedia.setRating(stoi(row[4])); // Row[4] = rating (integer, verify numeric & between 1-10 inclusive)
                tempMedia.setGenre(row[5]);        // Row[5] = genre (string, no verification)
                tempMedia.setLength(stoi(row[6])); // Row [6] = length (integer, verify numeric)
                tempMedia.setYearReleased(stoi(row[7])); // Row[7] = year (integer, verify numeric & between 1500-2023 inclusive)

                tempMedia.setNumber(iteration); // set the number to be the iteration (how many media have been created)
                iteration++;

                switch (tempMedia.getType()) { // increments total amount of the media types. 
                case 'M':
                    Media::totalMovies++;
                    break;
                case 'B':
                    Media::totalBooks++;
                    break;
                case 'S':
                    Media::totalSongs++;
                    break;
                }

                m.push_back(tempMedia);
            }

            getline(i, inRec); // get next input record

        } // end if !endLoop
    } // end while
    return 0;
}



void printHeader(ostream& out, bool printed, char type, char bound) {

    if (!printed) {
        out << "\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        switch (type) {
        case 'A':
            out << right << setw(29) << "YOUR MEDIA LIST\n\n";
            break;
        case 'M':
            out << right << setw(29) << "YOUR MOVIE LIST\n\n";
            break;
        case 'B':
            out << right << setw(29) << "YOUR BOOK LIST\n\n";
            break;
        case 'S':
            out << right << setw(29) << "YOUR SONG LIST\n\n";
            break;
        case 'T':
            out << right << setw(29) << "YOUR MEDIA LIBRARY\n";
            break;
        }


        if (type != 'T') {

            out << "#" << setw(12) << " " << "TITLE" << setw(31) << "YEAR" << setw(10) << "RATING";

            if (bound != '\0') { // if type or genre needs to be printed after
                switch (bound) {
                case 'T':
                    out << right << setw(6) << "TYPE";
                    break;
                case 'G':
                    out << right << setw(9) << "GENRE";
                    break;
                }
            } // end if :: bound
            out << "\n";
        } 
        else { // IF TYPE IS T, THEN PRINT THE TOTAL
            out << "#   TYPE\n";
            out << left << setw(4) << Media::totalMovies << "Movies\n";
            out << left << setw(4) << Media::totalBooks << "Books\n";
            out << left << setw(4) << Media::totalSongs << "Songs\n";
            out << left << setw(4) << (Media::totalMovies + Media::totalBooks + Media::totalSongs) << "Items\n\n\n";
        } // end if :: type
    }
}

// make order a static variable 
// ,make the other static varaible required in rubric
// rename functions and change arguments 









// PRINT FUNCTS BELOW ================================================================================









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
void printAllMedia(istream& in, ostream& out, ostream& outErr, vector <Media>& m) {

    bool headerPrinted = false;

    string input; // te user's input after the type. ex: ",8\n" (a newline char is at the end)

    getline(in, input); // if the user inputted just the type (ex. 'M'), then input will be just '\n'

    if (input[0] == ',') { // if user inputter somehting other than just the chaice char
        input.erase(input.begin()); // erase the ','

        try { //check if input is numeric
            int intFilter = stoi(input); // if this doesnt throw error, the if-else directly under this line runs

            if (intFilter < 1 || intFilter > 10) { // if filter isn't proper, print error
                outErr << "\nUnable to process command. The rating of: " << intFilter << " is invalid\n\n";
            } else {
                for (int i = 0; i < m.size(); i++) {
                    if (m[i].getRating() >= intFilter) { //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  if the rating == user's input
                        
                        printHeader(out, headerPrinted, 'A', 'T'); // passing in all for print type, type for bound
                        headerPrinted = true;

                        out << left << setw(3) << m[i].getNumber();
                        out << left << setw(42) << m[i].getTitle();
                        out << left << setw(9) << m[i].getYearReleased();
                        out << right << setw(3) << m[i].getRating();
                        // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                        out << right << setw(7) << m[i].getType(); // prints type as well
                        out << "\n";
                    }
                } // end for
            } // end if
        } // end try
        catch (logic_error) { //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  if user inputed a string instead
            string strFilter = input; 
            bool found = false;
            
            for (int i = 0; i < m.size(); i++) {
                if (m[i].getGenre() == strFilter) { // if the genre == user's input
                    found = true;

                    printHeader(out, headerPrinted, 'A', 'G'); // passing in all for print type, genre for bound
                    headerPrinted = true;

                    out << left << setw(3) << m[i].getNumber();
                    out << left << setw(42) << m[i].getTitle();
                    out << left << setw(9) << m[i].getYearReleased();
                    out << right << setw(3) << m[i].getRating();
                    // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                    out << right << setw(11) << m[i].getGenre(); // prints genre as well
                    out << "\n";
                }
            }
            if (!found) {
                outErr << "\nUnable to process command.  There was not item of genre: " << strFilter << " in your list.\n\n";
            }
        }
    }
    else { //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  IF THERE IS NO SECONDARY INPUT FROM THE USER:
        for (int i = 0; i < m.size(); i++) {

            printHeader(out, headerPrinted, 'A', 'T'); // passing in all for print type, null for bound
            headerPrinted = true;

            out << left << setw(3) << m[i].getNumber();
            out << left << setw(42) << m[i].getTitle();
            out << left << setw(9) << m[i].getYearReleased();
            out << right << setw(3) << m[i].getRating();
            // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
            out << right << setw(7) << m[i].getType(); // prints genre as well
            out << "\n";
        }
    }
} // end func




void printMovieList(istream& in, ostream& out, ostream& outErr, vector <Media>& m) {
    
    bool headerPrinted = false;
    
    string input; // the user's input after the type. ex: ",8\n" (a newline char is at the end)

    getline(in, input); // if the user inputted just the type (ex. 'M'), then input will be just '\n'


    if (input[0] == ',') { // if user inputter somehting other than just the choice char
        input.erase(input.begin()); // erase the ','

        try { //check if input is numeric

            int intFilter = stoi(input); // if this doesnt throw error, the if-else directly under this line runs

            if (intFilter < 1 || intFilter > 10) { // if filter isn't proper, print error
                outErr << "\nUnable to process command. The rating of: " << intFilter << " is invalid\n\n";
            }
            else {
                for (int i = 0; i < m.size(); i++) {
                    if (m[i].getRating() >= intFilter && m[i].getType() == 'M') { // if the rating == user's input  &&  if type == a movie
                        printHeader(out, headerPrinted, 'M', '\0'); // passing in movie for print type, none for bound
                        headerPrinted = true;

                        out << left << setw(3) << m[i].getNumber();
                        out << left << setw(42) << m[i].getTitle();
                        out << left << setw(9) << m[i].getYearReleased();
                        out << right << setw(3) << m[i].getRating();
                        // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                        out << "\n";
                    }
                } // end for
            } // end if
        } // end try
        catch (logic_error) { // if user inputed a string instead
            string strFilter = input;
            bool found = false;

            for (int i = 0; i < m.size(); i++) {
                if (m[i].getGenre() == strFilter && m[i].getType() == 'M') { // if the genre == user's input  &&  if type == a movie
                    found = true;
                    
                    printHeader(out, headerPrinted, 'M', 'G'); // passing in movie for print type, genre for bound
                    headerPrinted = true;

                    out << left << setw(3) << m[i].getNumber();
                    out << left << setw(42) << m[i].getTitle();
                    out << left << setw(9) << m[i].getYearReleased();
                    out << right << setw(3) << m[i].getRating();
                    // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                    out << right << setw(11) << m[i].getGenre(); // prints genre as well
                    out << "\n";
                }
            }
            if (!found) {
                outErr << "\nUnable to process command.  There was not item of genre: " << strFilter << " in your list.\n\n";
            }
        }
    }
    else { // IF THERE IS NO SECONDARY INPUT FROM THE USER:
        for (int i = 0; i < m.size(); i++) {
            if (m[i].getType() == 'M') { // if the medaiList at i's type == movie
                printHeader(out, headerPrinted, 'M', '\0'); // passing in movie for print type, none for bound
                headerPrinted = true;

                out << left << setw(3) << m[i].getNumber();
                out << left << setw(42) << m[i].getTitle();
                out << left << setw(9) << m[i].getYearReleased();
                out << right << setw(3) << m[i].getRating();
                // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                out << "\n";
            }
        }
    }
}
void printBookList(istream& in, ostream& out, ostream& outErr, vector <Media>& m) {
    
    bool headerPrinted = false;
    
    string input; // the user's input after the type. ex: ",8\n" (a newline char is at the end)

    getline(in, input); // if the user inputted just the type (ex. 'M'), then input will be just '\n'


    if (input[0] == ',') { // if user inputted somehting other than just the choice char
        input.erase(input.begin()); // erase the ','

        try { //check if input is numeric

            int intFilter = stoi(input); //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ if this doesnt throw error, the if-else directly under this line runs

            if (intFilter < 1 || intFilter > 10) { // if filter isn't proper, print error
                outErr << "\nUnable to process command. The rating of: " << intFilter << " is invalid\n\n";
            }
            else {
                for (int i = 0; i < m.size(); i++) {
                    if (m[i].getRating() >= intFilter && m[i].getType() == 'B') { // if the rating == user's input  &&  if type == a book
                        printHeader(out, headerPrinted, 'B', '\0'); // passing in book for print type, none for bound
                        headerPrinted = true;

                        out << left << setw(3) << m[i].getNumber();
                        out << left << setw(42) << m[i].getTitle();
                        out << left << setw(9) << m[i].getYearReleased();
                        out << right << setw(3) << m[i].getRating();
                        // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                        out << "\n";
                    }
                } // end for
            } // end if
        } // end try
        catch (logic_error) { // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ IF USER INPUTTED A STRING INSTEAD
            string strFilter = input;
            bool found = false;

            for (int i = 0; i < m.size(); i++) {
                if (m[i].getGenre() == strFilter && m[i].getType() == 'B') { // if the genre == user's input  &&  if type == a book
                    found = true;

                    printHeader(out, headerPrinted, 'B', 'G'); // passing in book for print type, genre for bound
                    headerPrinted = true;

                    out << left << setw(3) << m[i].getNumber();
                    out << left << setw(42) << m[i].getTitle();
                    out << left << setw(9) << m[i].getYearReleased();
                    out << right << setw(3) << m[i].getRating();
                    // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                    out << right << setw(11) << m[i].getGenre(); // prints genre as well
                    out << "\n";
                }
            }
            if (!found) {
                outErr << "\nUnable to process command.  There was not item of genre: " << strFilter << " in your list.\n\n";
            }
        }
    }
    else { // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ IF THERE IS NO SECONDARY INPUT FROM THE USER:   
        
        for (int i = 0; i < m.size(); i++) {
            if (m[i].getType() == 'B') { // if the medaiList at i's type == book
                printHeader(out, headerPrinted, 'B', '\0'); // passing in book for print type, none for bound
                headerPrinted = true;

                out << left << setw(3) << m[i].getNumber();
                out << left << setw(42) << m[i].getTitle();
                out << left << setw(9) << m[i].getYearReleased();
                out << right << setw(3) << m[i].getRating();
                // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                out << "\n";
            }
        }
    }
}
void printSongList(istream& in, ostream& out, ostream& outErr, vector <Media>& m) {
    
    bool headerPrinted = false;

    string input; // the user's input after the type. ex: ",8\n" (a newline char is at the end)

    getline(in, input); // if the user inputted just the type (ex. 'M'), then input will be just '\n'


    if (input[0] == ',') { // if user inputted somehting other than just the choice char
        input.erase(input.begin()); // erase the ','

        try { //check if input is numeric

            int intFilter = stoi(input); //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ if this doesnt throw error, the if-else directly under this line runs

            if (intFilter < 1 || intFilter > 10) { // if filter isn't proper, print error
                outErr << "\nUnable to process command. The rating of: " << intFilter << " is invalid\n\n";
            }
            else {
                for (int i = 0; i < m.size(); i++) {
                    if (m[i].getRating() >= intFilter && m[i].getType() == 'S') { // if the rating == user's input  &&  if type == a song
                        printHeader(out, headerPrinted, 'S', '\0'); // passing in song for print type, none for bound
                        headerPrinted = true;

                        out << left << setw(3) << m[i].getNumber();
                        out << left << setw(42) << m[i].getTitle();
                        out << left << setw(9) << m[i].getYearReleased();
                        out << right << setw(3) << m[i].getRating();
                        // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                        out << "\n";
                    }
                } // end for
            } // end if
        } // end try
        catch (logic_error) { // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ IF USER INPUTTED A STRING INSTEAD
            string strFilter = input;
            bool found = false;

            for (int i = 0; i < m.size(); i++) {
                if (m[i].getGenre() == strFilter && m[i].getType() == 'S') { // if the genre == user's input  &&  if type == a song
                    found = true;

                    printHeader(out, headerPrinted, 'S', 'G'); // passing in song for print type, genre for bound
                    headerPrinted = true;

                    out << left << setw(3) << m[i].getNumber();
                    out << left << setw(42) << m[i].getTitle();
                    out << left << setw(9) << m[i].getYearReleased();
                    out << right << setw(3) << m[i].getRating();
                    // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                    out << right << setw(11) << m[i].getGenre(); // prints genre as well
                    out << "\n";
                }
            }
            if (!found) {
                outErr << "\nUnable to process command.  There was not item of genre: " << strFilter << " in your list.\n\n";
            }
        }
    }
    else { // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ IF THERE IS NO SECONDARY INPUT FROM THE USER:   

        for (int i = 0; i < m.size(); i++) {
            if (m[i].getType() == 'S') { // if the medaiList at i's type == song
                printHeader(out, headerPrinted, 'S', '\0'); // passing in song for print type, genre for bound
                headerPrinted = true;

                out << left << setw(3) << m[i].getNumber();
                out << left << setw(42) << m[i].getTitle();
                out << left << setw(9) << m[i].getYearReleased();
                out << right << setw(3) << m[i].getRating();
                // \\ // \\ // \\ // \\ \\ // \\ // \\ // 
                out << "\n";
            }
        }
    }
}





void printTotals(ostream& out) {
    bool printed = false; // placeholder; only used for passing into function.
    printHeader(out, printed, 'T', '\0');
}




