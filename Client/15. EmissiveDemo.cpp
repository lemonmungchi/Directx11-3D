#include "pch.h"
#include "15. EmissiveDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"

void EmissiveDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"12. Lighting_Emissive.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f,0.f,-10.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	//Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		//Texture
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}

	//Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{ 0.5f,0.f,2.f });
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh2 = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh2);
	}
	{
		//Texture
		auto texture2 = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		_obj2->GetMeshRenderer()->SetTexture(texture2);
	}

	RENDER->Init(_shader);
}

void EmissiveDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		//빨간색만 받아주기
		Vec4 materialEmissive(1.f, 0.f, 0.f, 1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialEmissive);
		_obj->Update();
	}

	{
		Vec4 materialEmissive(0.f, 1.f, 0.f, 1.f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialEmissive);
		_obj2->Update();
	}
	
}

void EmissiveDemo::Render()
{
	
}
