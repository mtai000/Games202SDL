#include "Renderer.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Game.h"

#include "Shader/Shader.h"
#include <iostream>
#include "Core/Renderer.h"
#include "Core/Component.h"
#include "Object/Mesh.h"
#include "Object/Material.h"
#include "Object/Texture.h"
#include <Shader/VertexArray.h>
#include "Actor/CameraActor.h"

#include "Component/LightComponent.h"
#include "Component/MeshComponent.h"
#include "Component/FrameBufferComponent.h"
//#define TEST

Renderer::Renderer(Game* game)
	: mGame(game)
	, mScreenHeight(768)
	, mScreenWidth(1024)
	, mPhongShader(NULL)
	, mTestShader(NULL)
	, mShadowShader(NULL)
{

}

Renderer::~Renderer()
{
}


bool Renderer::Init(unsigned int width, unsigned int height)
{
	mScreenWidth = width;
	mScreenHeight = height;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Games 202", 100, 100,
		mScreenWidth, mScreenHeight, SDL_WINDOW_OPENGL);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	glGetError();

	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
#ifdef TEST
	CreateTestPlane();
#endif
	mMainCameraActor = new CameraActor(mGame);

	return true;
}

void Renderer::Shutdown()
{
	mPhongShader->Unload();
	delete mPhongShader;

	mLightShader->Unload();
	delete mLightShader;

	mShadowShader->Unload();
	delete mShadowShader;

	mTestShader->Unload();
	delete mTestShader;

	delete mTestVA;

	printf("Shutdown Renderer\n");
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	for (auto m : mMateriales) {
		m.second->Unload();
		delete m.second;
	}
	mMateriales.clear();

	for (auto m : mTextures) {
		m.second->Unload();
		delete m.second;
	}
	mTextures.clear();

	for (auto m : mMeshes) {
		m.second->Unload();
		delete m.second;
	}
	mMeshes.clear();
	printf("Unload Data\n");
}

void Renderer::AddMesh(Mesh* mesh)
{
	mMeshes.emplace(mesh->GetMeshName(), mesh);
}

Mesh* Renderer::GetMesh(const char* meshName)
{
	auto iter = mMeshes.find(meshName);
	if (iter != mMeshes.end())
	{
		return iter->second;
	}
	else
	{
		SDL_Log("can not found Mesh : %s", meshName);
	}

	return nullptr;
}

void Renderer::AddMaterial(Material* _material)
{
	mMateriales.emplace(_material->mName, _material);
}

Material* Renderer::GetMaterial(const char* _materialName)
{
	auto iter = mMateriales.find(_materialName);
	if (iter != mMateriales.end())
	{
		return iter->second;
	}
	else
	{
		SDL_Log("can not found Material : %s", _materialName);
	}

	return nullptr;
}

void Renderer::AddTexture(Texture* _texture)
{
	//mTextures.emplace(_texture.GetTexturePath() , _texture);
}

Texture* Renderer::GetTexture(const char* _texturePath)
{
	auto iter = mTextures.find(_texturePath);
	if (iter != mTextures.end()) {
		return iter->second;
	}
	else
	{
		SDL_Log("didn't load texture: %s", _texturePath);
	}
	return nullptr;
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	mMeshComps.erase(iter);
}

void Renderer::AddFrameBufferComp(FrameBufferComponent* fbo)
{
	mFrameBufferComps.emplace_back(fbo);
}

void Renderer::RemoveFrameBufferComp(FrameBufferComponent* fbo)
{
	auto iter = std::find(mFrameBufferComps.begin(), mFrameBufferComps.end(), fbo);
	mFrameBufferComps.erase(iter);
}

void Renderer::AddLightComp(LightComponent* light) {
	mLightComps.emplace_back(light);
}
void Renderer::RemoveLightComp(LightComponent* light) {
	auto iter = std::find(mLightComps.begin(), mLightComps.end(), light);
	mLightComps.erase(iter);
}

void Renderer::Draw()
{


#ifdef TEST
	TestRendering();
#endif
	//LightRendering();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0.0, 0.0, 2048, 2048);
	ShadowRendering();

	glViewport(0, 0, mScreenWidth, mScreenHeight);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	PhongRendering();


	SDL_GL_SwapWindow(mWindow);
}

