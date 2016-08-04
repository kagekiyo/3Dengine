#ifndef UGE_TEXTURE_H
#define UGE_TEXTURE_H

#include "SDLGL.h"
#include <memory>
#include <string>

namespace UGE
{
	class Texture
	{
	public:
		class Data
		{
		public:
			enum class Type
			{
				PNG,
				BMP
			};

			Data(const std::string &filename, Type t);
			~Data();

			const void*			getData() const;
			unsigned int		getWidth() const;
			unsigned int		getHeight() const;
			const std::string&	getName() const;
			bool				isValid() const;
		private:
			unsigned char*		mData;
			unsigned int		mWidth;
			unsigned int		mHeight;
			std::string			mName;
			bool				mValid;
		};

		enum class Format
		{
			RGBA,
			Depth
		};

		enum class Param
		{
			MinFilter,
			MagFilter,
			WrapS,
			WrapT
		};

		enum class ParamValue
		{
			Linear,
			Nearest,
			ClampToEdge,
			None
		};

		Texture(const std::string &name, Format f);
		Texture(const Data &d, Format f);
		~Texture();

		unsigned int		getID() const;
		void				setData(unsigned int width, unsigned int height, const void *data);
		void				setData(const Data &d);
		const std::string&	getName() const;
		void				setName(const std::string &name);
		unsigned int		getWidth() const;
		unsigned int		getHeight() const;
		void				bind(unsigned int unit = 0);
		void				setParam(Param p, ParamValue pv);
		ParamValue			getParamValue(Param p) const;
		bool				isDepth() const;

	private:
		static GLenum		paramToEnum(Param p);
		static GLenum		paramValueToEnum(ParamValue pv);

		unsigned int		mID;
		std::string			mName;
		unsigned int		mWidth;
		unsigned int		mHeight;
		Format				mFormat;
		ParamValue			mMinFilter;
		ParamValue			mMagFilter;
		ParamValue			mWrapS;
		ParamValue			mWrapT;

		static unsigned int	sUnits[8];
	};

}

#endif
