#include "MarryActor.h"
#include "Core/Actor.h"
#include <string>
#include "Component/MeshComponent.h"
#include "Core/Game.h"
#include "Core/Renderer.h"
#include "Core/Actor.h"
#include "Object/Mesh.h"
#include "Object/Material.h"

MarryActor::MarryActor(Game* game)
	:Actor(game)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("text"));
	mc->SetMaterial(game->GetRenderer()->GetMaterial("caizhi"));

	mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Body_MC003_Kozakura_Mari_face"));
	mc->SetMaterial(game->GetRenderer()->GetMaterial("MC003_Kozakura_Mari"));
	mc->SetTexture(game->GetRenderer()->GetTexture("assets/hw1/obj/mary/MC003_Kozakura_Mari.png"));

	SetPosition(glm::vec3(0.f));
	SetScale(glm::vec3(10.f, 10.f, 10.f));
}

MarryActor::~MarryActor()
{
}
