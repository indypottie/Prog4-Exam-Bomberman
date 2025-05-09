﻿// file to store all commands this is cleaner than creating a new file for each command 

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


// temp command to play sound for testing the sound system
class PlaySoundCommand final : public Command
{
public:
	explicit PlaySoundCommand(std::string soundFile) : m_SoundFile(std::move(soundFile)) {}

	void Execute() override;

private:
	std::string m_SoundFile;
};