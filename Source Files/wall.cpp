#include "stdafx.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "wall.h"

void Wall::Draw()
{
      glLineWidth(4.0);  //Set line width of following line loop

	  glBegin(GL_LINE_LOOP);  //start drawing a line loop
         glVertex3f(-4.14, -2.065, 0.0);   //left of window
         glVertex3f(4.14, -2.065, 0.0);   //bottom of window
         glVertex3f(4.14, 2.065, 0.0);   //right of window
         glVertex3f(-4.14, 2.065, 0.0); //top of window
      glEnd();  //end drawing of line loop
}