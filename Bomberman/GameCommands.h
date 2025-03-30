// file to store all commands this is cleaner than creating a new file for each command 

#pragma once
#include <iostream>

#include "Command.h"
#include "GameObjectCommand.h"



class TakeDamage final : public GameObjectCommand
{
public:
	explicit TakeDamage(dae::GameObject& gameObject) : GameObjectCommand(gameObject) {}

	void Execute() override;
};