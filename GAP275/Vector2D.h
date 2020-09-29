// Vector2D.h
// Zixuan Shi
// Vector in 2D utils

#pragma once

//////////////////////////////
// A two-dimensional vector.
//////////////////////////////
class Vector2D
{
public:
	double m_x;
	double m_y;

public:
	Vector2D(double x, double y);
	Vector2D();

	Vector2D Add(Vector2D& other);
	Vector2D Subtract(Vector2D& other);
	double GetMagnitude();
	double GetMagnitude(Vector2D& other);
	Vector2D Normalize();
	Vector2D ScalarMultiply(double scale);
	double DotProduct(Vector2D& other);
	double GetSquareLength();

	////////////////////
	//float Rotate();
	void Lerp(Vector2D otherVec, float value);
	Vector2D Lerp(Vector2D vecOne, Vector2D vecTwo, float value);

	double GetX() const { return m_x; }
	double GetY() const { return m_y; }

	void SetX(double x) { m_x = x; }
	void SetY(double y) { m_x = y; }
	void SetVector(double x, double y) { m_x = x; m_y = y; }

	void AddToX(double x) { m_x += x; }
	void AddToY(double y) { m_y += y; }

	Vector2D operator*=(double value);
	Vector2D operator+=(Vector2D& otherVector);
	Vector2D operator*(double value);
};