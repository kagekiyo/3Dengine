#include "ShaderProgram.h"
#include "Shader.h"
#include "Material.h"
#include "glm/gtc/type_ptr.hpp"

namespace UGE
{
	ShaderProgram* ShaderProgram::sProgramInUse = nullptr;

	ShaderProgram::ShaderProgram(const std::string &name, const std::shared_ptr<Shader> &vertexShader, const std::shared_ptr<Shader> &fragmentShader)
		: mID(glCreateProgram())
		, mName(name)
		, mVertexShader(vertexShader)
		, mFragmentShader(fragmentShader)
	{
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(mID);
	}

	void ShaderProgram::use()
	{
		if(!sProgramInUse || sProgramInUse != this)
		{
			sProgramInUse = this;
			glUseProgram(mID);
		}
	}

	void ShaderProgram::setUniform(const std::string &name, const glm::mat3 &value)
	{
		auto it = mUniforms.find(name);

		if(it == mUniforms.end())
		{
			makeUniform(name);
			glUniformMatrix3fv(mUniforms[name], 1, GL_FALSE, glm::value_ptr(value));
		}
		else
			glUniformMatrix3fv(it->second, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::setUniform(const std::string &name, const glm::mat4 &value)
	{
		auto it = mUniforms.find(name);

		if(it == mUniforms.end())
		{
			makeUniform(name);
			glUniformMatrix4fv(mUniforms[name], 1, GL_FALSE, glm::value_ptr(value));
		}
		else
			glUniformMatrix4fv(it->second, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::setUniform(const std::string &name, const glm::vec2 &value)
	{
		auto it = mUniforms.find(name);

		if(it == mUniforms.end())
		{
			makeUniform(name);
			glUniform2f(mUniforms[name], value.x, value.y);
		}
		else
			glUniform2f(it->second, value.x, value.y);
	}

	void ShaderProgram::setUniform(const std::string &name, const glm::vec3 &value)
	{
		auto it = mUniforms.find(name);

		if(it == mUniforms.end())
		{
			makeUniform(name);
			glUniform3f(mUniforms[name], value.x, value.y, value.z);
		}
		else
			glUniform3f(it->second, value.x, value.y, value.z);
	}

	void ShaderProgram::setUniform(const std::string &name, const glm::vec4 &value)
	{
		auto it = mUniforms.find(name);

		if(it == mUniforms.end())
		{
			makeUniform(name);
			glUniform4f(mUniforms[name], value.x, value.y, value.z, value.w);
		}
		else
			glUniform4f(it->second, value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::setUniform(const std::string &name, float value)
	{
		auto it = mUniforms.find(name);

		if(it == mUniforms.end())
		{
			makeUniform(name);
			glUniform1f(mUniforms[name], value);
		}
		else
			glUniform1f(it->second, value);
	}

	void ShaderProgram::setUniform(const std::string &name, int value)
	{
		auto it = mUniforms.find(name);

		if(it == mUniforms.end())
		{
			makeUniform(name);
			glUniform1i(mUniforms[name], value);
		}
		else
			glUniform1i(it->second, value);
	}
		 
	bool ShaderProgram::link()
	{
		glLinkProgram(mID);
		GLint param = GL_FALSE;
		glGetProgramiv(mID, GL_LINK_STATUS, &param);
		if(param != GL_TRUE)
		{
			return false;
		}
		return true;
	}

	void ShaderProgram::bindAttribLocation(unsigned int index, const std::string &name)
	{
		glBindAttribLocation(mID, index, name.c_str());
	}

	std::shared_ptr<Shader> ShaderProgram::getVertexShader() const
	{
		return mVertexShader;
	}

	std::shared_ptr<Shader> ShaderProgram::getFragmentShader() const
	{
		return mFragmentShader;
	}

	const std::string& ShaderProgram::getName() const
	{
		return mName;
	}

	std::string ShaderProgram::log()
	{
		auto l = mLog;
		mLog.clear();
		return l;
	}

	void ShaderProgram::makeUniform(const std::string &name)
	{
		mUniforms[name] = glGetUniformLocation(mID, name.c_str());
		checkGL(glGetUniformLocation)

		if(mUniforms[name] == -1)
		{
			char buffer[128];
			sprintf(buffer, "GL Error: uniform %s in program %s does not exist\n", name.c_str(), mName.c_str());
			mLog += buffer;
		}
	}

	ShaderProgram::Cache& ShaderProgram::Cache::instance()
	{
		static Cache c;
		return c;
	}

	std::shared_ptr<ShaderProgram> ShaderProgram::Cache::getProgram(const Material& m)
	{
		int key = 0;
		key |= static_cast<int>(m.isTransparent());
		key |= static_cast<int>(m.getTexture() != nullptr)	<< 1;
		auto it = mPrograms.find(key);
		if(it == mPrograms.end())
		{
			auto vertShader = std::make_shared<Shader>("v", Shader::Type::Vertex);
			auto fragShader = std::make_shared<Shader>("f", Shader::Type::Fragment);

			// todo: write shaders
			vertShader->setSource("");
			fragShader->setSource("");

			if(!vertShader->compile())
				printf(vertShader->log().c_str());
			if(!fragShader->compile())
				printf(fragShader->log().c_str());

			auto program = std::make_shared<ShaderProgram>("p", vertShader, fragShader);
			if(!program->link())
				printf(program->log().c_str());

			it = mPrograms.insert(it, {key, program});
		}
		return it->second;
	}
}
