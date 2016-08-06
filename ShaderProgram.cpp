#include "ShaderProgram.h"

namespace UGE
{
	ShaderProgram::ShaderProgram(const std::string &name, const Shader &vertexShader, const Shader &fragmentShader)
		: mName(name)
		, mVertexShader(vertexShader)
		, mFragmentShader(fragmentShader)
	{
	}


	ShaderProgram::~ShaderProgram()
	{
	}
}
