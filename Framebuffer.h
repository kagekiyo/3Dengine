#ifndef UGE_FRAMEBUFFER_H
#define UGE_FRAMEBUFFER_H

#include <string>
#include <memory>

namespace UGE
{
	class Texture;

	class Framebuffer
	{
	public:
		Framebuffer(const std::string &name, unsigned int width, unsigned int height);
		~Framebuffer();

		void						bind();
		void						unbind();

		void						attachTexture(std::shared_ptr<Texture> texture);
		void						detachTexture();

		unsigned int				getWidth() const;
		unsigned int				getHeight() const;

		static void					bindDefault();
		static void					setDefaultSize(unsigned int width, unsigned int height);

	private:
		void						makeRenderbuffer();

		unsigned int				mID;
		unsigned int				mDepthRenderBufferID;
		std::string					mName;
		std::shared_ptr<Texture>	mTexture;
		unsigned int				mWidth;
		unsigned int				mHeight;
		
		static unsigned int			sDefaultWidth;
		static unsigned int			sDefaultHeight;
	};
}

#endif
