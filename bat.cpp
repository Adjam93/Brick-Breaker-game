#include "stdafx.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "bat.h"

void Bat::Draw()
{	
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, batID);
   
	// initialize textures
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBegin(GL_QUADS);
 
     glTexCoord2f(0.0f, 0.0f); //lower left UV tex coordinates and lower left of bat
      glVertex3f(m_x - m_width / 2.0, m_y - m_height / 2.0, 0.0);

     glTexCoord2f(1.0f, 0.0f); //lower right UV tex coordinates and lower right of bat
      glVertex3f(m_x + m_width / 2.0, m_y - m_height / 2.0, 0.0);

     glTexCoord2f(1.0f, 1.0f); //upper right UV tex coordinates and upper right of bat
      glVertex3f(m_x + m_width / 2.0, m_y + m_height / 2.0, 0.0);

     glTexCoord2f(0.0f, 1.0f); //upper left UV tex coordinates and upper left of bat
      glVertex3f(m_x - m_width / 2.0, m_y + m_height / 2.0, 0.0);
    
    glEnd();

    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
}