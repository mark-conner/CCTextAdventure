// TextAdventure.cpp : Defines the entry point for the console application.

//include libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>

#include "Item.h"
#include "Room.h"
#include "Player.h"

//Declare structure
struct Everything	//Structure containing Items, Rooms and Player
{
	std::vector<Item> items;
	std::vector<Room> rooms;
	Player player;
};

//Declare functions
std::vector<Item> initializeItems(void);	//Read item text from file and create items.
std::vector<Room> initializeRooms(std::vector<Item>);	//Read item text from file and create rooms.
Player initializePlayer(void);	//Get players name and initialize
Everything reloadGame(Everything);	//New game or reloaded game?
void showIntro(void);	//Show intro text.
char menu(Everything);	//Function to print menu and validate user input
void lookAround(Everything);	//Display room description 
void inspectInventory(Everything);	//Display inventory description
bool checkJanitor(Everything);	//Check for end of game, return true if done
Everything dropItem(Everything);	//Remove inventroy from Player, give to Room
Everything getItem(Everything);	//Remove inventroy from Room, give to Player
bool quitGame(Everything);	//Ask if saving game and end
void saveGame(Everything);	//Save game to file
Everything loadGame(Everything);	//Reload a saved game

//Main function
int main(void)
{
	//Declar variables
	Everything all;	//Structure containing Items, Rooms and Player
	bool complete = false;	//has player completed all tasks
	char selection;	//Menu input


	all.items = initializeItems();	//Create inventory items
	all.rooms = initializeRooms(all.items);	//Create rooms
	all.player = initializePlayer();	//Get player
	
	all = reloadGame(all);	//Start game with new info or reloaded from save file

	while (!complete)
	{
		selection = toupper(menu(all));	//Show menu, get selection, set to uppercase

		if (selection == 'L') { lookAround(all); }	//Look at room
		else if(selection == 'I') { inspectInventory(all); }	//Inspect inventory
		else if (all.player.getLocation() == 0 && selection == 'T') { complete = checkJanitor(all); }	//If in room 0 and all is correct, end game
		else if (all.rooms[all.player.getLocation()].getMoveTo(0) != -1 && selection == 'N') { all.player.setLocation(all.rooms[all.player.getLocation()].getMoveTo(0)); }	//Move North
		else if (all.rooms[all.player.getLocation()].getMoveTo(1) != -1 && selection == 'E') { all.player.setLocation(all.rooms[all.player.getLocation()].getMoveTo(1)); }	//Move East
		else if (all.rooms[all.player.getLocation()].getMoveTo(2) != -1 && selection == 'S') { all.player.setLocation(all.rooms[all.player.getLocation()].getMoveTo(2)); }	//Move South
		else if (all.rooms[all.player.getLocation()].getMoveTo(3) != -1 && selection == 'W') { all.player.setLocation(all.rooms[all.player.getLocation()].getMoveTo(3)); }	//Move West
		else if (all.player.getItem().getItemName() != "nothing" && all.rooms[all.player.getLocation()].getItem().getItemName() == "nothing" && selection == 'D') { all = dropItem(all); }	//Drop item in room
		else if (all.player.getItem().getItemName() == "nothing" &&	all.rooms[all.player.getLocation()].getItem().getItemName() != "nothing" && selection == 'G') { all = getItem(all); }	//Get item from room
		else if (selection == 'O') { std::cout << all.player.toggleItemState() << std::endl; }	//Change item on/off and display message
		else if (selection == 'Q') { complete = quitGame(all); }
	}


    return 0;
}

//Initialize Item vector
std::vector<Item> initializeItems(void)
{
	std::vector<Item> items;
	std::string fileText;	//Text read from files
	std::vector<std::string> itemText (5, "");	//Text for the item variables
	std::ifstream itemFile("items.txt");
	bool state;	//temp value to set stat of item from on/off value

	if (itemFile.is_open())
	{
		for (int item = 0; item < 4; item++)
		{
			for (int i = 0; i < 5; i++)
			{
				std::getline(itemFile, fileText);
				itemText[i] = fileText;
			}

			if (itemText[2] == "on") { state = true; }
			else { state = false; }
			items.push_back(Item(itemText[0], itemText[1], state, itemText[3], itemText[4]));
		}
	}
	
	else
	{
		std::cout << "Could not open items.txt file.";
	}

	return items;
}

