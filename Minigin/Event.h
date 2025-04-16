#pragma once
#include <cstdint>
#include <string>
#include <variant>


struct EventArg
{
	using Value = std::variant<int, float, bool, const char*, std::string>;

	Value value;

	EventArg() = default;

	template <typename T>
	EventArg(T&& _value) : value(std::forward<T>(_value)) {}

	template <typename T>
	T Get() const
	{
		if (std::holds_alternative<T>(value))
		{
			return std::get<T>(value);
		}
		else
		{
			throw std::bad_variant_access();
		}
	}
};



using EventId = unsigned int;

struct Event
{
	const EventId id;

	static constexpr uint8_t MAX_ARGS = 8;
	uint8_t nbArgs = 0;
	EventArg args[MAX_ARGS];

	explicit Event(EventId _id) : id(_id) {}

	template <typename... Args>
	Event(EventId _id, Args&&... _args) : id(_id)
	{
		SetArgs(std::forward<Args>(_args)...);
	}

private:

	template <typename T, typename... Rest>
	void SetArgs(T&& first, Rest&&... rest)
	{
		if (nbArgs < MAX_ARGS)
		{
			args[nbArgs++] = EventArg(std::forward<T>(first));
			SetArgs(std::forward<Rest>(rest)...);
		}
	}

	void SetArgs() {} // Terminator
};

template <int length> struct sdbm_hash
{
	consteval static unsigned int _calculate(const char* const text, unsigned int& value)
	{
		const unsigned int character = sdbm_hash<length - 1>::_calculate(text, value);
		value = character + (value << 6) + (value << 16) - value;
		return text[length - 1];
	}

	consteval static unsigned int calculate(const char* const text)
	{
		unsigned int value = 0;
		const auto character = _calculate(text, value);
		return character + (value << 6) + (value << 16) - value;
	}
};

template <> struct sdbm_hash<1>
{
	consteval static unsigned int _calculate(const char* const text, unsigned int&) { return text[0]; }
};

template <size_t N> consteval unsigned int make_sdbm_hash(const char (&text)[N])
{
	return sdbm_hash<N - 1>::calculate(text);
}