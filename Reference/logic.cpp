#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

/// @brief Declaring global variables to use 
int energy;
int score;
std::string currentLocation;
std::string criminal;

/// @brief Vector to store locations and suspects
std::vector<std::string> locations = {"Kitchen", "Garden", "TV Lounge", "Basement"};
std::vector<std::string> suspects = {"Jackson", "Hagrid", "Julian"};

/// @brief Function to initialize the game
void initializeGame()
{
	energy = 100;
	score = 0;
	currentLocation = "Main Hall";
}

/// @brief Function to generate a random suspect
void generateCriminal()
{
	criminal = suspects[utils::getRandomInt(0, suspects.size())];
}

/// @brief Function to move player
/// @param location The location name
void movement(const std::string location)
{
	currentLocation = location;
	energy -= 10;
	if (energy < 0)
		energy = 0;
}

/// @brief Function to give detective the optoion to rest
void rest()
{
	int energyGain = 30;
	energy += energyGain;
	if (energy > 100)
		energy = 100;
}

/// @brief Function to interrogate the suspects
/// @param suspect_name The suspect name
std::string Interrogate(const std::string suspect_name)
{
	energy -= 20;
	if (energy < 0)
		energy = 0;
	int reaction = utils::getRandomInt(0, 3);
	if (reaction == 0)
	{
		return suspect_name + " seems nervous.";
	}
	else if (reaction == 1)
	{
		return suspect_name + " avoids your question.";
	}
	else if (reaction == 2)
	{
		return suspect_name + "'s story doesn't add up.";
	}
	else
	{
		return suspect_name + "answers your questions confidently and denies everything.";
	}
}

/// @brief Function to search for clues
bool searchClues()
{
	energy -= 30;
	if (energy < 0)
		energy = 0;
	bool found = utils::getRandomInt(0, 2);
	if (found)
	{
		score += 20;
		if (score > 100)
			score = 100;
		return true;
	}
	else
	{
		return false;
	}
}

/// @brief Function to accuse the suspect
/// @param accusedName The name of the suspect accused
bool accusation(const std::string accusedName)
{
	if (accusedName == criminal)
	{
		score += 50;
		return true;
	}
	else
	{
		energy -= 30;
		if (energy < 100)
			energy = 0;
		score -= 50;
		if (score < 0)
			score = 0;
		return false;
	}
}

