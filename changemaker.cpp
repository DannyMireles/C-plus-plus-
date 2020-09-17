#include <iostream>
//include header files
using namespace std;

int main()  {
	//define variables needed
	int dollars;
	int quarters;
	int	dimes;
	int nickels;
	int pennies;
	int tot_coins;
	int cents;
	
	//ask user for dollar and cent amount
	cout << "Enter dollars: ";
	cin >> dollars;
	cout << "Enter cents: ";
	cin >> pennies;
	
	//run calculations using modulo & division
	pennies = dollars * 100 + pennies;
	
	quarters = pennies / 25;
	pennies = pennies % 25;
	
	dimes = pennies / 10;
	pennies = pennies % 10;
	
	nickels = pennies / 5;
	pennies = pennies % 5;
	
	cents = pennies;
	
	tot_coins = quarters + dimes + nickels + pennies;
	
	//output the values
	cout << "Pennies: " << cents << endl;
	cout << "Nickels: " << nickels << endl;
	cout << "Dimes: " << dimes << endl;
	cout << "Quarters: " << quarters << endl;
	cout << endl;
	cout << "Total coins used: " << tot_coins << endl;
}