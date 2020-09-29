// Vector2D.cpp
// Zixuan Shi
// Vector in 2D utils

#include "Vector2D.h"

#include <math.h>
#include <iostream>

Vector2D::Vector2D(double x, double y)
	: m_x{ x }
	, m_y{ y }
{
}

Vector2D::Vector2D()
	: m_x{ 0 }
	, m_y{ 0 }
{
}

Vector2D Vector2D::Add(Vector2D& other)
{
	Vector2D newVector;

	newVector.m_x = this->m_x + other.m_x;
	newVector.m_y = this->m_y + other.m_y;

	return newVector;
}

Vector2D Vector2D::Subtract(Vector2D& other)
{
	Vector2D newVector;

	newVector.m_x = this->m_x - other.m_x;
	newVector.m_y = this->m_y - other.m_y;

	return newVector;
}

////////////////////////////////////////
// The magnitude from 0,0 to the vector
////////////////////////////////////////
double Vector2D::GetMagnitude()
{
	return sqrt((this->m_x * this->m_x) + (this->m_y * this->m_y));
}

////////////////////////////////////////
// Squared length
////////////////////////////////////////
double Vector2D::GetSquareLength()
{
	return (this->m_x * this->m_x) + (this->m_y * this->m_y);
}

////////////////////////////////////////
// Find lerp
////////////////////////////////////////
void Vector2D::Lerp(Vector2D otherVec, float value)
{
	// check input
	if (value < 0 || value > 1)
	{
		std::cout << "\nError: Invalid input for lerping.\n";
	}

	this->m_x = this->m_x + (abs(this->m_x - otherVec.m_x) * value);
	this->m_y = this->m_y + (abs(this->m_y - otherVec.m_y) * value);
}

////////////////////////////////////////
// Find lerp
////////////////////////////////////////
Vector2D Vector2D::Lerp(Vector2D vecOne, Vector2D vecTwo, float value)
{
	// check input
	if (value < 0 || value > 1)
	{
		std::cout << "\nError: Invalid input for lerping.\n";
		return Vector2D{};
	}

	return Vector2D{ vecOne.m_x + (abs(vecOne.m_x - vecTwo.m_x) * value), vecOne.m_y + (abs(vecOne.m_y - vecTwo.m_y) * value) };
}

////////////////////////////////////////
// The magnitude of two vectors
////////////////////////////////////////
double Vector2D::GetMagnitude(Vector2D& other)
{
	return sqrt((this->m_x - other.m_x) * (this->m_x - other.m_x) + (this->m_y - other.m_y) * (this->m_y - other.m_y));
}

Vector2D Vector2D::Normalize()
{
	double length = GetMagnitude();

	if (length == 0)
	{
		return Vector2D{};
	}
	else
	{
		return Vector2D{ (this->m_x / length),  (this->m_y / length) };
	}
}

Vector2D Vector2D::ScalarMultiply(double scale)
{
	Vector2D newVector;

	newVector.m_x = this->m_x * scale;
	newVector.m_y = this->m_y * scale;

	return newVector;
}

double Vector2D::DotProduct(Vector2D& other)
{
	return (this->m_x * other.m_x) + (this->m_y * other.m_y);
}

Vector2D Vector2D::operator*=(double value)
{
	m_x *= value;
	m_y *= value;
	return *this;
}

Vector2D Vector2D::operator+=(Vector2D& otherVector)
{
	m_x += otherVector.m_x;
	m_y += otherVector.m_y;
	return *this;
}

Vector2D Vector2D::operator*(double value)
{
	m_x *= value;
	m_y *= value;
	return *this;
}

