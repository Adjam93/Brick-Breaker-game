#ifndef BRICK_H
#define BRICK_H

class Brick {
public:
	float m_x , m_y;   // center of the brick
	float m_height, m_width; // dim

	int life;  // life of the brick;
    void Draw(GLuint &ID);
	void setLevel();

	void drawLayout1();
	void drawLayout2();
	void drawLayout3();

	GLuint brickID;
	GLuint brick2ID;
};
#endif