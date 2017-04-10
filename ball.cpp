#include "stdafx.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "ball.h"

void Ball::Draw() {

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D , ballID);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	glPushMatrix();
	glTranslatef(m_x, m_y, 0);
	glutSolidSphere(m_r, 20, 20);
	glPopMatrix();

    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}