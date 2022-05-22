#pragma once

template <typename T, typename Parameter>
class NamedType 
{
public: 
	explicit NamedType(const T& value) : m_value(value) {}
	explicit NamedType(T&& value) : m_value(std::move(value)) {}
	T& get() { return m_value; }
	const T& get() const { return m_value; }
private:
	T m_value;
};