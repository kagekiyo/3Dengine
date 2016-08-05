#include "Shader.h"

namespace UGE
{
	Shader::Shader(const std::string &name, Type t)
		: mName(name)
		, mType(typeToEnum(t))
	{
		mID = glCreateShader(mType);
	}


	Shader::~Shader()
	{
		glDeleteShader(mID);
	}

	const std::string& Shader::getName() const
	{
		return mName;
	}

	void Shader::setSource(const std::string &src)
	{
		mSource = src;
		const char *s = src.c_str();
		glShaderSource(mID, 1, &s, nullptr);
	}

	const std::string& Shader::getSource() const
	{
		return mSource;
	}

	bool Shader::compile()
	{
		glCompileShader(mID);
		GLint param = GL_FALSE;
		glGetShaderiv(mID, GL_COMPILE_STATUS, &param);
		
		if(param != GL_TRUE)
		{
			GLint infoLogLength;
			glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &infoLogLength);
			char *log = new char[infoLogLength];
			glGetShaderInfoLog(mID, infoLogLength, nullptr, log);
			char *buffer = new char[32 + infoLogLength + mName.size()];
			sprintf(buffer, "GL Shader error: %s:\n%\n", mName.c_str(), log);
			mLog += log;
			delete[] buffer;
			delete[] log;

			return false;
		}

		return true;
	}

	std::string Shader::log()
	{
		auto l = mLog;
		mLog.clear();
		return l;
	}

	GLenum Shader::typeToEnum(Type t)
	{
		switch(t)
		{
			case Type::Vertex:		return GL_VERTEX_SHADER;	break;
			case Type::Fragment:	return GL_FRAGMENT_SHADER;	break;
		}
		return GL_INVALID_ENUM;
	}
}
