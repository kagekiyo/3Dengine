#ifdef _WIN32
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#else
#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#endif
#include <stdio.h>

#define checkGL(glCallStr)\
{\
	GLenum glError = glGetError();\
	if(glError != GL_NO_ERROR)\
		printf("GL Error: %s: %d\n", #glCallStr, glError);\
}