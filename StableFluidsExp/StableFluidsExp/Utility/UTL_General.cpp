/*
* UTL_Gneral.cpp
* Xue Cui
* 30th Jan, 2016
* Desc:
*
*/
#include "UTL_General.h"

using namespace VFXEpoch;

float VFXEpoch::RandomF(float min, float max){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> range(min, max);
	return range(gen);
}

int VFXEpoch::RandomI(int min, int max){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> range(min, max);
	return range(gen);
}

float VFXEpoch::Lerp(float t, float x0, float x1)
{
	return (1 - t) * x0 + t * x1;
}

float VFXEpoch::Bilerp(float t, float s, float x0, float x1, float y0, float y1)
{
	return VFXEpoch::Lerp(s, VFXEpoch::Lerp(t, x0, x1), VFXEpoch::Lerp(t, y0, y1));
}

void VFXEpoch::ExtractComponents(VFXEpoch::Grid2DfScalarField& component, VFXEpoch::Grid2DVector2DfField vectorField, VECTOR_COMPONENTS axis)
{
	if (component.getDimY() != vectorField.getDimY() ||
		component.getDimX() != vectorField.getDimX())
	{
		assert(component.getDimY() == vectorField.getDimY() && component.getDimX() != vectorField.getDimX());
	}
	else
	{
		switch (axis)
		{
		case VFXEpoch::VECTOR_COMPONENTS::X:
			for (int i = 0; i != component.getDimY(); i++){
				for (int j = 0; j != component.getDimX(); j++){
					component.setData(vectorField.getData(i, j).m_x, i, j);
				}
			}
			break;
		case VFXEpoch::VECTOR_COMPONENTS::Y:
			for (int i = 0; i != component.getDimY(); i++){
				for (int j = 0; j != component.getDimX(); j++){
					component.setData(vectorField.getData(i, j).m_y, i, j);
				}
			}
			break;
		case VFXEpoch::VECTOR_COMPONENTS::Z:
			break;
		default:
			for (int i = 0; i != component.getDimY(); i++){
				for (int j = 0; j != component.getDimX(); j++){
					component.setData(vectorField.getData(i, j).m_x, i, j);
				}
			}
			break;
		}
	}
}

void VFXEpoch::ExtractComponents(VFXEpoch::Grid2DfScalarField& component, VFXEpoch::Grid3DVector3DfField vectorField, VECTOR_COMPONENTS axis)
{

}

void VFXEpoch::InsertComponents(VFXEpoch::Grid2DfScalarField component, VFXEpoch::Grid2DVector2DfField& vectorField, VECTOR_COMPONENTS axis)
{
	if (component.getDimY() != vectorField.getDimY() ||
		component.getDimX() != vectorField.getDimX())
	{
		assert(component.getDimY() == vectorField.getDimY() && component.getDimX() != vectorField.getDimX());
	}
	else
	{
		VFXEpoch::Vector2Df vec(0.0f, 0.0f);
		switch (axis)
		{
		case VFXEpoch::VECTOR_COMPONENTS::X:
			for (int i = 0; i != component.getDimY(); i++){
				for (int j = 0; j != component.getDimX(); j++){
					vec = vectorField.getData(i, j);
					vec.m_x = component.getData(i, j);
					vectorField.setData(vec, i, j);
				}
			}
			break;
		case VFXEpoch::VECTOR_COMPONENTS::Y:
			for (int i = 0; i != component.getDimY(); i++){
				for (int j = 0; j != component.getDimX(); j++){
					vec = vectorField.getData(i, j);
					vec.m_y = component.getData(i, j);
					vectorField.setData(vec, i, j);
				}
			}
			break;
		case VFXEpoch::VECTOR_COMPONENTS::Z:
			break;
		default:
			break;
		}
	}
}

void VFXEpoch::InsertComponents(VFXEpoch::Grid2DfScalarField component, VFXEpoch::Grid3DVector3DfField& vectorField, VECTOR_COMPONENTS axis)
{

}

void VFXEpoch::Zeros(VFXEpoch::Grid2DfScalarField& field)
{
	for (int i = 0; i != field.getDimY(); i++)
	{
		for (int j = 0; j != field.getDimX(); j++)
		{
			field.setData(0.0f, i, j);
		}
	}
}

void VFXEpoch::Zeros(VFXEpoch::Grid2DVector2DfField& field)
{
	for (int i = 0; i != field.getDimY(); i++)
	{
		for (int j = 0; j != field.getDimX(); j++)
		{
			VFXEpoch::Vector2Df data(0.0f, 0.0f);
			field.setData(data, i, j);
		}
	}
}
