#include "Geometry.h"
#include "VertexBuffer.h"

namespace UGE
{
	Geometry::Geometry()
		: mVertexCount(0)
		, mMode(GL_TRIANGLES)
	{
	}

	void Geometry::draw()
	{
		for(auto vboIt = mVBOs.begin(); vboIt != mVBOs.end(); ++vboIt)
		{
			auto vbo = vboIt->get();
			vbo->bind();

			const std::vector<VertexBuffer::Attribute> &kVBOAttributes = vbo->getAttributes();

			for(auto attributeIt = kVBOAttributes.cbegin(); attributeIt != kVBOAttributes.cend(); ++attributeIt)
			{
				const auto &kAttribute = *attributeIt;

				glEnableVertexAttribArray(kAttribute.id);
				checkGL(glEnableVertexAttribArray)
				glVertexAttribPointer(kAttribute.id, kAttribute.components, GL_FLOAT, GL_FALSE, vbo->getStride(), reinterpret_cast<void*>(kAttribute.offset * sizeof(GLfloat)));
				checkGL(glVertexAttribPointer)
			}
		}

		glDrawArrays(mMode, 0, mVertexCount);
		checkGL(glDrawArrays)

		for(auto vboIt = mVBOs.begin(); vboIt != mVBOs.end(); ++vboIt)
		{
			auto vbo = vboIt->get();

			const std::vector<VertexBuffer::Attribute> &kVBOAttributes = vbo->getAttributes();

			for(auto attributeIt = kVBOAttributes.cbegin(); attributeIt != kVBOAttributes.cend(); ++attributeIt)
			{
				glDisableVertexAttribArray(attributeIt->id);
				checkGL(glDisableVertexAttribArray)
			}
		}
	}

	void Geometry::addVertexBuffer(VertexBufferPtr vbo)
	{
		mVBOs.push_back(vbo);
		calculateVertexCount();
	}

	void Geometry::setMode(Mode m)
	{
		switch(m)
		{
		case Mode::Triangles:	 	mMode = GL_TRIANGLES; 		break;
		case Mode::TriangleStrip:	mMode = GL_TRIANGLE_STRIP; 	break;
		case Mode::TriangleFan:	 	mMode = GL_TRIANGLE_FAN; 	break;
		default:				 	mMode = GL_INVALID_ENUM; 	break;
		}
	}

	void Geometry::setVertexCount(unsigned int count)
	{
		mVertexCount = count;
	}

	const std::string& Geometry::getName() const
	{
		return mName;
	}

	void Geometry::calculateVertexCount()
	{
		mVertexCount = 0;

		for(auto vboIt = mVBOs.begin(); vboIt != mVBOs.end(); ++vboIt)
		{
			auto vbo = vboIt->get();

			unsigned int components = 0;
			const std::vector<VertexBuffer::Attribute> &kVBOAttributes = vbo->getAttributes();

			for(auto attributeIt = kVBOAttributes.cbegin(); attributeIt != kVBOAttributes.cend(); ++attributeIt)
			{
				components += attributeIt->components;
			}

			mVertexCount += (vbo->getSize() / sizeof(GLfloat)) / components;
		}
	}
}