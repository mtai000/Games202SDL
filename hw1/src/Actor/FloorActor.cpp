#include "FloorActor.h"
#include "Core/Actor.h"
#include "Core/Game.h"
#include "Core/Renderer.h"
#include "Component/MeshComponent.h"
#include "Object/Mesh.h"
#include "Object/Material.h"
#include "Object/Texture.h"

FloorActor::FloorActor(Game* _game)
	:Actor(_game)
{
	const char* meshname = "Plane";
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(_game->GetRenderer()->GetMesh(meshname));
	if (!mc->GetMesh())
		SDL_Log("Can not load mesh: %s", "Plane");
	mc->SetMaterial(_game->GetRenderer()->GetMaterial("None"));
	SetPosition(glm::vec3(0.f, 0.f, 0.f));
	SetScale(glm::vec3(4.f, 4.f, 4.f));
}

FloorActor::~FloorActor()
{
}


