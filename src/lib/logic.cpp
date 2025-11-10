#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

// Declaring global variables to use 
int energy;
int score;
std::string currentLocation;
std::string criminal;

// Vector to store locations and suspects
std::vector<std::string> locations = { "Study Room", "Kitchen", "Garden", "TV Lounge", "Basement" };
std::vector<std::string> suspects = { "Ali", "Maria", "John" };

// Function to generate a random suspect
void generateSuspect()
{
	srand(time(0));
	criminal = suspects[rand() % suspects.size()];
}

// Function to initialize the game
void InitializeGame()
{
	energy = 100;
	score = 0;
	currentLocation = "Main Hall";
}
// Function to move player
void movement(const std::string location)
{
	currentLocation = location;
	energy -= 10;
}