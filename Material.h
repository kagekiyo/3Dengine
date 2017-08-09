#ifndef UGE_MATERIAL_H
#define UGE_MATERIAl_H

#include <map>
#include <memory>
#include "glm\glm.hpp"

namespace UGE
{
	class ShaderProgram;

	class Material
	{
	public:
		Material();
		~Material() = default;

		const glm::vec4&				getColour() const;
		void							setColour(const glm::vec4& rgba);
		void							setColour(const glm::vec3& rgb);

		bool							isTransparent() const;
		void							setTransparency(bool v);
	private:
		void							getProgram();

		std::weak_ptr<ShaderProgram>	mProgram;
		glm::vec4						mColour;
		bool							mTransparency;
	};
}

#endif