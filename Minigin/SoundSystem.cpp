﻿//---------------------------
// Include Files
//---------------------------
#include "SoundSystem.h"
#include <SDL_mixer.h>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <ranges>
#include <SDL_timer.h>
#include <unordered_map>

class SoundSystem::SoundSystemImpl
{
public:
	SoundSystemImpl()
	{

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
		}

		std::cout << "[SoundSystemImpl] Constructor starting\n";
		m_Worker = std::jthread([this](std::stop_token stopToken) {
			std::cout << "[SoundSystem Thread] Launched\n";
			ProcessQueue(stopToken);
			});
		std::cout << "[SoundSystemImpl] Constructor finished\n";
	}

	~SoundSystemImpl()
	{
		std::cout << "[SoundSystemImpl] Destructor called, notifying thread...\n";
		m_Condition.notify_all(); // Wake thread in case it's waiting

		CleanupSounds();

		Mix_CloseAudio(); // Close audio device
	}

	void QueueSound(const std::string& soundFile)
	{
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_SoundQueue.push(soundFile);
			std::cout << "Sound added to queue, queue size: " << m_SoundQueue.size() << '\n';
		}
		m_Condition.notify_one();
	}

private:
	void ProcessQueue(const std::stop_token& stopToken)
	{
		std::cout << "[SoundSystem] Entered ProcessQueue\n";
		while (!stopToken.stop_requested())
		{
			std::unique_lock lock(m_Mutex);
			std::cout << "[SoundSystem] Waiting on condition...\n";

			m_Condition.wait(lock, stopToken, [this] {
				std::cout << "[SoundSystem] In predicate check\n";
				return !m_SoundQueue.empty();
				});

			if (stopToken.stop_requested())
				break;

			std::cout << "[SoundSystem] Woke up!\n";

			while (!m_SoundQueue.empty())
			{
				const auto soundFile = m_SoundQueue.front();
				m_SoundQueue.pop();
				lock.unlock();

				PlaySound(soundFile);

				lock.lock();
			}
		}
		std::cout << "[SoundSystem] Exiting ProcessQueue\n";
	}

	void PlaySound(const std::string& soundFile)
	{
		if (!m_SoundCache.contains(soundFile))
			LoadSound(soundFile);

		Mix_Chunk* chunk = m_SoundCache[soundFile];
		if (chunk)
			Mix_PlayChannel(-1, chunk, 0);
	}

	void LoadSound(const std::string& soundFile)
	{
		if (m_SoundCache.contains(soundFile)) return;

		Mix_Chunk* chunk = Mix_LoadWAV(soundFile.c_str());
		if (!chunk)
		{
			std::cerr << "Failed to load sound: " << soundFile << " - " << Mix_GetError() << '\n';
			return;
		}

		m_SoundCache[soundFile] = chunk;
	}

	void CleanupSounds()
	{
		for (auto& chunk : m_SoundCache | std::views::values)
		{
			Mix_FreeChunk(chunk);
		}
		m_SoundCache.clear();
	}

	std::queue<std::string> m_SoundQueue;
	std::mutex m_Mutex;
	std::condition_variable_any m_Condition;
	std::jthread m_Worker;

	std::unordered_map<std::string, Mix_Chunk*> m_SoundCache;
};


/// ---------------------------
/// SoundSystem class
/// ---------------------------

SoundSystem::SoundSystem() : m_Impl(std::make_unique<SoundSystemImpl>())
{
	// nothing to do
}

SoundSystem::~SoundSystem() = default;

SoundSystem::SoundSystem(SoundSystem&&) noexcept = default;
SoundSystem& SoundSystem::operator=(SoundSystem&&) noexcept = default;



void SoundSystem::QueueSound(const std::string& soundFile)
{
	m_Impl->QueueSound(soundFile);
}