void Renderer::LightRendering()
{
	mLightShader->SetActive();
	mLightShader->SetMat4("uViewMatrix", mMainCameraActor->GetViewMatrix());
	mLightShader->SetMat4("uProjectionMatrix", mMainCameraActor->GetProjMatrix());
	mLightShader->SetVec3("uLightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	for (auto m : mMeshComps) {
		if (m->GetVisible())
		{
			m->Draw(mLightShader);
		}
	}
}

void Renderer::ShadowRendering()
{
	mShadowShader->SetActive();
	mShadowShader->SetMat4("uViewMatrix", mMainCameraActor->GetViewMatrix());
	mShadowShader->SetMat4("uProjectionMatrix", mMainCameraActor->GetProjMatrix());

	for (int i = 0; i < mLightComps.size(); i++)
	{
		mFrameBufferComps[i]->Active();
		glClearColor(1.f, 1.f, 1.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto m : mMeshComps)
		{
			mShadowShader->SetMat4("uModelMatrix", m->GetOwner()->GetWorldTransform());
			mShadowShader->SetMat4("uLightMVP", mLightComps[i]->GetMVP(m->GetOwner()));
			m->Draw(mShadowShader);
		}
		mFrameBufferComps[i]->Disactive();
	}
}

void Renderer::PhongRendering()
{
	mPhongShader->SetActive();
	mPhongShader->SetMat4("uViewMatrix", mMainCameraActor->GetViewMatrix());
	mPhongShader->SetMat4("uProjectionMatrix", mMainCameraActor->GetProjMatrix());

	for (int i = 0; i < mLightComps.size(); i++)
	{
		if (i != 0)
		{
			glDepthFunc(GL_LEQUAL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
		}

		for (auto m : mMeshComps) {
			if (m->GetVisible())
			{
				mPhongShader->SetMat4("uModelMatrix", m->GetOwner()->GetWorldTransform());
				mPhongShader->SetMat4("uLightMVP", mLightComps[i]->GetMVP(m->GetOwner()));

				auto _material = m->GetMaterial();
				mPhongShader->SetVec3("uKd", _material->mKd);
				mPhongShader->SetVec3("uKs", _material->mKs);
				mPhongShader->SetVec3("uLightPos", mLightComps[i]->GetOwner()->GetPosition());

				mPhongShader->SetVec3("uCameraPos", mMainCameraActor->GetPosition());
				mPhongShader->SetVec3("uLightIntensity", mLightComps[i]->GetIntensity());

				if (m->GetTexture())
				{
					mPhongShader->SetInt("uTextureSample", 1);
					mPhongShader->SetTexture("uSampler", m->GetTexture()->GetTextureID());
				}
				else
				{
					mPhongShader->SetInt("uTextureSample", 0);
				}

				mPhongShader->SetShadowMap("uShadowMap", mFrameBufferComps[i]->GetColorTexture());

				m->Draw(mPhongShader);
				mPhongShader->ResetTextureID();
			}
		}
	}
	glDisable(GL_BLEND);
}

void Renderer::TestRendering() {
	mTestShader->SetActive();
	mTestShader->SetMat4("uViewMatrix", mMainCameraActor->GetViewMatrix());
	mTestShader->SetMat4("uProjectionMatrix", mMainCameraActor->GetProjMatrix());

	//mTestVA->SetActive();
	//glDrawElements(GL_TRIANGLES, mTestVA->GetNumIndices(), GL_UNSIGNED_INT, 0);

	for (auto m : mMeshComps) {
		if (m->GetVisible())
		{
			m->Draw(mTestShader);
		}
	}

}


bool Renderer::LoadShaders() {
#ifdef  TEST
	mTestShader = new Shader();
	if (!mTestShader->Load("assets/shader/test.vert", "assets/shader/test.frag"))
	{
		return false;
	}
#endif //  Test


	mPhongShader = new Shader();
	if (!mPhongShader->Load(std::string(mms::shaders_path + "phong.vert").c_str(), std::string(mms::shaders_path + "phong.frag").c_str()))
	{
		return false;
	}
	////mPhongShader->SetActive();

	mShadowShader = new Shader();
	if (!mShadowShader->Load(std::string(mms::shaders_path + "shadow.vert").c_str(), std::string(mms::shaders_path + "shadow.frag").c_str()))
	{
		return false;
	}
	//mPhongShader->SetActive();

	return true;
}

bool Renderer::LoadObj(const char* filePath) {
	FILE* file = fopen(filePath, "r");
	if (file == NULL) {
		return false;
	}
	std::string folder(filePath);
	std::size_t pos = folder.find_last_of("/");
	folder = folder.substr(0, pos);

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	std::string name;
	std::string mtlname;
	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			if (!temp_vertices.empty() || !temp_uvs.empty() || !temp_normals.empty()) {
				PushbackMesh(name, mtlname,
					temp_vertices, temp_uvs, temp_normals,
					vertexIndices, uvIndices, normalIndices);
			}
			break;
		}

		if (strcmp(lineHeader, "o") == 0) {
			if (!temp_vertices.empty() || !temp_uvs.empty() || !temp_normals.empty()) {
				PushbackMesh(name, mtlname,
					temp_vertices, temp_uvs, temp_normals,
					vertexIndices, uvIndices, normalIndices);
			}

			char _name[128];
			fscanf(file, "%s", &_name);
			name = _name;
		}
		else if (strcmp(lineHeader, "mtllib") == 0) {
			char mtllib[128];
			fscanf(file, "%s", &mtllib);
			if (pos != std::string::npos)
			{
				LoadMaterial((folder + "/").c_str(), mtllib);
			}
			else {
				assert(0, "not found the material file!");
			}
		}
		else if (strcmp(lineHeader, "usemtl") == 0) {
			char _name[128];
			fscanf(file, "%s", &_name);
			mtlname = _name;
		}
		else if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.emplace_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.emplace_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.emplace_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3, vertex4;
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2],
				&vertexIndex[3], &uvIndex[3], &normalIndex[3]);

			if (matches == 9) {
				vertexIndices.emplace_back(vertexIndex[0]);
				vertexIndices.emplace_back(vertexIndex[1]);
				vertexIndices.emplace_back(vertexIndex[2]);
				uvIndices.emplace_back(uvIndex[0]);
				uvIndices.emplace_back(uvIndex[1]);
				uvIndices.emplace_back(uvIndex[2]);
				normalIndices.emplace_back(normalIndex[0]);
				normalIndices.emplace_back(normalIndex[1]);
				normalIndices.emplace_back(normalIndex[2]);

			}
			else if (matches == 12)
			{
				vertexIndices.emplace_back(vertexIndex[0]);
				vertexIndices.emplace_back(vertexIndex[1]);
				vertexIndices.emplace_back(vertexIndex[2]);
				uvIndices.emplace_back(uvIndex[0]);
				uvIndices.emplace_back(uvIndex[1]);
				uvIndices.emplace_back(uvIndex[2]);
				normalIndices.emplace_back(normalIndex[0]);
				normalIndices.emplace_back(normalIndex[1]);
				normalIndices.emplace_back(normalIndex[2]);

				vertexIndices.emplace_back(vertexIndex[0]);
				vertexIndices.emplace_back(vertexIndex[3]);
				vertexIndices.emplace_back(vertexIndex[2]);
				uvIndices.emplace_back(uvIndex[0]);
				uvIndices.emplace_back(uvIndex[3]);
				uvIndices.emplace_back(uvIndex[2]);
				normalIndices.emplace_back(normalIndex[0]);
				normalIndices.emplace_back(normalIndex[3]);
				normalIndices.emplace_back(normalIndex[2]);
			}
			else
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}

		}
	}
	return true;
}

