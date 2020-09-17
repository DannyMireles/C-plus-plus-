#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"
#include "provided.h"

using namespace std;

int main () {
	int ngames;
	int duration;
	string titlesFile;
	string planFile;
	string preferencesFile;
	string gameTitles[MAX_NB_GAMES];
	int preferencesArray[MAX_NB_GAMES];
	int planArray[366];
	
	for (int i = 0; i < MAX_NB_GAMES; i++) {
		preferencesArray[i] = 0;
	}
	
	cout << "Please enter the number of games and the duration: ";
	cin >> ngames >> duration;

	if (ngames < 0 || ngames > 100 || duration < 0 || duration > 365) {
		cout << "Invalid input." << endl;
	} else {
		cout << "Please enter name of file with titles: ";
		cin >> titlesFile;
		cout << "Please enter name of file with preferences: ";
		cin >> preferencesFile;
		cout << "Please enter name of file with plan: ";
		cin >> planFile;
		
		readPrefs(preferencesFile, ngames, preferencesArray);
		readPlan(planFile, planArray);
		readGameTitles(titlesFile, ngames, gameTitles);
		int start = findBestVacation(duration, preferencesArray, planArray);
		
		
		cout << "Best start day is " << start << endl;
		cout << "Games to be played:" << endl;
		printGamesPlayedInVacation(start, duration, planArray, gameTitles, ngames);
	}
}



	