#include "Player.h"

Player::Player()
{
	m_name = "John Doe";
	m_inventory = Item();
	m_location = 0;
}

Player::Player(std::string newName, Item newInventory, int newLocation)
{
	m_name = newName;
	m_inventory = newInventory;
	m_location = newLocation;
}

void Player::setName(std::string newName)
{
	m_name = newName;
}

void Player::setLocation(int newLocation)
{
	m_location = newLocation;
}

void Player::setItem(Item item)
{
	m_inventory = item;
}

void Player::setItemState(bool newState)
{
	m_inventory.setItemState(newState);
}

void Player::takeItem(Item newInventory)
{
	m_inventory = newInventory;
}

Item Player::dropItem(void)
{
	Item tempInventory = m_inventory;	//Temp inventory to return
	m_inventory = Item();	//Set inventory to empty item

	return tempInventory;
}

std::string Player::toggleItemState(void)
{
	m_inventory.setItemState(!m_inventory.getItemState());	//Toggle item state

	return m_inventory.getAction();
}
