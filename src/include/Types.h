#ifndef ENUMS_H_907CD1C9_A3AE_40C3_AF2B_16BD46233C24
#define ENUMS_H_907CD1C9_A3AE_40C3_AF2B_16BD46233C24

#include <cstdint>

enum class ModifierKey
{
	kNone = 0,
	kControl = (1 << 0),
	kShift = (1 << 1),
	kOption = (1 << 2),
	kFirstPress = (1 << 3)
};

inline ModifierKey& operator |=(ModifierKey& a, ModifierKey b)
{
	return a = static_cast<ModifierKey>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

enum class Key
{
	kUnknown,
	kBack,
	kOK,
	kUp,
	kDown,
	kLeft,
	kRight,
	kTab,
	kPageUp,
	kPageDown,
	kHome,
	kEnd,
	kDelete,
	kEscape,
	kShift,
	kCtrl,
	kOption,
	kA,
	kC,
	kV,
	kX,
	kY,
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
