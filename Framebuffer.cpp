#include "Framebuffer.h"
#include "Texture.h"
#include "SDLGL.h"

namespace UGE
{

	unsigned int Framebuffer::sDefaultWidth = 100;
	unsigned int Framebuffer::sDefaultHeight = 100;

	Framebuffer::Framebuffer(const std::string &name, unsigned int width, unsigned int height)
		: mDepthRenderBufferID(0)
		, mName(name)
		, mTexture(nullptr)
		, mWidth(width)
		, mHeight(height)
	{
		glGenFramebuffers(1, &mID);
		checkGL(glGenFramebuffers)
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &mID);
		checkGL(glDeleteFramebuffers)
	}

	void Framebuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mID);
		checkGL(glBindFramebuffer)
		glViewport(0, 0, mWidth, mHeight);
		checkGL(glViewport)
	}

	void Framebuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		checkGL(glBindFramebuffer 0)
	}

	void Framebuffer::attachTexture(std::shared_ptr<Texture> texture)
	{
		bind();
#ifdef _WIN32
		glDrawBuffer(GL_NONE);
		checkGL(glDrawBuffer)
		glReadBuffer(GL_NONE);
		checkGL(glReadBuffer)
#endif
		if(texture.get()->isDepth() && mDepthRenderBufferID != 0)
		{
			glDeleteRenderbuffers(1, &mDepthRenderBufferID);
			checkGL(glDeleteRenderbuffers)
			mDepthRenderBufferID = 0;
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, texture.get()->isDepth() ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.get()->getID(), 0);
		int error = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if(error != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("GL Framebuffer error: %i\n", error);
		}
		mTexture = texture;
	}

	void Framebuffer::detachTexture()
	{
		bind();
		glFramebufferTexture2D(GL_FRAMEBUFFER, mTexture.get()->isDepth() ? GL_DEPTH_ATTACHMENT : GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);

		if(mTexture.get()->isDepth())
			makeRenderbuffer();

		checkGL(glFramebufferTexture2D)
		mTexture.reset();
	}

	unsigned int Framebuffer::getWidth() const
	{
		return mWidth;
	}

	unsigned int Framebuffer::getHeight() const
	{
		return mHeight;
	}

	void Framebuffer::bindDefault()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		checkGL(glBindFramebuffer)
		glViewport(0, 0, sDefaultWidth, sDefaultHeight);
		checkGL(glViewport)
	}

	void Framebuffer::setDefaultSize(unsigned int width, unsigned int height)
	{
		sDefaultWidth = width;
		sDefaultHeight = height;
	}

	void Framebuffer::makeRenderbuffer()
	{
		bind();
		if(mDepthRenderBufferID == 0)
		{
			glGenRenderbuffers(1, &mDepthRenderBufferID);
			checkGL(glGenRenderbuffers)
		}

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, mWidth, mHeight);
		checkGL(glRenderbufferStorage)
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRenderBufferID);
		checkGL(glFramebufferRenderbuffer)
	}
}

