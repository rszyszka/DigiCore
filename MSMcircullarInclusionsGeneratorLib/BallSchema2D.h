#pragma once

class BallSchema2D
{
private:
	const int size;
	bool** schema;
	~BallSchema2D();
public:
	__declspec(dllexport) BallSchema2D(int radius);
	__declspec(dllexport) const int getSize();
	__declspec(dllexport) bool** getSchema();
};