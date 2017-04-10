#ifndef BALL_H
#define BALL_H

class Ball {
public:
	float m_r;       // radius
	float m_x, m_y;  // centre

	float m_vx, m_vy; // velocity

	void Draw();

	GLuint ballID;
};
#endif