//Initialize Room vector
std::vector<Room> initializeRooms(std::vector<Item> items)
{
	std::vector<Room> rooms;
	std::string fileText;	//Text read from files
	std::vector<std::string> roomText(9, "");	//Text for the item variables
	std::ifstream roomFile("rooms.txt");
	std::vector<signed int> moves;
	Item roomItem;	//Item for room to convert from text
	bool state;	//Right item state

	if (roomFile.is_open())
	{
		for (int room = 0; room < 5; room++)
		{
			for (int i = 0; i < 8; i++)
			{
				std::getline(roomFile, fileText);
				roomText[i] = fileText;
			}
			roomItem = Item();
			for (int j = 0; j < 4; j++)
			{
				if (roomText[2] == items[j].getItemName()) 
				{ 
					roomItem = items[j];
				}
			}

			if (roomText[7] == "on") { state = true; }
			else { state = false; }

			switch (room)
			{
			case 0:
				moves = { 1, -1, -1, -1 };
				break;
			case 1:
				moves = { 4, -1, 0, 2 };
				break;
			case 2:
				moves = { -1, 1, -1, -1 };
				break;
			case 3:
				moves = { -1, 4, 2, -1 };
				break;
			case 4:
				moves = { -1, -1, -1, 3 };
				break;
			}

			rooms.push_back(Room(roomText[0], roomText[1], roomItem, roomText[3], roomText[4], roomText[5], roomText[6], state, moves));
		}
	}

	else
	{
		std::cout << "Could not open items.txt file.";
	}

	return rooms;
}

//Initialize Player
Player initializePlayer(void)
{
	std::string playerName;
	Player newPlayer;

	std::cout << "Hello, what is your name? ";
	std::getline(std::cin, playerName);

	newPlayer = Player(playerName, Item(), 0);	//initialize player with new name, nothing for inventory in room 0

	return newPlayer;
}

//Start new game or reload from file
Everything reloadGame(Everything all)
{
	char selection;	//player selection

	std::cout << std::endl << all.player.getName() << ", will you be starting a new game or loading an old one?" <<std::endl;
	
	while (true)
	{
		std::cout << "(N)ew game" << std::endl << "(R)eload game" << std::endl << "Your choice: ";
		(std::cin >> selection).get();

		switch (selection)
		{
		case 'n':
		case 'N':
			showIntro();
			std::cout << std::endl;
			return all;
			break;
		case 'r':
		case 'R':
			all = loadGame(all);
			std::cout << std::endl;
			return all;
			break;
		};
	}
		return all;
}

//Show introduction text for new game
void showIntro(void)
{
	std::string getText;	//text from file
	std::ifstream readFromFile("intro.txt");	//Open intro text file for reading
	
	if (readFromFile.is_open())
	{
		while (std::getline(readFromFile, getText))
		{
			std::cout << getText << std::endl;
		}
	}
	else
	{
		std::cout << "Unable to open intro.txt.";
	}
}

//Main menu
char menu(Everything all)	//Display context appropriate menu
{
	char selection;	//Player selection from main menu
	
	std::cout << std::endl << "What would you like to do...\n";
	std::cout << "(L)ook around\n";
	std::cout << "(I)nspect your inventory\n";
	if (all.player.getLocation() == 0) { std::cout << "(T)alk to Janitor\n"; }
	if (all.rooms[all.player.getLocation()].getMoveTo(0) != -1) { std::cout << "Move (N)orth\n"; }
	if (all.rooms[all.player.getLocation()].getMoveTo(2) != -1) { std::cout << "Move (S)outh\n"; }
	if (all.rooms[all.player.getLocation()].getMoveTo(1) != -1) { std::cout << "Move (E)ast\n"; }
	if (all.rooms[all.player.getLocation()].getMoveTo(3) != -1) { std::cout << "Move (W)est\n"; }
	if (all.player.getItem().getItemName() != "nothing" &&
		all.rooms[all.player.getLocation()].getItem().getItemName() == "nothing") {
		std::cout << "(D)rop off item in room\n";
	}
	if (all.player.getItem().getItemName() == "nothing" &&
		all.rooms[all.player.getLocation()].getItem().getItemName() != "nothing") {
		std::cout << "(G)et item from room\n";
	}
	if (all.player.getItem().getItemState()) { std::cout << "Turn item (O)ff\n"; }
	else { std::cout << "Turn item (O)n\n"; }
	std::cout << "(Q)uit the game\n";
	std::cout << "Your selection: ";

	(std::cin >> selection).get();
	std::cout << std::endl;
	
	return selection;
}

//Display room description and contents
void lookAround(Everything all)
{
	std::cout << std::endl << "You are in " << all.rooms[all.player.getLocation()].getName() << "." << std::endl << std::endl;
	std::cout << all.rooms[all.player.getLocation()].getDescription() << std::endl;
	if (all.rooms[all.player.getLocation()].getItem().getItemName() == "nothing")
	{
		std::cout << "There is nothing to take from this room.";
	}
	else
	{
		std::cout << "There is a " << all.rooms[all.player.getLocation()].getItem().getItemName() << " in this room.";
	}
	std::cout << std::endl << std::endl;
}

//Display your inventory description
void inspectInventory(Everything all)
{
	std::cout << std::endl << all.player.getItem().getItemDescription() << std::endl;
}

