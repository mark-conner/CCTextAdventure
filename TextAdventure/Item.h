#pragma once
#ifndef ITEM_H_
#define ITEM_H_

#include <string>

class Item
{
private:
	std::string m_itemName;
	std::string m_itemDescription;
	bool m_itemState;	//Is the item on or off
	std::string m_itemActionOn;	//Description of item being activated
	std::string m_itemActionOff;	//Description of item being deactivated

public:
	Item::Item();	//Modified default constructor
	Item::Item(std::string, std::string, bool, std::string, std::string);	//Overloaded default constructor
	void Item::setItemName(std::string);	//Set item's name
	void Item::setItemDesciption(std::string);	//Set item's description
	void Item::setItemState(bool);	//Set item's state
	void Item::setItemActionOn(std::string);	//Set item's action when turned on
	void Item::setItemActionOff(std::string);	//Set item's action when turned on
	std::string Item::getItemName(void) { return m_itemName; }	//Get item's name
	std::string Item::getItemDescription(void) { return m_itemDescription; }	//Get items's description
	bool Item::getItemState(void) { return m_itemState; }	//Get item's on/off state (true = on)
	std::string Item::getAction(void); //Get item's description of current action
};

#endif // !ITEM_H_
