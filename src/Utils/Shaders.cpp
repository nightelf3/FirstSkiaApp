#include "include/Utils/Shaders.h"

SkRuntimeEffect::Result Shaders::LoadFromFile(const SkString& filePath)
{
	sk_sp<SkData> skData = SkData::MakeFromFileName(filePath.c_str());
	if (!skData)
		return {nullptr, SkString{"Can't load the shader"}};
	SkString str{static_cast<const char*>(skData->data()), skData->size()};
	return SkRuntimeEffect::MakeForShader(std::move(str));
}
