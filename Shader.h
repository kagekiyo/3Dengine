#ifndef UGE_SHADER_H
#define UGE_SHADER_H

#include <map>
#include <string>
#include "SDLGL.h"

namespace UGE
{
	class Shader
	{
	public:
		enum class Type
		{
			Vertex,
			Fragment
		};
		Shader(const std::string &name, Type t);
		~Shader();

		const std::string&	getName() const;
		void				setSource(const std::string &src);
		const std::string&	getSource() const;
		bool				compile();
		std::string			log();
	private:
		static GLenum		typeToEnum(Type t);

		unsigned int		mID;
		std::string			mName;
		std::string			mSource;
		std::string			mLog;
		GLenum				mType;
	};
}

#endif
