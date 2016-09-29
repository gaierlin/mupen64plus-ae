#ifndef __LOG_H__
#define __LOG_H__

#define LOG_NONE	0
#define LOG_ERROR   1
#define LOG_MINIMAL	2
#define LOG_WARNING 3
#define LOG_VERBOSE 4
#define LOG_APIFUNC 5

#define LOG_LEVEL LOG_WARNING

#if LOG_LEVEL>0
#ifdef ANDROID
#include <android/log.h>
#include <GLES2/gl2.h>
#include <string>

#define LOG(A, ...) \
    if (A <= LOG_LEVEL) \
    { \
		__android_log_print(ANDROID_LOG_DEBUG, "Rice", __VA_ARGS__); \
    }
#endif // ANDROID
#endif

#define debugPrint(A, ...)

inline bool checkShaderCompileStatus(GLuint obj)
{
	static const GLsizei nShaderLogSize = 1024;
	GLint status;
	glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLchar shader_log[nShaderLogSize];
		GLsizei nLogSize = nShaderLogSize;
		glGetShaderInfoLog(obj, nShaderLogSize, &nLogSize, shader_log);
		shader_log[nLogSize] = 0;
		LOG(LOG_ERROR, "shader_compile error: %s\n", shader_log);
		return false;
	}
	else{
		LOG(LOG_ERROR, "shader_compile SUCCESS!!!");
	}
	return true;
}

inline void logErrorShader(GLenum _shaderType, const std::string & _strShader)
{
	LOG(LOG_ERROR, "Error in %s shader", _shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment");

	const int max = 800;
	int pos = 0;

	while(pos < _strShader.length() ) {

		if (_strShader.length() - pos < max) {
			LOG(LOG_ERROR, "%s", _strShader.substr(pos).data());
		} else {
			LOG(LOG_ERROR, "%s", _strShader.substr(pos, max).data());
		}
		pos += max;
	}
}

inline bool checkProgramLinkStatus(GLuint obj)
{
	static const GLsizei nShaderLogSize = 1024;
	GLint status;
	glGetProgramiv(obj, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLsizei nLogSize = nShaderLogSize;
		GLchar shader_log[nShaderLogSize];
		glGetProgramInfoLog(obj, nShaderLogSize, &nLogSize, shader_log);
		LOG(LOG_ERROR, "shader_link error: %s\n", shader_log);
		return false;
	}
	return true;
}

#endif
