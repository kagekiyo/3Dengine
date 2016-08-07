#ifndef UGE_SHADERPROGRAM_H
#define UGE_SHADERPROGRAM_H

#include <string>
#include <map>
#include "SDLGL.h"
#include "glm/glm.hpp"
#include <memory>

namespace UGE
{
	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string &name, std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);
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
		std::shared_ptr<Shader> getVertexShader() const;
		std::shared_ptr<Shader> getFragmentShader() const;
		const std::string&		getName() const;
		std::string				log();
	private:
		typedef std::map<std::string, GLint> UniformMap;

		void					makeUniform(const std::string &name);

		unsigned int			mID;
		std::string				mName;
		std::string				mLog;
		std::shared_ptr<Shader>	mVertexShader;
		std::shared_ptr<Shader>	mFragmentShader;
		UniformMap				mUniforms;

		static ShaderProgram*	sProgramInUse;
	};
}

#endif