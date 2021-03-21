#ifndef BASEBACKGROUND_H_EBFC0D95_2CA0_4123_A180_8032569FAF4E
#define BASEBACKGROUND_H_EBFC0D95_2CA0_4123_A180_8032569FAF4E

#include "include/Interfaces/IBackground.h"
#include "include/Types.h"

class BaseBackgound : public IBackground
{
public:
	BaseBackgound(WHandle handle);

protected:
	WHandle m_WHandle;
};

#endif // BASEBACKGROUND_H_EBFC0D95_2CA0_4123_A180_8032569FAF4E