bool Renderer::LoadMaterial(const char* folder, const char* fileName) {
	std::string sFolder(folder);
	FILE* file = fopen((sFolder + fileName).c_str(), "r");
	if (file == NULL) {
		return false;
	}

	Material* _m = new Material();

	while (1) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			mGame->GetRenderer()->AddMaterial(_m);
			break;
		}

		if (strcmp(lineHeader, "newmtl") == 0) {
			if (_m->mName != "") {
				mGame->GetRenderer()->AddMaterial(_m);
				_m = new Material();
			}

			char name[128];
			fscanf(file, "%s", &name);
			_m->mName = name;
		}
		else if (strcmp(lineHeader, "Ns") == 0) {
			float _ns;
			fscanf(file, "%f\n", &_ns);
			_m->mNs = _ns;
		}
		else if (strcmp(lineHeader, "Ka") == 0) {
			glm::vec3 _ka;
			fscanf(file, "%f %f %f\n", &_ka.x, &_ka.y, &_ka.z);
			_m->mKa = _ka;
		}
		else if (strcmp(lineHeader, "Kd") == 0) {
			glm::vec3 _v;
			fscanf(file, "%f %f %f\n", &_v.x, &_v.y, &_v.z);
			_m->mKd = _v;
		}
		else if (strcmp(lineHeader, "Ks") == 0) {
			glm::vec3 _v;
			fscanf(file, "%f %f %f\n", &_v.x, &_v.y, &_v.z);
			_m->mKs = _v;
		}
		else if (strcmp(lineHeader, "Ke") == 0) {
			glm::vec3 _v;
			fscanf(file, "%f %f %f\n", &_v.x, &_v.y, &_v.z);
			_m->mKe = _v;
		}
		else if (strcmp(lineHeader, "Ni") == 0) {
			float _ni;
			fscanf(file, "%f\n", &_ni);
			_m->mNi = _ni;
		}
		else if (strcmp(lineHeader, "d") == 0) {
			float _d;
			fscanf(file, "%f\n", &_d);
			_m->md = _d;
		}
		else if (strcmp(lineHeader, "illum") == 0) {
			float _illum;
			fscanf(file, "%f\n", &_illum);
			_m->mIllum = _illum;
		}
		else if (strcmp(lineHeader, "map_Kd") == 0) {
			char _map_kd[128];
			fscanf(file, "%s", &_map_kd);
			_m->mMap_Kd = sFolder + _map_kd;
			Texture* _t = new Texture();
			_t->Load(_m->mMap_Kd);
			mTextures.emplace(_m->mMap_Kd, _t);
		}
	}
}

