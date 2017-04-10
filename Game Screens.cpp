#include "stdafx.h"
#include <Windows.h>
#include <math.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "Game Screens.h"

void Screens::start_screen()
{
	glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, startID);
			
   // initialize textures
 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_POLYGON);
 
     glTexCoord2f(0.0f, 0.0f);
      glVertex3f(-4.12f, -2.055, 0.0);
     glTexCoord2f(1.0f, 0.0f);
      glVertex3f(4.12f, -2.055f, 0.0);
     glTexCoord2f(1.0f, 1.0f);
      glVertex3f(4.12f, 2.055f, 0.0);
     glTexCoord2f(0.0f, 1.0f);
      glVertex3f(-4.12f, 2.055f, 0.0);;
    
    glEnd();

    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
}

void Screens::game_over_screen()
{
	glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, endID);
			
   // initialize textures
 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_POLYGON);
 
     glTexCoord2f(0.0f, 0.0f);
      glVertex3f(-4.10f, -2.0f, 0.0);
     glTexCoord2f(1.0f, 0.0f);
      glVertex3f(4.10f, -2.0f, 0.0);
     glTexCoord2f(1.0f, 1.0f);
      glVertex3f(4.10f, 2.0f, 0.0);
     glTexCoord2f(0.0f, 1.0f);
      glVertex3f(-4.10f, 2.0f, 0.0);
    
    glEnd();

    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
}

void Screens::game_win_screen()
{
	glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, winID);
			
   // initialize textures
 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBegin(GL_POLYGON);
 
     glTexCoord2f(0.0f, 0.0f);
      glVertex3f(-4.14f, -2.075, 0.0);
     glTexCoord2f(1.0f, 0.0f);
      glVertex3f(4.14f, -2.075f, 0.0);
     glTexCoord2f(1.0f, 1.0f);
      glVertex3f(4.14f, 2.075f, 0.0);
     glTexCoord2f(0.0f, 1.0f);
      glVertex3f(-4.14f, 2.075f, 0.0);
    
    glEnd();

    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
}

void Screens::background()
{
	glEnable(GL_TEXTURE_2D);

   // glBindTexture(GL_TEXTURE_2D, backgroundID);
			
   // initialize textures
 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBegin(GL_POLYGON);
 
     glTexCoord2f(0.0f, 0.0f);
      glVertex3f(-4.12f, -2.055, 0.0);
     glTexCoord2f(1.0f, 0.0f);
      glVertex3f(4.12f, -2.055f, 0.0);
     glTexCoord2f(1.0f, 1.0f);
      glVertex3f(4.12f, 2.055f, 0.0);
     glTexCoord2f(0.0f, 1.0f);
      glVertex3f(-4.12f, 2.055f, 0.0);
    
    glEnd();

    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
}