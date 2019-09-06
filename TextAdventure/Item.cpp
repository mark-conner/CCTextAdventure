#include "Item.h"

Item::Item()
{
	m_itemName = "nothing";
	m_itemDescription = "You are not carrying anything.";
	m_itemState = false;
	m_itemActionOn = "You get weird looks doing that.";
	m_itemActionOff = "Idle hands are the devil's workshop.";
}

Item::Item(std::string newItemName, std::string newItemDesc, bool newItemState, std::string newOn, std::string newOff)
{
	m_itemName = newItemName;
	m_itemDescription = newItemDesc;
	m_itemState = newItemState;
	m_itemActionOn = newOn;
	m_itemActionOff = newOff;
}

void Item::setItemName(std::string newItemName)
{
	m_itemName = newItemName;
}

void Item::setItemDesciption(std::string newDesc)
{
	m_itemDescription = newDesc;
}

void Item::setItemState(bool newState)
{
	m_itemState = newState;
}

void Item::setItemActionOn(std::string newOn)
{
	m_itemActionOn = newOn;
}

void Item::setItemActionOff(std::string newOff)
{
	m_itemActionOff = newOff;
}

std::string Item::getAction(void)
{
	if (m_itemState) { return m_itemActionOn; }

	return m_itemActionOff;
}
