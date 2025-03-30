#pragma once
#include <cstdint>


struct EventArg {};

enum class EventId : uint8_t
{
	DAMAGE_TAKEN,
	PLAYER_DIED,
	POINTS_TAKEN
};

struct Event
{
	const EventId id;

	static constexpr uint8_t MAX_ARGS = 8;
	uint8_t nbArgs;
	EventArg args[MAX_ARGS];

	explicit Event(EventId _id) : id(_id) {}
};