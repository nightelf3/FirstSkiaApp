#ifndef ENUMS_H_907CD1C9_A3AE_40C3_AF2B_16BD46233C24
#define ENUMS_H_907CD1C9_A3AE_40C3_AF2B_16BD46233C24

#include <cstdint>

struct ModifierKey
{
	using TUModifierKey = size_t;
	enum Modifiers : TUModifierKey
	{
		kNone = 0,
		kControl = (1 << 0),
		kShift = (1 << 1),
		kAlt = (1 << 2),
	};

	ModifierKey(Modifiers key) : m_Key(key) {}

	bool Has(ModifierKey key)
	{
		return m_Key & key.m_Key;
	}

	bool operator ==(ModifierKey key)
	{
		return m_Key == key.m_Key;
	}

	ModifierKey& operator |=(ModifierKey key)
	{
		m_Key |= key.m_Key;
		return *this;
	}

private:
	TUModifierKey m_Key;
};

inline bool operator ==(ModifierKey::Modifiers modifiers, ModifierKey key)
{
	return ModifierKey(modifiers) == key;
}

enum class Key
{
	kUnknown,
	kEnter,
	kUp,
	kDown,
	kLeft,
	kRight,
	kDelete,
	kEscape,
	kTab,
	kX,
	kZ
};

enum class InputState
{
	kDown,
	kUp,
	kMove,
	kZoomIn,
	kZoomOut
};

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
using WHandle = HWND;
#else
using WHandle = void*;
#endif

#endif // ENUMS_H_907CD1C9_A3AE_40C3_AF2B_16BD46233C24
