#include "Shader.h"
#include "ShaderProgram.h"
#include <memory>

int main(int argc, char *argv[])
{
	using namespace UGE;
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	auto window = SDL_CreateWindow("sdasda", 0, 0, 100, 100, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	auto context = SDL_GL_CreateContext(window);

	glewExperimental = true;
	glewInit();

	std::shared_ptr<ShaderProgram> p;
	{
		std::shared_ptr<Shader> v(new Shader("vert", Shader::Type::Vertex));
		std::shared_ptr<Shader> f(new Shader("frag", Shader::Type::Fragment));
		p.reset(new ShaderProgram("prog", v, f));
	}
	return 0;
}