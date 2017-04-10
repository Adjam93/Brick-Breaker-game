#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "ball.h"
#include "bat.h"
#include "PowerUps.h"
#include "Sounds.h"

extern Ball  ball;
extern Bat   bat;
extern Powers powers;
extern Sounds sounds;

extern int lifeCount;
extern bool powerBatIncrease; 
extern bool powerBallIncrease;
extern bool powerLifeIncrease;

void Powers::batIncreaseDraw()
{
	  glBegin(GL_QUADS); //Draw power up as square (four corners joined as GL_QUADS)
		  glVertex2f(powerBatX,powerBatY); // = Bottom left of square
		  glVertex2f(powerBatX+powerWH,powerBatY); //X + 0.12(WH), same given Y value = bottom right of square
		  glVertex2f(powerBatX+powerWH,powerBatY+powerWH);//X + 0.12(WH), Y + 0.12(WH) = top right of square
		  glVertex2f(powerBatX,powerBatY+powerWH); //Same given X vale, Y + 0.12(WH) = top left of square
	   glEnd();
}

void Powers::ballPowerDraw()
{
	  glBegin(GL_QUADS); //Draw power up as square (four corners joined as GL_QUADS)
		  glVertex2f(powerBallX,powerBallY); // = Bottom left of square
		  glVertex2f(powerBallX+powerWH,powerBallY); //X + 0.12(WH), same given Y value = bottom right of square
		  glVertex2f(powerBallX+powerWH,powerBallY+powerWH);//X + 0.12(WH), Y + 0.12(WH) = top right of square
		  glVertex2f(powerBallX,powerBallY+powerWH); //Same given X vale, Y + 0.12(WH) = top left of square
	   glEnd();
}

void Powers::lifePowerDraw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, heartID);

   // initialize textures
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	  glBegin(GL_QUADS); //Draw power up as square (four corners joined as GL_QUADS)

		  glTexCoord2f(0.0f, 0.0f);
		  glVertex2f(powerLifeX,powerLifeY); // = Bottom left of square

		  glTexCoord2f(1.0f, 0.0f);
		  glVertex2f(powerLifeX+powerWH,powerLifeY); //X + 0.12(WH), same given Y value = bottom right of square

		  glTexCoord2f(1.0f, 1.0f);
		  glVertex2f(powerLifeX+powerWH,powerLifeY+powerWH);//X + 0.12(WH), Y + 0.12(WH) = top right of square

		  glTexCoord2f(0.0f, 1.0f);
		  glVertex2f(powerLifeX,powerLifeY+powerWH); //Same given X vale, Y + 0.12(WH) = top left of square
	   glEnd();

	    // Specify filtering and wrap mode
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	glDisable(GL_TEXTURE_2D);
}

void Powers::powerCollisions()
{
	if( (abs(powers.powerBatY - bat.m_y - 1.0 * bat.m_height) <= 0.01) && 
		((bat.m_x - 0.5 * bat.m_width) <= powers.powerBatX) &&
		(powers.powerBatX <= (bat.m_x + 0.5 * bat.m_width))) //If powerup square hits the top of the bat
	 {
		if(powerBatIncrease) //If the bat increase boolean = true (hits the brick)
		{
			sounds.powerUpSound(); //Play the sound file for if a power up is collected
			bat.m_width = 2.0; //Increase the bats width
			powerBatIncrease = false; //Set the bat increase boolean to false (so it won't be drawn)
		}

	}

	if( (abs(powers.powerBallY - bat.m_y - 1.0 * bat.m_height) <= 0.01) && 
		((bat.m_x - 0.5 * bat.m_width) <= powers.powerBallX) &&
		(powers.powerBallX <= (bat.m_x + 0.5 * bat.m_width))) //If powerup square hits the top of the bat
	 {
		if(powerBallIncrease) //If the ball speed increase boolean = true (hits the brick)
		{
			sounds.powerUpSound();
			ball.m_vx = 0.0092; //Increase speed of the balls x and y velocity 
			ball.m_vy = 0.0092; //0.0088
			powerBallIncrease = false; //Set the ball speed increase boolean to false (so it won't be drawn)
		}

	}

	if( (abs(powers.powerLifeY - bat.m_y - 1.0 * bat.m_height) <= 0.01) && 
		((bat.m_x - 0.5 * bat.m_width) <= powers.powerLifeX) &&
		(powers.powerLifeX <= (bat.m_x + 0.5 * bat.m_width))) //If powerup square hits the top of the bat
	 {
		if(powerLifeIncrease) //If the life increase boolean = true (hits the brick)
		{
			sounds.powerUpSound();
			lifeCount += 1; //Increase player lives by one 
			powerLifeIncrease = false; //Set the life increase boolean to false (so it won't be drawn)
		}
	 }
}