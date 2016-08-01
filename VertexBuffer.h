#ifndef UGE_VERTEXBUFFER_H
#define UGE_VERTEXBUFFER_H

#include <vector>

namespace UGE
{
	class VertexBuffer
	{
	public:
		struct Attribute
		{
			unsigned int				id;
			unsigned int				components;
			int							offset;
		};

		VertexBuffer();
		~VertexBuffer();

		unsigned int					getID() const;
		void							bind();
		void							setData(int size, const void *data);
		int								getSize() const;
		void							addAttribute(unsigned int id, unsigned int components, int offset);
		const std::vector<Attribute>&	getAttributes() const;
		int								getStride() const;
	private:
		void							calculateStride();

		unsigned int					mID;
		int								mSize;
		std::vector<Attribute>			mAttributes;
		int								mStride;
	};
}

#endif