#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

class Renderer {
public:
	Renderer(class Game* game);
	~Renderer();
	class Game* GetGame() { return mGame; }

	bool Init(unsigned int width, unsigned int height);
	void Shutdown();
	void UnloadData();

	void AddMesh(class Mesh* _mesh);
	class Mesh* GetMesh(const char* _meshName);

	void AddMaterial(class Material* _material);
	class Material* GetMaterial(const char* _materialName);

	void AddTexture(class Texture* _texture);
	class Texture* GetTexture(const char* _texturePath);

	void AddMeshComp(class MeshComponent* mesh);
	void RemoveMeshComp(class MeshComponent* mesh);

	void AddFrameBufferComp(class FrameBufferComponent* fbo);
	void RemoveFrameBufferComp(class FrameBufferComponent* fbo);

	void AddLightComp(class LightComponent* light);
	void RemoveLightComp(class LightComponent* light);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	void Draw();

	void LightRendering();

	void ShadowRendering();

	void PhongRendering();

	bool LoadObj(const char* filePath);
	bool LoadMaterial(const char* folder, const char* fileName);

	class CameraActor* GetMainCamera() { return mMainCameraActor; }


private:
	bool LoadShaders();

	class CameraActor* mMainCameraActor;

	SDL_Window* mWindow;
	SDL_GLContext mContext;

	class Shader* mTestShader;
	class Shader* mLightShader;
	class Shader* mPhongShader;
	class Shader* mShadowShader;


	std::vector<class MeshComponent*> mMeshComps;
	std::vector<class FrameBufferComponent*> mFrameBufferComps;
	std::vector<class LightComponent*> mLightComps;

	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::unordered_map<std::string, class Material*> mMateriales;
	std::unordered_map<std::string, class Texture*> mTextures;

	class Game* mGame;
	unsigned int mScreenWidth, mScreenHeight;

	void PushbackMesh(std::string& name
		, std::string& mtlname
		, std::vector<glm::vec3>& _iv
		, std::vector<glm::vec2>& _it
		, std::vector<glm::vec3>& _in
		, std::vector<unsigned int>& _iVertexIndices
		, std::vector<unsigned int>& _iUVIndices
		, std::vector<unsigned int>& _iNormalIndices);

	//Test part
	void CreateTestPlane();
	class VertexArray* mTestVA;
	void TestRendering();
};