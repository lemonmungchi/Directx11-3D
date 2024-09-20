#include "pch.h"
#include "ModelAnimator.h"
#include "Material.h"
#include "ModelMesh.h"
#include "Model.h"
#include "ModelAnimation.h"

ModelAnimator::ModelAnimator(shared_ptr<Shader> shader)
	: Super(ComponentType::Animator), _shader(shader)
{

}

ModelAnimator::~ModelAnimator()
{
}

//void ModelAnimator::Update()
//{
//	if (_model == nullptr)
//		return;
//
//	//TODO
//	if (_texture == nullptr)
//		CreateTexture();
//
//	//Anim Update
//	ImGui::InputInt("AnimIndex", &_keyframeDesc.animIndex);
//	_keyframeDesc.animIndex %= _model->GetAnimationCount();
//	ImGui::InputInt("CurrFrame", (int*)&_keyframeDesc.currFrame);
//	_keyframeDesc.currFrame %= _model->GetAnimationByIndex(_keyframeDesc.animIndex)->frameCount;
//
//	//애니메이션 현재 프레임 정보
//	RENDER->PushKeyframeData(_keyframeDesc);
//
//	//SRV를 전달
//	_shader->GetSRV("TransformMap")->SetResource(_srv.Get());
//
//	//Bones -> shader
//	BoneDesc boneDesc;
//
//	const uint32 boneCount = _model->GetBoneCount();
//
//	for (uint32 i = 0; i < boneCount; i++)
//	{
//		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
//		boneDesc.transforms[i] = bone->transform;
//	}
//	RENDER->PushBoneData(boneDesc);
//
//	//Transform
//	auto world = GetTransform()->GetWorldMatrix();
//	RENDER->PushTransformData(TransformDesc{ world });
//
//	const auto& meshes = _model->GetMeshes();
//	for (auto& mesh : meshes)
//	{
//		if (mesh->material)
//			mesh->material->Update();
//
//		//BoneIndex
//		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);
//
//		uint32 stride = mesh->vertexBuffer->GetStride();
//		uint32 offset = mesh->vertexBuffer->GetOffset();
//
//		//각 매쉬를 버퍼에 할당
//		DC->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
//		DC->IASetIndexBuffer(mesh->indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
//
//		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
//	}
//}

