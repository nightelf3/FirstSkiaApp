#include "include/Utils/ThemeUtils.h"

ContainerParams ThemeUtils::GetRightContainerParams()
{
	ContainerParams params;
	params.width = 320.0f;
	params.padding = 10.0f;
	params.itemsSpacing = 10.0f;
	return params;
}

ContainerParams ThemeUtils::GetControlsContainerParams()
{
	ContainerParams params;
	params.itemsSpacing = 4.0f;
	params.padding = 10.0f;
	params.drawParams.background = SkColors::kDkGray.toSkColor();
	params.drawParams.outline = SkColors::kGray.toSkColor();
	return params;
}
