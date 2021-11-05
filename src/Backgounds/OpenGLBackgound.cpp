#include "include/Backgounds/OpenGLBackgound.h"

#include "include/gpu/GrContextOptions.h"
#include "src/gpu/gl/GrGLDefines.h"
#include "src/utils/win/SkWGL.h"
#include <GL/GL.h>

namespace
{
	constexpr int nSampleCount = 1;
	constexpr int nStencilBits = 8;

	HGLRC CreateWGLContext(HDC dc)
	{
		static PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
			32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, nStencilBits, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
		};

		GLuint PixelFormat;
		if (!(PixelFormat = ChoosePixelFormat(dc, &pfd)))
			return NULL;

		if (!SetPixelFormat(dc, PixelFormat, &pfd))
			return NULL;

		HGLRC hRC = NULL;
		if (!(hRC = wglCreateContext(dc)))
			return NULL;

		if (!wglMakeCurrent(dc, hRC))
		{
			wglDeleteContext(hRC);
			return NULL;
		}

		return hRC;
	}
}

OpenGLBackgound::OpenGLBackgound(WHandle handle) :
	BaseBackgound(handle)
{
}

OpenGLBackgound::~OpenGLBackgound()
{
	Destroy();
}

sk_sp<SkSurface> OpenGLBackgound::CreateSurface(int width, int height)
{
	m_dc = GetDC(m_WHandle);

	if (!(m_hRC = CreateWGLContext(m_dc)))
		return nullptr;

	glClearStencil(0);
	glClearColor(0, 0, 0, 0);
	glStencilMask(0xffffffff);
	glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width, height);

	m_BackendContext = GrGLMakeNativeInterface();
	m_Context = GrDirectContext::MakeGL(m_BackendContext, {});

	GrGLint buffer;
	m_BackendContext->fFunctions.fGetIntegerv(GR_GL_FRAMEBUFFER_BINDING, &buffer);

	GrGLFramebufferInfo fbInfo;
	fbInfo.fFBOID = buffer;
	fbInfo.fFormat = GR_GL_RGBA8;

	SkSurfaceProps props(0, kRGB_H_SkPixelGeometry);

	GrBackendRenderTarget backendRT(std::max(width, 1), std::max(height, 1), nSampleCount, nStencilBits, fbInfo);
	return SkSurface::MakeFromBackendRenderTarget(m_Context.get(), backendRT,
		kBottomLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, nullptr, &props);
}

void OpenGLBackgound::Destroy()
{
	if (m_Context)
	{
		m_Context->abandonContext();
		m_Context.reset();
	}

	m_BackendContext.reset(nullptr);

	if (m_hRC)
	{
		wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}

	if (m_dc)
	{
		ReleaseDC(m_WHandle, m_dc);
		m_dc = NULL;
	}
}

void OpenGLBackgound::SwapBuffers()
{
	HDC dc = GetDC(m_WHandle);
	::SwapBuffers(dc);
	ReleaseDC(m_WHandle, dc);
}