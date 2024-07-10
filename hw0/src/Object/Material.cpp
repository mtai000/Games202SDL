#include "Material.h"

Material::Material()
{
	mType = PHONG;
	mKa = glm::vec3();
	mKd = glm::vec3();
	mKs = glm::vec3();
}

Material::Material(const Type& _type)
{
	mType = _type;
	mKa = glm::vec3();
	mKd = glm::vec3();
	mKs = glm::vec3();
}

Material::~Material() {

}

Material::Material(const Type& _type, const glm::vec3& _ka, const glm::vec3& _kd, const glm::vec3& _ks)
{
	mType = _type;
	mKa = _ka;
	mKd = _kd;
	mKs = _ks;
}

void Material::Unload() {

}