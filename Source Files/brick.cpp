#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
#include "brick.h"
#include "wall.h"

extern const int numofbricks = 66;
extern Wall wall;
extern Brick bricks[numofbricks];

void Brick::Draw(GLuint &ID)
{
	glEnable(GL_TEXTURE_2D);

   // initialize textures
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	if (life > 0) {
				     glBegin(GL_QUADS);
 
					 glTexCoord2f(0.0f, 0.0f); //lower left UV tex coordinates and lower left of brick
					  glVertex3f(m_x - m_width / 2.0, m_y - m_height / 2.0, 0.0);

					 glTexCoord2f(1.0f, 0.0f); //lower right UV tex coordinates and lower right of brick
					  glVertex3f(m_x + m_width / 2.0, m_y - m_height / 2.0, 0.0);

					 glTexCoord2f(1.0f, 1.0f); //upper right UV tex coordinates and upper right of brick
					  glVertex3f(m_x + m_width / 2.0, m_y + m_height / 2.0, 0.0);

					 glTexCoord2f(0.0f, 1.0f); //upper left UV tex coordinates and upper left of brick
					  glVertex3f(m_x - m_width / 2.0, m_y + m_height / 2.0, 0.0);
    
					 glEnd();
				}

    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
}

void Brick::drawLayout1()
{	
		float w = 0.72;
		float h = 0.15;
		float gap_x = 0.03;
		float gap_y = 0.20;

		 for (int i = 0; i < numofbricks; i++)
		 {	
				bricks[i].life = 1;
				bricks[i].m_height = h;
				bricks[i].m_width  = w;
				bricks[i].m_x = -3.75 + i * (w + gap_x);
				bricks[i].m_y = 1.95;

				if (bricks[i].m_x > wall.right)
				{
					do{
					   bricks[i].m_x += -8.25;
					   bricks[i].m_y -= gap_y;
					}
					while(bricks[i].m_x > wall.right);
				}

				 if (i < 11 || i >=11 && i < 22)
						{
							bricks[i].life = 2;
						}
			}
}

void Brick::drawLayout2()
{	
		float w = 0.72;
		float h = 0.15;
		float gap_x = 0.03;

			 for (int i = 0; i < numofbricks; i++)
					{				
							bricks[i].life = 1;
							bricks[i].m_height = h;
							bricks[i].m_width  = w;
							bricks[i].m_x = -3.75 + i * (w + gap_x);
							bricks[i].m_y = 1.95;

					   /* if (i>=0 && i<=10)
						{
								//bricks[i].m_x += -8.25;
								bricks[i].m_y = 1.95;
						}*/
   						if (i>10 && i<=19)
						{
							bricks[i].m_x += -7.50;
							bricks[i].m_y = 1.75;
							bricks[i].life = 2;
						}
   						if (i>19 && i<=28)
						{
							bricks[i].m_x += -14.25;
							bricks[i].m_y = 1.55;
							bricks[i].life = 2;
						}
   						if (i>29 && i<=36)
						{
							bricks[i].m_x += -21.00;
							bricks[i].m_y = 1.35;
						}
						if (i>39 && i<=44)
						{
							bricks[i].m_x += -27.75;
							bricks[i].m_y = 1.15;
						}
						if (i>49 && i<=52)
						{
							bricks[i].m_x += -34.50;
							bricks[i].m_y = 0.95;
						}
						if (i==60)
						{
							bricks[i].m_x += -41.25;
							bricks[i].m_y = 0.75;
						}
				}
}


void Brick::drawLayout3()
{

	float w = 0.72;
	float h = 0.15;
	float gap_x = 0.03;
	//float gap_y = 0.20;

		 for (int i = 0; i < numofbricks; i++)
                {
					    bricks[i].life = 1;
						bricks[i].m_height = h;
						bricks[i].m_width  = w;
						bricks[i].m_x = -3.75 + i * (w + gap_x);
						bricks[i].m_y = 1.95;

   					if (i>10 && i<=19)
					{
						bricks[i].m_x += -7.50;
						bricks[i].m_y = 1.75;
						bricks[i].life = 2;
					}
   					if (i>19 && i<=30)
					{
						bricks[i].m_x += -15.00;
						bricks[i].m_y = 1.55;
					}
   					if (i>30 && i<=35)
					{
						bricks[i].m_x += -21.00;
						bricks[i].m_y = 1.35;
						bricks[i].life = 2;
					}
					if (i>36 && i<=47)
					{
						bricks[i].m_x += -27.75;
						bricks[i].m_y = 0.95;
						bricks[i].life = 2;
					}
					if (i>49 && i<=52)
					{
						bricks[i].m_x += -34.50;
						bricks[i].m_y = 0.75;				
					}
					if (i==60)
					{
						bricks[i].m_x += -41.25;
						bricks[i].m_y = 0.55;
					}
                }
}