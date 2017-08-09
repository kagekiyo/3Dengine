#ifndef UGE_MATERIAL_H
#define UGE_MATERIAl_H

#include <map>
#include <memory>

namespace UGE
{
	class ShaderProgram;

	class Material
	{
	public:
		Material();
		~Material();
	private:
		std::weak_ptr<ShaderProgram> mProgram;
	};
}

#endif