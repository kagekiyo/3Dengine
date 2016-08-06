#ifndef UGE_SHADERPROGRAM_H
#define UGE_SHADERPROGRAM_H

#include <string>
#include <map>
#include "SDLGL.h"
#include "glm/glm.hpp"

namespace UGE
{
	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string &name, const Shader &vertexShader, const Shader &fragmentShader);
		~ShaderProgram();

		void					use();
		void					setUniform(const std::string &name, const glm::mat3 &value);
		void					setUniform(const std::string &name, const glm::mat4 &value);
		void					setUniform(const std::string &name, const glm::vec2 &value);
		void					setUniform(const std::string &name, const glm::vec3 &value);
		void					setUniform(const std::string &name, const glm::vec4 &value);
		void					setUniform(const std::string &name, float value);
		void					setUniform(const std::string &name, int value);

		bool					link();
		void					bindAttribLocation(unsigned int index, const std::string &name);
		const Shader&			getVertexShader() const;
		const Shader&			getFragmentShader() const;
		const std::string&		getName() const;
		std::string				log();
	private:
		typedef std::map<std::string, GLint> UniformMap;

		void					makeUniform(const std::string &name);

		unsigned int			mID;
		std::string				mName;
		std::string				mLog;
		const Shader&			mVertexShader;
		const Shader&			mFragmentShader;
		UniformMap				mUniforms;

		static ShaderProgram*	sProgramInUse;
	};
}

#endif