//Check with the Janitor if tasks completed
bool checkJanitor(Everything all)
{
	bool complete = true;	//default complete state to true

		for (int i = 0; i < 5; i++)
		{
			if (all.rooms[i].getRightItem() != all.rooms[i].getItem().getItemName() ||	//wrong room item
				(all.rooms[i].getRightItemState() != all.rooms[i].getItem().getItemState()))	//wrong item state (room 2 doesn't care on state)
			{
				complete = false;
			}
		}

		if (complete)
		{
			std::cout << "The Janitor glares at you and then smiles.  He says 'Well, it looks like you helped everyone.'\n" <<
				"He suddenly opens the door as if it was never broken.  'You can go now.  I'll see you tomorrow!'\n" <<
				"You leave and realize you have missed all of your classes.  You hope to never run into The Janitor ever again.\n\n" <<
				"Press any key to exit";
			std::cin;
		}
		else
		{

			std::cout << "The Janitor says, 'I heard an instructor teach in a class one time that " << all.player.getName() <<
				"\nis Canadian for idiot.  Don't interrupt me unless you are done.'" << std::endl;
		}
		return complete;
}

//Drop Item from inventory and give to the Room
Everything dropItem(Everything all)
{
	all.rooms[all.player.getLocation()].recieveItem(all.player.dropItem());
	all.rooms[all.player.getLocation()].displayItemDropDescription();
	return all;
}

//Get Item from Room and give to Player
Everything getItem(Everything all)
{
	all.player.takeItem(all.rooms[all.player.getLocation()].takeItem());
	return all;
}

//Ask if save game and quit
bool quitGame(Everything all)
{
	char selection;	// Player input

	std::cout << std::endl << "Do you really want to quit (y/N)? ";
	(std::cin >> selection).get();
	if (toupper(selection) != 'Y') { return false; }
	std::cout << std::endl << "Do you want to save your game (Y/n)? ";
	(std::cin >> selection).get();
	if (toupper(selection) == 'N') { return true; }
	else
	{
		saveGame(all);
		return true;
	}
	std::cout << "Quiting error!";
	return true;
}

//Save game to file
void saveGame(Everything all)
{
	std::string file;	//Save file name
	
	std::ofstream writeToFile;

	std::cout << std::endl << "Enter the file name to save to: ";
	std::getline(std::cin, file);	//Get file name
	file = file + ".txt";	//Make complete file name

	writeToFile.open(file);

	writeToFile << all.rooms[all.player.getLocation()].getName() << "\n";	//write current room name
	writeToFile << all.player.getItem().getItemName() << "\n";	//write player's inventory item
	writeToFile << all.player.getItem().getItemState() << "\n";	//write player's invetory item's state

	for (int i = 0; i < all.rooms.size(); i++)	//iterate through rooms
	{
		writeToFile << all.rooms[i].getItem().getItemName() << "\n";	//write room inventory name
		writeToFile << all.rooms[i].getItem().getItemState() << "\n";	//write room inventory state
	}
		
	writeToFile.close();
}

//Load game from file
Everything loadGame(Everything all)
{
	std::string file;	//file name
	std::string text;	//text from file
	int rm = 0;	//room counter while reading file

	std::cout << std::endl << "Enter the file name to load: ";
	std::getline(std::cin, file);	//Get file name
	file = file + ".txt";	//Make complete file name

	std::ifstream readFromFile(file);
	
	if (readFromFile.is_open())
	{
		std::getline(readFromFile, text);	//Get Player's Room name
		for (int i = 0; i < all.rooms.size(); i++)
		{
			if (all.rooms[i].getName() == text) { all.player.setLocation(i); }
		}

		std::getline(readFromFile, text);	//Get Player's Inventory name
		if (text != "nothing")	//If player has an item, set it
		{
			for (int i = 0; i < all.items.size(); i++)
			{
				if (all.items[i].getItemName() == text)
				{
					all.player.setItem(all.items[i]);	//Set Player's Inventory Item
				}
			}
		}
		else { all.player.setItem(Item()); }	//Else set Player's Inventory to empty Item

		std::getline(readFromFile, text);	//Get Player's Inventory state
		if (text == "1") { all.player.setItemState(true); }	//Set Player's Inventory state
		else { all.player.setItemState(false); }

		while (std::getline(readFromFile, text))
		{
			if (rm >= all.rooms.size()) { break; }	//If reading more room info than rooms, stop

			if (text != "nothing")	//If Room has an Item, set it
			{
				for (int i = 0; i < all.items.size(); i++)
				{
					if (all.items[i].getItemName() == text)
					{
						all.rooms[rm].setItem(all.items[i]);	//Set Rooms Inventory Item
					}
				}
			}
			else { all.rooms[rm].setItem(Item()); }	//Else set Room's inventory to empty Item

			std::getline(readFromFile, text);	//Get Player's Inventory state
			if (text == "1") { all.rooms[rm].setItemState(true); }	//Set Player's Inventory state
			else { all.rooms[rm].setItemState(false); }

			rm++;	//Increment room number
		}
		readFromFile.close();
	}
	else
	{
		std::cout << "\nUnable to read from file!\nStarting new game.\n";
		showIntro();
	}

	return all;
}