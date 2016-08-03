#include "Texture.h"
#include <vector>
#include "lodepng.h"

namespace UGE
{
	Texture::Data::Data(const std::string &filename, Texture::Data::Type t)
		: mData(nullptr)
		, mValid(true)
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
}