void ModelAnimator::Update()
{
	if (_model == nullptr)
		return;

	//TODO
	if (_texture == nullptr)
		CreateTexture();

	_keyframeDesc.sumTime += DT;

	shared_ptr<ModelAnimation> current = _model->GetAnimationByIndex(_keyframeDesc.animIndex);
	if (current)
	{
		//30프레임이면 1/30초 마다 다음 프레임
		float timePerFrame = 1 / (current->frameRate * _keyframeDesc.speed);
		if (_keyframeDesc.sumTime >= timePerFrame)
		{
			_keyframeDesc.sumTime = 0.f;
			_keyframeDesc.currFrame = (_keyframeDesc.currFrame + 1) % current->frameCount;
			_keyframeDesc.nextFrame = (_keyframeDesc.currFrame + 1) % current->frameCount;
		}

		_keyframeDesc.ratio = (_keyframeDesc.sumTime / timePerFrame);
	}

	//Anim Update
	ImGui::InputInt("AnimIndex", &_keyframeDesc.animIndex);
	_keyframeDesc.animIndex %= _model->GetAnimationCount();
	ImGui::InputFloat("Speed", &_keyframeDesc.speed, 0.5f, 4.f);

	//애니메이션 현재 프레임 정보
	RENDER->PushKeyframeData(_keyframeDesc);

	//SRV를 전달
	_shader->GetSRV("TransformMap")->SetResource(_srv.Get());

	//Bones -> shader
	BoneDesc boneDesc;

	const uint32 boneCount = _model->GetBoneCount();

	for (uint32 i = 0; i < boneCount; i++)
	{
		shared_ptr<ModelBone> bone = _model->GetBoneByIndex(i);
		boneDesc.transforms[i] = bone->transform;
	}
	RENDER->PushBoneData(boneDesc);

	//Transform
	auto world = GetTransform()->GetWorldMatrix();
	RENDER->PushTransformData(TransformDesc{ world });

	const auto& meshes = _model->GetMeshes();
	for (auto& mesh : meshes)
	{
		if (mesh->material)
			mesh->material->Update();

		//BoneIndex
		_shader->GetScalar("BoneIndex")->SetInt(mesh->boneIndex);

		uint32 stride = mesh->vertexBuffer->GetStride();
		uint32 offset = mesh->vertexBuffer->GetOffset();

		//각 매쉬를 버퍼에 할당
		DC->IASetVertexBuffers(0, 1, mesh->vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		DC->IASetIndexBuffer(mesh->indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

		_shader->DrawIndexed(0, _pass, mesh->indexBuffer->GetCount(), 0, 0);
	}
}

void ModelAnimator::SetModel(shared_ptr<Model> model)
{
	_model = model;

	const auto& materials = _model->GetMaterials();
	for (auto& material : materials)
	{
		material->SetShader(_shader);
	}
}

void ModelAnimator::CreateTexture()
{
	if (_model->GetAnimationCount() == 0)
		return;

	_animTransforms.resize(_model->GetAnimationCount());
	for (uint32 i = 0; i < _model->GetAnimationCount(); i++)
		CreateAnimationTransform(i);

	//CreateTexture
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
		desc.Width = MAX_MODEL_TRANSFORMS * 4;		//4칸으로 쪼개기
		desc.Height = MAX_MODEL_KEYFRAMES;
		desc.ArraySize = _model->GetAnimationCount();		//텍스처배열
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; // 16바이트
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;

		//한층
		const uint32 dataSize = MAX_MODEL_TRANSFORMS * sizeof(Matrix);
		//층을 프레임만큼
		const uint32 pageSize = dataSize * MAX_MODEL_KEYFRAMES;
		//애니메이션 개수만큼
		void* mallocPtr = ::malloc(pageSize * _model->GetAnimationCount());
	
		// 파편화된 데이터를 조립한다.
		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			uint32 startOffset = c * pageSize;

			//포인터 연산 - ~칸씩 앞으로 가기 때문에
			BYTE* pageStartPtr = reinterpret_cast<BYTE*>(mallocPtr) + startOffset;

			
			for (uint32 f = 0; f < MAX_MODEL_KEYFRAMES; f++)
			{
				void* ptr = pageStartPtr + dataSize * f;
				::memcpy(ptr, _animTransforms[c].transforms[f].data(), dataSize);
			}
		}

		// 리소스 만들기
		vector<D3D11_SUBRESOURCE_DATA> subResources(_model->GetAnimationCount());

		for (uint32 c = 0; c < _model->GetAnimationCount(); c++)
		{
			void* ptr = (BYTE*)mallocPtr + c * pageSize;
			subResources[c].pSysMem = ptr;
			subResources[c].SysMemPitch = dataSize;
			subResources[c].SysMemSlicePitch = pageSize;
		}

		//텍스처 배열이 전달된다.
		HRESULT hr = DEVICE->CreateTexture2D(&desc, subResources.data(), _texture.GetAddressOf());
		CHECK(hr);

		::free(mallocPtr);
	
	}

	// Create SRV
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		desc.Texture2DArray.MipLevels = 1;
		desc.Texture2DArray.ArraySize = _model->GetAnimationCount();

		HRESULT hr = DEVICE->CreateShaderResourceView(_texture.Get(), &desc, _srv.GetAddressOf());
		CHECK(hr);
	}
}

void ModelAnimator::CreateAnimationTransform(uint32 index)
{
	//캐싱용
	vector<Matrix> tempAnimBoneTransforms(MAX_MODEL_TRANSFORMS, Matrix::Identity);

	shared_ptr<ModelAnimation> animation = _model->GetAnimationByIndex(index);

	//프레임순회
	for (uint32 f = 0; f < animation->frameCount; f++)
	{
		//본 순회
		for (uint32 b = 0; b < _model->GetBoneCount(); b++)
		{
			shared_ptr<ModelBone> bone = _model->GetBoneByIndex(b);

			Matrix matAnimation;

			shared_ptr<ModelKeyframe> frame = animation->GetKeyframe(bone->name);
			if (frame != nullptr)
			{
				ModelKeyframeData& data = frame->transforms[f];

				Matrix S, R, T;
				S = Matrix::CreateScale(data.scale.x, data.scale.y, data.scale.z);
				R = Matrix::CreateFromQuaternion(data.rotation);
				T = Matrix::CreateTranslation(data.translation.x, data.translation.y, data.translation.z);
			
				matAnimation = S * R * T; 
			}
			else
			{
				matAnimation = Matrix::Identity;
			}

			// 처음 T 포즈기준
			Matrix toRootMatrix = bone->transform;
			Matrix invGlobal = toRootMatrix.Invert();

			int32 parentIndex = bone->parentIndex;
			
			Matrix matParent = Matrix::Identity;
			if(parentIndex>=0)
				matParent = tempAnimBoneTransforms[parentIndex];

			tempAnimBoneTransforms[b] = matAnimation * matParent;

			//기본-> 다른자세
			_animTransforms[index].transforms[f][b] = invGlobal * tempAnimBoneTransforms[b];
		}
	}
}
