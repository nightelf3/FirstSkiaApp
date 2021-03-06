#ifndef OPENGLBACKGROUND_H_7558918C_23B1_4BDA_9055_450D3308DED5
#define OPENGLBACKGROUND_H_7558918C_23B1_4BDA_9055_450D3308DED5

#include "BaseBackgound.h"
#include "include/gpu/gl/GrGLInterface.h"
#include "include/gpu/GrDirectContext.h"

class OpenGLBackgound : public BaseBackgound
{
public:
	OpenGLBackgound(WHandle handle);
	~OpenGLBackgound();

	std::wstring GetName() const override { return L"OpenGL"; }
	sk_sp<SkSurface> CreateSurface(int widht, int height) override;
	void Destroy() override;
	void SwapBuffers() override;

protected:
	HGLRC m_hRC = NULL;
	HDC m_dc = NULL;
	sk_sp<GrDirectContext> m_Context;
	sk_sp<const GrGLInterface> m_BackendContext;
};

#endif // OPENGLBACKGROUND_H_7558918C_23B1_4BDA_9055_450D3308DED5
