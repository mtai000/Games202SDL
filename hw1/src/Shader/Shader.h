#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>

class Shader {
public:
	Shader();
	~Shader();
	bool Load(const std::string& vertex, const std::string& fragment);
	void Unload();


	void SetActive();

	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void SetVec2(const std::string& name, const glm::vec2& value);
	void SetVec2(const std::string& name, float x, float y);
	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetVec3(const std::string& name, float x, float y, float z);
	void SetVec4(const std::string& name, const glm::vec4& value);
	void SetVec4(const std::string& name, float x, float y, float z, float w);
	void SetMat3(const std::string& name, const glm::mat3& mat);
	void SetMat4(const std::string& name, const glm::mat4& mat);

	void SetTexture(const std::string& name, const unsigned int id);
	void SetShadowMap(const std::string& name, const unsigned int id);

	unsigned int GetProgramID() const { return mProgram; }
	void ResetTextureID() { mTextureID = 0; }
private:
	unsigned int mTextureID;
	bool CompileShader(const std::string& filename, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram();
	unsigned int mVertex; //vertex id
	unsigned int mFragment; //fragment id 
	unsigned int mProgram; //program id

};