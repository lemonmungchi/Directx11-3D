#pragma once

class Viewport
{
public:
	Viewport();
	Viewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);
	~Viewport();

	void RSSetViewport();
	void Set(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);

	float GetWidth() { return _vp.Width; }
	float GetHeight() { return _vp.Height; }

	//2D-> 3D
	Vec3 Project(const Vec3& pos, const Matrix& W, const Matrix& V, const Matrix& P);
	//3D-> 2D
	Vec3 Unproject(const Vec3& pos, const Matrix& W, const Matrix& V, const Matrix& P);

private:
	D3D11_VIEWPORT _vp;
};