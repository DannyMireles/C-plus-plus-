#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "provided.h"

using std::ifstream;
using std::string, std::getline;
using std::cout, std::endl;
using std::runtime_error;

/*  Function readGameTitles
 *  fileName: path to the file containing titles
 *  ngames: number of games cousins are bringing to the house
 *  gameTitles: array where row i stores the title for game i
 *  Return value: none
 *  Throws runtime_error if file cannot be opened
 */
void readGameTitles(string fileName, int ngames, string  gameTitles[]) {
    ifstream fin(fileName);
    if (!fin.is_open()) {  // error in opening the file
        throw runtime_error("Invalid titles file.");
    }

    for (int i = 0; i < ngames; i++) {
        gameTitles[i] = "Unknown Title";
    }

    int gameid;
    string title;
    while (!fin.eof()) {  // while not at the end of the file
        fin >> gameid;
        if (fin.good()) {  // no error reading integer game
            // read title as the rest of the line
            if (gameid >= 0 && gameid < MAX_NB_GAMES) {
                // valid game
                // consume space
                char space;
                fin >> std::noskipws >> space;
                getline(fin, gameTitles[gameid]);
            } else {
                // ignoring invalid gameid, just consume title
                getline(fin, title);
            }
        } else {
            // read the rest of the line and ignore it
            fin.clear();
            getline(fin, title);
        }
    }
}


/*  Function printGamesPlayedInVacation
 *  start:  first day of the vacation (1 <= start < 365)
 *  duration: number of vacation days
 *  plan: array with 366 positions with the sequence of games 
 *        to be played over the year. In other words, 
 *        plan[k] indicates the game planned for day k (1 <= k <= 365) 
 *  gameTitles: array with game titles
 *  ngames: number of games
 *  Return value: none. 
 */
void printGamesPlayedInVacation(int start, int duration, int plan[],
                                string gameTitles[], int ngames) {
    bool title_included[MAX_NB_GAMES];
    for (int i = 0; i < ngames; i++) {
        title_included[i] = false;
    }
    for (int i = start; i < start + duration && i <= 365; i++) {
        int gameid = plan[i];
        if (!title_included[gameid]) {
            cout << gameTitles[gameid] << endl;
            title_included[gameid] = true;
        }
    }
}
