#include "Model.h"
#include "Direct3D.h"

namespace Model {

	//モデルのポインタをぶち込んでおくベクタ
	std::vector<ModelData*> modelList;
	RENDER_STATE state_;
}

int Model::Load(std::string fileName)
{
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//ファイルネームが同じだったら、読まん！
	for (auto& e : modelList)
	{
		if (e->filename_ == fileName) {
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}

	if (pData->pfbx_ == nullptr)
	{
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}

	modelList.push_back(pData);
	return((int)(modelList.size() - 1));
}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
	//モデル番号は、modelListのインデックス
}



Fbx* Model::GetModel(int _hModel)
{
	return modelList[_hModel]->pfbx_;
}

void Model::Draw(int hModel) {
	//モデル番号は、modelListのインデックス
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isReffered = false; //参照されてる？
	for (int i = 0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered == false)
		{
			SAFE_DELETE(modelList[i]->pfbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}

void Model::ToggleRenderState()
{
	int n = (int)(Model::state_);
	Model::state_ = (RENDER_STATE)(++n % 2);
	for (auto& theI : modelList)
	{
		theI->pfbx_->SetRenderingShader(Model::state_);
	}
}