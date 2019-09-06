#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "item.h"


class Player
{
private:
	std::string m_name;	//Player's name
	Item m_inventory;	//Item in player's inventory
	int m_location;	//Location (room number) player is in

public:
	Player::Player();	//Modified Default Constructor
	Player::Player(std::string, Item, int);	//Overloaded default constructor
	void Player::setName(std::string);	//Set Player's name
	void Player::setLocation(int);	//Set Player's location (room number)
	void Player::setItem(Item);	//Set Player's Item
	void Player::setItemState(bool);	//Set Player's Item's state
	std::string Player::getName(void) { return m_name; }	//Return player's name
	int Player::getLocation(void) { return m_location; }	//Return player's location
	Item Player::getItem(void) { return m_inventory; }	//Get item
	void Player::takeItem(Item);	//Take an item from room inventory
	Item Player::dropItem(void);	// drop item in room and remove from inventory
	std::string Player::toggleItemState(void); //Toggle item state and return message

};

#endif // !PLAYER_H_