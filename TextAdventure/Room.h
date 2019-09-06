#pragma once
#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"

class Room
{
private:
	std::string m_name;
	std::string m_description;
	Item m_inventory;
	std::string m_wrongItemDescription;
	std::string m_rightItemWrongStateDescription;
	std::string m_rightItemRightStateDescription;
	std::string m_rightItem;
	bool m_rightItemState;
	std::vector<signed int> m_moveTo;	//[0]=N [1]=E [2]=S [3]=W

public:
	Room::Room();	//Modified default constructor
	Room::Room(std::string, std::string, Item, std::string, std::string, std::string, std::string, bool, std::vector<signed int>);
	void Room::setName(std::string);	//Set Room's name
	void Room::setDescription(std::string);	//Set Room's description
	void Room::recieveItem(Item);	//Get an Item dropped by player
	Item Room::takeItem(void);	//Remove Item from Room and return to Player
	Item Room::getItem(void) { return m_inventory; }	//Get item
	void Room::setItem(Item);	//Set inventory Item
	void Room::setItemState(bool);	//Set inventory Item's state
	signed int Room::getMoveTo(int dir) { return m_moveTo[dir]; }
	std::string Room::getName(void) { return m_name; }
	std::string Room::getRightItem(void) { return m_rightItem; }
	bool Room::getRightItemState(void) { return m_rightItemState; }
	std::string Room::getDescription(void) { return m_description; }
	void Room::displayItemDropDescription(void);


};
#endif // !ROOM_H_

