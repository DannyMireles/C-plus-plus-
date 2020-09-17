#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

 /*  Function readPrefs
 *  fileName: path to the file containing preferences
 *  ngames:   number of games 
 *  prefs:    array of integers created with MAX_NB_GAMES=200
 *            positions. 
 *  Return value: none
 *  Throws: runtime_error if file cannot be opened
 */
void readPrefs(
	std::string fileName,
    int ngames,
    int prefs[]);


/*  Function readPlan
 *  fileName: path to the file containing the plan
 *  plan:    array of integers created with 366 positions
 *  Return value: none
 *  Throws: runtime_error if file cannot be opened
 */
void readPlan(
	std::string fileName,
    int plan[]);


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
int computeFunLevel(int start, int duration, int prefs[], int plan[]);
int computeFunLevel(
	int start,
	int duration,
	int prefs[],
	int plan[]);
	

/*  Function findBestVacation
 *  duration: number of vacation days
 *  prefs: prefs[k] indicates the rate specified for game k
 *  plan: array with 366 positions with the sequence of games 
 *        to be played over the year. In other words, 
 *        plan[k] indicates the game planned for day k (1 <= k <= 365) 
 *  Return value: the earliest start date that results in the highest fun level.
 */
int findBestVacation(
	int duration,
	int prefs[],
	int plan[]);







#endif
