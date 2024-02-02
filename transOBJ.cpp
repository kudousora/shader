#include "transOBJ.h"
#include "Engine/Model.h"

transOBJ::transOBJ(GameObject* parent)
	:GameObject(parent, "transOBJ"), hModel_(-1)
{
}

transOBJ::~transOBJ()
{
}

void transOBJ::Initialize()
{
	hModel_ = Model::Load("Dice.fbx");
	assert(hModel_ >= 0);
}

void transOBJ::Update()
{
}

void transOBJ::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void transOBJ::Release()
{
}