void Renderer::PushbackMesh(
	std::string& name, std::string& mtlname,
	std::vector<glm::vec3>& _iv,
	std::vector<glm::vec2>& _it,
	std::vector<glm::vec3>& _in,
	std::vector<unsigned int>& _iVertexIndices,
	std::vector<unsigned int>& _iUVIndices,
	std::vector<unsigned int>& _iNormalIndices) {

	std::vector<SVertex> _sv;
	std::vector<unsigned int> _indices;
	//tmp_mesh.MeshMaterialName = findMaterial(mtlname);
	for (unsigned int i = 0; i < _iVertexIndices.size(); i++) {
		SVertex _tmp_v;
		assert(_iVertexIndices[i] - 1 < _iv.size(), "vertex indices out of array index");
		_tmp_v.position = _iv[_iVertexIndices[i] - 1];

		assert(_iUVIndices[i] - 1 < _it.size(), "UV indices out of array index");
		_tmp_v.texCoord = _it[_iUVIndices[i] - 1];

		assert(_iNormalIndices[i] - 1 < _in.size(), "normal indices out of array index");
		_tmp_v.normal = _in[_iNormalIndices[i] - 1];

		_sv.emplace_back(_tmp_v);
		_indices.emplace_back(i);
	}
	//_iv.clear();
	//_it.clear();
	//_in.clear();
	_iVertexIndices.clear();
	_iUVIndices.clear();
	_iNormalIndices.clear();
	VertexArray* va = new VertexArray(&_sv[0], _sv.size(), &_indices[0], _indices.size());
	Mesh* m = new Mesh(va);
	m->SetMeshName(name);
	AddMesh(m);
}



void Renderer::CreateTestPlane()
{
	float vertices[] = {
	-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
	0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
	0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
	-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	SVertex s;
	auto a = SVertex();

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mTestVA = new VertexArray(vertices, 4, indices, 6);
}