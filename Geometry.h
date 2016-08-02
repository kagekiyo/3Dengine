#ifndef UGE_GEOMETRY_H
#define UGE_GEOMETRY_H

#include <vector>
#include <string>
#include <memory>
#include "SDLGL.h"

namespace UGE
{
	class VertexBuffer;

	class Geometry
	{
	public:
		enum class Mode
		{
			Triangles,
			TriangleStrip,
			TriangleFan
		};

		typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;

		Geometry();

		void							draw();
		void							addVertexBuffer(VertexBufferPtr vbo);
		void							setMode(Mode m);
		void							setVertexCount(unsigned int count);
		const std::string&				getName() const;
	private:
		void							calculateVertexCount();

		std::vector<VertexBufferPtr>	mVBOs;
		unsigned int					mVertexCount;
		GLenum							mMode;
		std::string						mName;
	};
}

#endif