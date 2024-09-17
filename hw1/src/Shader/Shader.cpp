#include "Shader.h"

Shader::Shader()
	: mVertex(0)
	, mFragment(0)
	, mProgram(0)
	, mTextureID(0)
{
}

Shader::~Shader() {

}

bool Shader::Load(const std::string& vertex, const std::string& fragment) {
	mProgram = glCreateProgram();
	if (!CompileShader(vertex, GL_VERTEX_SHADER, mVertex) ||
		!CompileShader(fragment, GL_FRAGMENT_SHADER, mFragment)) {
		return false;
	}

	glAttachShader(mProgram, mVertex);
	glAttachShader(mProgram, mFragment);
	glLinkProgram(mProgram);
	if (!IsValidProgram())
	{
		return false;
	}
	return true;
}

void Shader::Unload() {
	if (!this) return;
	glDeleteProgram(mProgram);
	glDeleteShader(mVertex);
	glDeleteShader(mFragment);
}

bool Shader::CompileShader(const std::string& filename,
	GLenum shaderType, GLuint& outShader_id) {

	std::ifstream shaderFile(filename);
	if (shaderFile.is_open()) {
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		auto tmp = sstream.str();
		const char* contentsChar = tmp.c_str();
		outShader_id = glCreateShader(shaderType);
		glShaderSource(outShader_id, 1, &contentsChar, nullptr);
		glCompileShader(outShader_id);

		if (!IsCompiled(outShader_id)) {
			printf("Failed to compile shader %s", filename.c_str());
			return false;
		}
	}
	else
	{
		printf("Shader file not found: %s", filename.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader) {
	GLint status;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		printf("GLSL Compile Failed: \n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram() {
	GLint status;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mProgram, 511, nullptr, buffer);
		printf("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}

void Shader::SetActive()
{
	glUseProgram(mProgram);
}

void Shader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string& name, float x, float y)
{
	glUniform2f(glGetUniformLocation(mProgram, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(mProgram, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(mProgram, name.c_str()), x, y, z, w);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat)
{
	glUniformMatrix3fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetTexture(const std::string& name, const unsigned int id)
{
	glActiveTexture(GL_TEXTURE0 + mTextureID);
	glBindTexture(GL_TEXTURE_2D, id);
	glUniform1i(glGetUniformLocation(mProgram, name.c_str()), mTextureID);
	mTextureID++;
}

void Shader::SetShadowMap(const std::string& name, const unsigned int id)
{
	glActiveTexture(GL_TEXTURE0 + mTextureID);
	glBindTexture(GL_TEXTURE_2D, id);
	glUniform1i(glGetUniformLocation(mProgram, name.c_str()), mTextureID);
	mTextureID++;
}


