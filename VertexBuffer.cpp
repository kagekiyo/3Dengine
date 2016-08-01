#include "VertexBuffer.h"
#include "SDLGL.h"

namespace UGE
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &mID);
		checkGL(glGenBuffers)

	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &mID);
		checkGL(glDeleteBuffers)
	}

	unsigned int VertexBuffer::getID() const
	{
		return mID;
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		checkGL(glBindBuffer)
	}

	void VertexBuffer::setData(int size, const void *data)
	{
		bind();

		glBufferData(GL_ARRAY_BUFFER, (mSize = size), data, GL_STATIC_DRAW);
		checkGL(glBufferData)
	}

	int VertexBuffer::getSize() const
	{
		return mSize;
	}

	void VertexBuffer::addAttribute(unsigned int id, unsigned int components, int offset)
	{
		Attribute a;
		a.id = id;
		a.components = components;
		a.offset = offset;
		mAttributes.push_back(a);

		calculateStride();
	}

	const std::vector<VertexBuffer::Attribute>& VertexBuffer::getAttributes() const
	{
		return mAttributes;
	}

	int VertexBuffer::getStride() const
	{
		return mStride;
	}

	void VertexBuffer::calculateStride()
	{
		mStride = 0;

		for(unsigned int i = 0; i < mAttributes.size(); ++i)
			mStride += sizeof(GLfloat) * mAttributes[i].components;
	}
}