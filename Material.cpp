#include "Material.h"
#include "ShaderProgram.h"

namespace UGE
{
	Material::Material()
		: mColour(1.0f)
		, mTransparency(false)
	{
		getProgram();
	}

	const glm::vec4& Material::getColour() const
	{
		return mColour;
	}

	void Material::setColour(const glm::vec4& rgba)
	{
		mColour = rgba;
	}

	void Material::setColour(const glm::vec3& rgb)
	{
		mColour = glm::vec4(rgb.x, rgb.y, rgb.z, 1.0f);
	}

	std::shared_ptr<Texture> Material::getTexture() const
	{
		return mTexture.lock();
	}

	void Material::setTexture(const std::shared_ptr<Texture>& t)
	{
		mTexture = t;
		getProgram();
	}

	bool Material::isTransparent() const
	{
		return mTransparency;
	}

	void Material::setTransparency(bool v)
	{
		mTransparency = v;
		getProgram();
	}

	void Material::getProgram()
	{
		mProgram = ShaderProgram::Cache::instance().getProgram(*this);
	}
}
