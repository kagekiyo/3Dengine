#include "Texture.h"
#include <vector>
#include "lodepng.h"
#include <string>

namespace UGE
{
	unsigned int Texture::sUnits[8];

	Texture::Data::Data(const std::string &filename, Texture::Data::Type t)
		: mData(nullptr)
		, mValid(true)
		, mFilename(filename)
	{
		switch(t)
		{
			case Type::PNG:
			{
				std::vector<unsigned char> image;

				unsigned int error = lodepng::decode(image, mWidth, mHeight, filename.c_str());

				if(error != 0)
				{
					printf("error loading texture %s: %s\n", filename.c_str(), lodepng_error_text(error));
					mValid = true;
				}
				else
				{
					mData = static_cast<unsigned char*>(malloc(image.size()));

					unsigned int count = 0;

					for(unsigned int i = mHeight; i > 0; --i)
					{
						for(unsigned int j = 0; j < (mWidth * 4); ++j)
						{
							mData[count++] = image[((i * (mWidth * 4)) - (mWidth * 4)) + j];
						}
					}
				}
				break;
			}
		}
	}

	Texture::Data::~Data()
	{
		delete mData;
	}

	const void* Texture::Data::getData() const
	{
		return mData;
	}

	unsigned int Texture::Data::getWidth() const
	{
		return mWidth;
	}

	unsigned int Texture::Data::getHeight() const
	{
		return mHeight;
	}

	const std::string& Texture::Data::getName() const
	{
		return mName;
	}

	bool Texture::Data::isValid() const
	{
		return mValid;
	}

	const std::string&	Texture::Data::getFilename() const
	{
		return mFilename;
	}

	Texture::Texture(const std::string &name, Format f)
		: mName(name)
		, mFormat(f)
		, mFilenameHash(0)
	{
		glGenTextures(1, &mID);
		checkGL(glGenTextures)
	}

	Texture::Texture(const Data &d, Format f)
		: mName(d.getName())
		, mFormat(f)
		, mFilenameHash(0)
	{
		std::hash<std::string> h;
		mFilenameHash = h(d.getFilename());
		glGenTextures(1, &mID);
		checkGL(glGenTextures)
		setData(d);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mID);
		checkGL(glDeleteTextures)
	}

	unsigned int Texture::getID() const
	{
		return mID;
	}

	void Texture::setData(unsigned int width, unsigned int height, const void *data)
	{
		bind();

		GLenum internalFormat = mFormat == Format::Depth ? GL_DEPTH_COMPONENT : GL_RGBA;
		GLenum format = mFormat == Format::Depth ? GL_DEPTH_COMPONENT : GL_RGBA;
		GLenum type = mFormat == Format::Depth ? GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth = width, mHeight = height, 0, format, type, data);
		checkGL(glTexImage2D)
	}

	void Texture::setData(const Data &d)
	{
		setData(d.getWidth(), d.getHeight(), d.getData());
	}

	const std::string& Texture::getName() const
	{
		return mName;
	}

	void Texture::setName(const std::string &name)
	{
		mName = name;
	}

	unsigned int Texture::getWidth() const
	{
		return mWidth;
	}

	unsigned int Texture::getHeight() const
	{
		return mHeight;
	}

	void Texture::bind(unsigned int unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		checkGL(glActiveTexture)

		if(sUnits[unit] != mID)
		{
			glBindTexture(GL_TEXTURE_2D, mID);
			checkGL(glBindTexture)
			sUnits[unit] = mID;
		}
	}

	void Texture::setParam(Param p, ParamValue pv)
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, paramToEnum(p), paramValueToEnum(pv));
		checkGL(glTexParameteri)
		switch(p)
		{
			case Param::MinFilter: 	mMinFilter = pv; 	break;
			case Param::MagFilter: 	mMagFilter = pv; 	break;
			case Param::WrapS: 		mWrapS = pv; 		break;
			case Param::WrapT: 		mWrapT = pv; 		break;
		}
	}

	Texture::ParamValue Texture::getParamValue(Param p) const
	{
		switch(p)
		{
		case Param::MinFilter: 	return mMinFilter;
		case Param::MagFilter: 	return mMagFilter;
		case Param::WrapS: 		return mWrapS;
		case Param::WrapT: 		return mWrapT;
		}
		return ParamValue::None;
	}

	bool Texture::isDepth() const
	{
		return mFormat == Format::Depth;
	}

	GLenum Texture::paramToEnum(Param p)
	{
		switch(p)
		{
			case Param::MinFilter: 	return GL_TEXTURE_MIN_FILTER; 	break;
			case Param::MagFilter: 	return GL_TEXTURE_MAG_FILTER; 	break;
			case Param::WrapS: 		return GL_TEXTURE_WRAP_S; 		break;
			case Param::WrapT: 		return GL_TEXTURE_WRAP_T; 		break;
		}
		return GL_INVALID_ENUM;
	}

	GLenum Texture::paramValueToEnum(ParamValue pv)
	{
		switch(pv)
		{
			case ParamValue::Linear: 		return GL_LINEAR; 			break;
			case ParamValue::Nearest: 		return GL_NEAREST;			break;
			case ParamValue::ClampToEdge:	return GL_CLAMP_TO_EDGE;	break;
			case ParamValue::None:			return GL_INVALID_ENUM;		break;
		}
		return GL_INVALID_ENUM;
	}

	bool Texture::operator<(const Texture& rhs) const
	{
		return mFilenameHash < rhs.mFilenameHash;
	}
}
