// Kenneth Kakie Program 3 Media Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Medialib.h"



int main()
{
    ifstream inFile;
    ofstream outFile, outErr;

    inFile.open("mediaList.txt");   // file where the media is read
    outFile.open("mediaReport.txt");// file where formatted output is output
    outErr.open("mediaError.txt");  // file where errors are output

    if (!inFile.good()) {
        cout << "badfile\n";
        return -1;
    }






    // phase 1 loads the mediaList array (basically, creates the library)

    // ======= Phase 1 Start =======

    vector<Media> mediaList;

    readMediaList(inFile, outErr, mediaList);

    inFile.close(); // closes mediaReport.txt

    // ======= Phase 1 End =======









    inFile.open("mediaCommands.txt"); // opens the file with user commands
    
    if (inFile.good()) {
        
    }
    else {
        outErr << "badfile\n";
        return -1;
    }





    // phase 2 takes in and runs the commands the user inputs (via text file)

    // ======= Phase 2 Start =======

    int rating = 0;
    vector<string> inputVect;
    string inp, tempString;
    char input;

    input = inFile.get();



    while (toupper(input) != 'Q') {

        switch (input) {
        case 'A':
            printAllMedia(inFile, outFile, outErr, mediaList);
            break;
        case 'M':
            printMovieList(inFile, outFile, outErr, mediaList);
            break;
        case 'B':
            printBookList(inFile, outFile, outErr, mediaList);
            break;
        case 'S':
            printSongList(inFile, outFile, outErr, mediaList);
            break;
        case 'T':
            printTotals(outFile);
            char trash;
            trash = inFile.get(); // CLEARS THE ISTREAM OF THE '\n' CHARACTER OTHERWISE THE NEXT get() PULLS '\n' INSTEAD OF A, B, S, etc.
            break;
        case 'N':
            addNewMedia(inFile, outFile, outErr, mediaList);
            break;
        default:
            outErr << "\nBad input.\n";
        }
        
        input = inFile.get(); // get the user's next input letter
    }

    // ======= Phase 2 End =======
    



    inFile.close();
    outFile.close();
    outErr.close();
    return 0;
}
