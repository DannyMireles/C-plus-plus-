#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "functions.h"

using namespace std;

/*  Function readPrefs
 *  fileName: path to the file containing preferences
 *  ngames:   number of games 
 *  prefs:    array of integers created with MAX_NB_GAMES=200
 *            positions. 
 *  Return value: none
 *  Throws: runtime_error if file cannot be opened
 */
void readPrefs(string fileName, int ngames, int prefs[]) {
	ifstream fin(fileName);
    if (!fin.is_open()) {
        throw runtime_error("Invalid titles file.");
    }
	//initially assign all games with a rating of 0
    for (int i = 0; i < ngames; i++) {
		prefs[i] = 0;
	}

    // if file can be opened
    if (fin.is_open()) {
		int validLines = 0;
        int gameid;
		int rating;
        // read till end of file, reading the game id and game rating
        while (!fin.eof()) {
			fin >> gameid;
			fin >> rating;
            if(gameid >= 0 && gameid < ngames && rating >= 0 && rating <= 5) {
                validLines++; 
                prefs[gameid] = rating; 
                }
            }
        }
	}


/*  Function readPlan
 *  fileName: path to the file containing the plan
 *  plan:    array of integers created with 366 positions
 *  Return value: none
 *  Throws: runtime_error if file cannot be opened
 */
void readPlan(string fileName, int plan[]) {
	ifstream fin;
	fin.open(fileName);
	if(!fin.is_open()) {
		throw runtime_error("Invalid plan title.");
	}
	while(!fin.eof()) {
		int day;
		int id;
		fin >> day;
		fin >> id;
		plan[day] = id;
	}
}
			
/*  Function computeFunLevel
 *  start:  first day of the vacation (1 <= start <= 365)
 *  duration: number of vacation days (duration >= 1)
 *  prefs: prefs[k] indicates the rating specified for game k
 *  plan: array with 366 positions with the sequence of games 
 *        to be played over the year. In other words, 
 *        plan[k] indicates the game planned for day k (1 <= k <= 365) 
 *  Return value: Sum of the ratings for games played during the vacation period.
 *  Throws: invalid_argument exception if duration exceeds the number of days remaining in the year
 */
int computeFunLevel(int start, int duration, int prefs[], int plan[]) {
	if (start + duration > 366) { //if start plus duration is more than the number of days
		throw invalid_argument("Invalid argument");
	}
	int funLevel = 0;
	for (int i = start; i < start + duration; i++) { //sum all fun level
		funLevel = funLevel + prefs[plan[i]];
	}
	return funLevel; //return fun level
}

/*  Function findBestVacation
 *  duration: number of vacation days
 *  prefs: prefs[k] indicates the rate specified for game k
 *  plan: array with 366 positions with the sequence of games 
 *        to be played over the year. In other words, 
 *        plan[k] indicates the game planned for day k (1 <= k <= 365) 
 *  Return value: the earliest start date that results in the highest fun level.
 */
int findBestVacation(int duration, int prefs[], int plan[]) {
	int highestFun = 0;
	int maxFun = 0;
	int funLevel = 0;
	try {
		if (duration < 1 || duration > 365) {
			throw duration;
		}
		for (int i = 1; i <= 366 - duration; i++) {
			if (computeFunLevel(i, duration, prefs, plan) > 0) {
				funLevel = computeFunLevel(i, duration, prefs, plan);
			}
			if (funLevel > highestFun) {
				highestFun = funLevel;
				maxFun = i;
			}
		}
	}
	catch (int ex) {
		throw invalid_argument ("Invalid duration time");
	}
	return maxFun;
}