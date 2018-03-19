#ifndef COLOR_H
#define COLOR_H

struct Color
{
	Color() {
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}

	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	float r;
	float g;
	float b;
	float a;
};

#endif // !COLOR_H
