#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
	float x, y;
	
	Vector2() {
		this->x = 0;
		this->y = 0;
	}

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector2(int x, int y) {
		this->x = (float)x;
		this->y = (float)y;
	}

	Vector2& operator =(Vector2 vec) {
		this->x = vec.x;
		this->y = vec.y;
		return *this;
	}

	Vector2& operator +=(Vector2 vec) {
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	Vector2& operator -=(Vector2 vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		return *this;
	}

	Vector2& operator *=(Vector2 vec) {
		this->x *= vec.x;
		this->y *= vec.y;
		return *this;
	}

	Vector2& operator *=(float val) {
		this->x *= val;
		this->y *= val;
		return *this;
	}

	Vector2 operator +(Vector2 val) const {
		Vector2 res = (*this);
		res.x += val.x;
		res.y += val.y;
		return res;
	}

	Vector2 operator -(Vector2 val) const {
		Vector2 res = (*this);
		res.x -= val.x;
		res.y -= val.y;
		return res;
	}

	Vector2 operator /(float val) const {
		Vector2 res = (*this);
		res.x /= val;
		res.y /= val;
		return res;
	}

	Vector2 operator *(float val) const {
		Vector2 res = (*this);
		res.x *= val;
		res.y *= val;
		return res;
	}
};

#endif // !VECTOR2_H
