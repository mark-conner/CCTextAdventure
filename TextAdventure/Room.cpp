#include "Room.h"

Room::Room()
{
	m_name = "Empty";
	m_description = "This room is empty.";
	m_inventory = Item();
	m_moveTo = { -1, -1, -1, -1 };
}

Room::Room(std::string newName, std::string newDescription, Item newInventory, std::string newWID, std::string newRIWSD, std::string newRIRSD, std::string newRI, bool newRIS, std::vector<signed int> newMoves)
{
	m_name = newName;
	m_description = newDescription;
	m_inventory = newInventory;
	m_wrongItemDescription = newWID;
	m_rightItemWrongStateDescription = newRIWSD;
	m_rightItemRightStateDescription = newRIRSD;
	m_rightItem = newRI;
	m_rightItemState = newRIS;
	m_moveTo = newMoves;
}

void Room::setName(std::string newName)
{
	m_name = newName;
}

void Room::setDescription(std::string newDesc)
{
	m_description = newDesc;
}

//Get an Item dropped by player
void Room::recieveItem(Item newInventoryItem)
{
	m_inventory=newInventoryItem;
}

//Remove Item from Room and return to Player
Item Room::takeItem(void)
{
	Item tempItem = m_inventory;	//temp variable for returning item
	m_inventory = Item();
	return tempItem;
}

void Room::setItem(Item newInv)
{
	m_inventory = newInv;
}

void Room::setItemState(bool newState)
{
	m_inventory.setItemState(newState);
}

//Display item transfer description
void Room::displayItemDropDescription(void)
{
	if (m_inventory.getItemName() == m_rightItem && m_inventory.getItemState() == m_rightItemState)		//Right item right state
	{
		std::cout << m_rightItemRightStateDescription << std::endl;
	}
	else if (m_inventory.getItemName() == m_rightItem && m_inventory.getItemState() != m_rightItemState)	//right item wrong state
	{
		std::cout << m_rightItemWrongStateDescription << std::endl;

	}
	else if (m_inventory.getItemName() != m_rightItem)	//wrong item
	{
		std::cout << m_wrongItemDescription << std::endl;

	}
	else { std::cout << "Room inventory error."; }	//error

}
