#pragma once

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(T t) const noexcept
	{
		return std::hash<std::underlying_type_t<T>>{}(static_cast<std::underlying_type_t<T>>(t));
	}
};