#ifndef UGE_MATERIAL_H
#define UGE_MATERIAl_H

#include <map>
#include <memory>
#include "glm\glm.hpp"

namespace UGE
{
	class ShaderProgram;
	class Texture;

	class Material
	{
	public:
		Material();
		~Material() = default;

		const glm::vec4&				getColour() const;
		void							setColour(const glm::vec4& rgba);
		void							setColour(const glm::vec3& rgb);

		std::shared_ptr<Texture>		getTexture() const;
		void							setTexture(const std::shared_ptr<Texture>& t);

		bool							isTransparent() const;
		void							setTransparency(bool v);
	private:
		void							getProgram();

		std::weak_ptr<ShaderProgram>	mProgram;
		std::weak_ptr<Texture>			mTexture;
		glm::vec4						mColour;
		bool							mTransparency;
	};
}

#endif