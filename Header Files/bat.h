#ifndef BAT_H
#define BAT_H

class Bat {
public:
	Bat(){m_height = 0.12; m_width = 1.0; }
	void setPosition(double x, double y){ m_x = x; m_y = y;}
	void Draw();

public:
	float m_x, m_y;          // center of the bat
	float m_height, m_width; // dimensions
	GLuint batID;
};
#endif
