#ifndef POWERS_H
#define POWERS_H

class Powers {
public:
	
	  void batIncreaseDraw();
	  void ballPowerDraw();
	  void lifePowerDraw();
	  void powerCollisions();
	  Powers(){powerWH = 0.12;} //Defined width/height of powerup square

	  float powerBatX, powerBallX, powerLifeX;  //x position of power up
	  float powerBatY, powerBallY, powerLifeY; //y position of power up
	  
	  float power_vy; // Y Velocity of power up (Only Y needed as the power up only moves vertically)

	  GLuint heartID;

	  public:
		  float powerWH;
};
#endif