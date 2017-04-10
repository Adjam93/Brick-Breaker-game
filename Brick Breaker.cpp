#include "stdafx.h"
#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include <fstream>
#include <random>     
#include <time.h>     
#include "glut.h"
#include "ball.h"
#include "bat.h"
#include "brick.h"
#include "wall.h"
#include "Game Screens.h"
#include "imageloader.h"
#include "PowerUps.h"
#include "Sounds.h"

void display();
void reshape(int w, int h);
void idle();
void init();
void drawCursor();
void moveBall();
void reset();
void PowerUps();
void brickCollisions();
void batCollisions();
void set_level();
void reset();
void Timer(int value);
void PowerTimer();
void loadTexture(const char* filename, GLuint &ID);
void text();
void printtext(float x, float y, std::string String);
void PrintWinScreen(float x, float y, std::string String);
void WinScreenMessage();

const int numofbricks = 66;

float bat_pos = 0.0f;
int lifeCount = 3;
int scoreCount = 0;
int totalBricks = 227; //88 for level 1 88+63 = 151 for level 2 // 151+76 = 227 for level 3
int interval = 1000 / 60;

bool paused = false;         // Movement paused or resumed
float ball_xSpeedSaved, ball_ySpeedSaved, bat_xMoveSaved, power_moveSaved;  // To support resume
bool batMove = true;
bool gameRunning = false;
bool Start_Screen = true;
bool game_over_screen = false, win_screen = false;
bool powerBatIncrease = false, powerBallIncrease = false, powerLifeIncrease = false;
static bool bat_timer = false;

Ball  ball;
Bat   bat;
Wall  wall;
Brick *brickLayout;
Brick bricks[numofbricks];
Screens screens;
Powers powers;
Sounds sounds;

void moveBat()
{
		if(GetAsyncKeyState(VK_LEFT) && !Start_Screen && !game_over_screen && !win_screen)
	   //If the left arrow key is pressed and no screens are displaying, increase the bat position left
		{
			bat_pos -= 0.060; //Decrease bat_pos to move left

			  //if game is not running, then move the ball along  with the bat
				if(!gameRunning) 
				{
						ball.m_x -= 0.060;

					if (ball.m_x < -3.62 ) //If the balls x position is less than -3.62....
						{
						  ball.m_x = -3.62; //....stop it moving
						}   /*This is necessary in order so that the ball will always be fired from the bat,
				 }           *otherwise if it's not on the bat, the ball will go down the y axis on restart,
				             *reducing lives and the score count*/
		}

			if (bat_pos < -3.62 ) //If the left x bat position is less than the x wall position
			{
			  bat_pos = -3.62; //Put the bat back if its x pos. gets less than the wall x pos.(-3.62)
			}

			if (bat.m_width == 2.0 && bat_pos < -3.13 ) //If the bat increase power up has changed the bats width
				{
				  bat_pos = -3.13; //Stop the bat moving past the wall, with its increased size
				}  
		}

		if(GetAsyncKeyState(VK_RIGHT) && !Start_Screen && !game_over_screen && !win_screen) 
			//If the right arrow key is pressed and no screens are displaying, increase the bat position right
		{
			bat_pos += 0.060; //Increase bat_pos to move right
		    
				if(!gameRunning )   //if game is not running,then move the ball along  with the bat
				{
					ball.m_x += 0.060;

					if (ball.m_x > 3.62 )  //If the balls x position is greater than 3.62....
						{
						  ball.m_x = 3.62; //....stop it moving 
						}
				 }

			if (bat_pos > 3.62 ) //If the right x bat position. is greater than the x wall position.
			{
			  bat_pos = 3.62; //Put the bat back if its x pos. gets greater than the wall x pos.(3.62) 
			}  

			if (bat.m_width == 2.0 && bat_pos > 3.13 ) 
			{
			  bat_pos = 3.13; 
			}  
		}

		if(batMove) //If bat move is true -> move bat. If false (when paused) don't move bat
		{
		   bat.m_x = +bat_pos;
		}
}

void keyboardInput(unsigned char key, int x, int y){

	//Function to exit program when escape key is pressed 
	switch(key){
	
	case 13: //Enter key pressed 
		 
		if(Start_Screen)
		{
		 // glDisable(GL_TEXTURE_2D); //Disable the texture (image of start screen) to start the game
	      Start_Screen = false; //Start screen set to false, to remove drawing of polygon which texture is bound to.
		}
		if(game_over_screen) //If all lives lost game over screen is true and displayed
		{
			game_over_screen = false; //Enter key pressed: game over screen set to false
			lifeCount = 3; //Life count reset to 5
			scoreCount = 0; //Score count reset to 0
			totalBricks = 227; //Bricks counter reset to 227
			brickLayout->drawLayout1(); //Reset layout 1 (1st level)
		}

		if(win_screen) //If all lives lost game over screen is true and displayed
		{
			win_screen = false; //Enter key pressed: win screen set to false
			lifeCount = 3; 
			scoreCount = 0;
			totalBricks = 227;
			brickLayout->drawLayout1(); //Reset layout 1 (1st level)
		}

		if(lifeCount != 0)
		{
			gameRunning = true; 
		    //sets gameRunning to true so that moveBall function will be run in idle function...
			//...and game can be started/restarted
		}
		break;

	case 'p': case'P':
		paused = !paused;       // Toggle pause
		batMove = !batMove;     // Toggle batMove, to stop bat movement when paused
      if (paused) //If pause boolean is true
	  {            
         ball_xSpeedSaved = ball.m_vx;  // Save current ball velocity
         ball_ySpeedSaved = ball.m_vy;
		 bat_xMoveSaved = bat_pos; //Save current bat position
         ball.m_vx = 0.0;      // Stop movement
         ball.m_vy = 0.0;
		 bat_pos = 0.0;     //Stop bat movement
		 power_moveSaved = powers.power_vy; //Save current position of any power ups
		 powers.power_vy = 0.0; //Stop any power ups moving
      } else 
	  {
        ball.m_vx = ball_xSpeedSaved;  // Restore velocity
        ball.m_vy = ball_ySpeedSaved;
		bat_pos = bat_xMoveSaved;  //Restore bat movement
		powers.power_vy = power_moveSaved; //Restore power up movement
      }
	  break;

	case 27: // 27 = Escape key
		 exit(0);
	}
}

int main(int argc, char* argv[])
{
	// initialize glut
	glutInit(&argc, argv);

	// initialize window position
	glutInitWindowPosition(100, 100);
	
	// window size
	glutInitWindowSize(1200, 600);

	// display mode
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// create a window
	glutCreateWindow(argv[0]);
	glutSetWindowTitle("Brick Breaker");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
    glutKeyboardFunc(keyboardInput);
	glutTimerFunc(interval, Timer, 0);

	// and then initialize the graphics
	init();
	
	// glut main loop
	glutMainLoop();

	return 0;
}

void reset()
{
	ball.m_y = -1.83; //Reset ball position
	ball.m_x = 0.0; 

	bat_pos = 0.0;    //Reset bat position
	bat.m_x = 0.0;

	powerBatIncrease = false; //Any power ups falling at the same time as game over/won will be removed
	bat.m_width = 1.0; //Reset effects of any power ups.

	powerBallIncrease = false;
	ball.m_vx = 0.0065; //Reset effects of any power ups.
	ball.m_vy = 0.0065;

	powerLifeIncrease = false;
}

void moveBall()
{
	 //float delta_t = 1.35;
	 ball.m_x += ball.m_vx;// * delta_t; //Move the ball on x axis
	 ball.m_y += ball.m_vy;// * delta_t; //move the ball on y axis

		   if ( ball.m_x < wall.left ) //Check if the ball hits the left wall
			{
			  ball.m_vx = -ball.m_vx; //Send the ball back across the x axis to the right
			}
 
          if ( ball.m_x > wall.right) //Check if the ball hits the right wall
			{
			  ball.m_vx = -ball.m_vx; //Send the ball back across the x axis to the left
			}
 
          if ( ball.m_y > wall.top ) //Check if the ball hits the top wall
			{
			  ball.m_vy = -ball.m_vy; //Send the ball back down the y axis
			}

	      if (ball.m_y < wall.bottom) //Check if the ball hits the bottom wall
		    {
				gameRunning = false;  //Set gameRunning boolean to false, so that moveBall function won't be run

				lifeCount -= 1;  //Descrease lives total by one
				scoreCount -= 20; //Reduce score if life lost
				bat_timer = false; //Reset boolean to false, in order to recalculate start time for bat increase power up

				reset(); //Call reset function, in order to reset ball/bat positions and remove any power ups

				if(totalBricks != 0) //Don't play sound if all bricks are hit and win message is being displayed
				{
					sounds.lifeLostSound(); //Play the sound file for if a life is lost
				}

					if(lifeCount < 1)
					{ 
						sounds.GameOverSound(); //If all lives lost play game over sound
					}	
             }
}

void PowerUps()
{
	//If brick with power up is hit
	  if (powerBatIncrease)
	     {powers.powerBatY -= powers.power_vy;} //Negate the power up velocity, to move the power up square down the Y axis	 

	  if(powerBallIncrease)
	    {powers.powerBallY -= powers.power_vy;}

	  if(powerLifeIncrease)
	    {powers.powerLifeY -= powers.power_vy;}


		if(powers.powerBatY < wall.bottom) //If the power up misses the bat and goes to the bottom wall
			{
				if(powerBatIncrease)
					{
						powerBatIncrease = false; //Set the power up from true to false, so it won't be drawn
					}
		    }

		if(powers.powerBallY < wall.bottom) //If the power up misses the bat and goes to the bottom wall
			{
				if(powerBallIncrease)
					{
						powerBallIncrease = false;
					}
				}

			if(powers.powerLifeY < wall.bottom) //If the power up misses the bat and goes to the bottom wall
			{
				if(powerLifeIncrease)
				{
					powerLifeIncrease = false;
				}
			}
}

void Timer(int value)
{
	moveBat(); //Call function to move the bat

	if(lifeCount < 1) //If all lives gone
	{
		game_over_screen = true; //Set boolean to true, allowing game over screen to be displayed
	}

	if(totalBricks == 0) //If all bricks have been hit
	{
		win_screen = true; //Set win screen boolean to true, so it will be drawn in display function

		reset(); //Call reset function, in order to reset ball/bat positions and remove any power ups
	}

	PowerTimer(); //Call power timer function, for handling time of bat increase power up

	glutTimerFunc(interval, Timer, 0);	//Allow the bat to move on constant timer intervals (1000/60 = every 16.6 milliseconds)
	glutPostRedisplay(); //Recall display function
}

void PowerTimer()
{
	/*Time variables and boolean bat_timer(global variable) declared static, so that when width is changing,
	 * any changes to the variables are not reset*/

	static time_t start_time, current_time;

	if(bat.m_width == 2.0) //If bat power up has increased bat size
	 {
		 if(bat_timer == false) //bat_timer boolean is false at start
		 {
			 time(&start_time); //Get the start time of bat increase
			 bat_timer = true;	 //Set bat_timer to true
		 }

		 time(&current_time); //Get current time elapsed

		 time_t d_t = current_time - start_time; //d_t time is current - start time (of bat increase), so its value will be 0
		 std::cout << d_t << std::endl;

		 if(d_t > 19) //If d_t time is over 19 seconds (20 seconds)
		 {
			 bat.m_width = 1.0; //Reset bat width (power up effect lost)
			 std::cout << d_t << std::endl;
			 bat_timer = false; //bat_timer set to false;
		 }
	 }
}


void brickCollisions()
{
	int min = 0; //Minimum number of bricks array
	int max = 65; //Max number of bricks array
	std::random_device rand;     //Only used once to initialise engine
	std::mt19937 generate(rand);      //Random-number engine used
	std::uniform_int_distribution<int> uni(min,max); //Guaranteed unbiased
	auto random_integer = uni(generate); 

	//Ball and Brick collisions
	for (int i = 0; i < numofbricks; i++){

		/*TOP, BOTTOM, RIGHT & LEFT COLLISIONS*/	                                      
		//Ball hits brick on the top
		if( (abs(ball.m_y - bricks[i].m_y - 0.5 * bricks[i].m_height) <= 0.01) && 
		((bricks[i].m_x - 0.5 * bricks[i].m_width) <= ball.m_x) &&
		(ball.m_x <= (bricks[i].m_x + 0.5 * bricks[i].m_width))) 
	{
		if(bricks[i].life != 0) //If the brick is still on screen
			{
              ball.m_vy = -ball.m_vy;  //Invert velocity of ball
		      bricks[i].life -= 1;    //Remove brick (life = 0)
			  scoreCount += 10; //Increase score count by 10 
			  totalBricks -= 1; //Decrease bricks counter
			  sounds.soundBrick(); //Play the sound file for when a brick is hit
			 
			  if(i == uni(generate)) //i = a randomly generated int from 0 - 65 (for one of the bricks displayed)
			  {
				  powers.powerBatX = bricks[i].m_x; powers.powerBatY = bricks[i].m_y; 
				  powerBatIncrease = true; 
				  //Set bat increase to true (so it will be drawn) and drop it from the centre of the brick the ball hits
			  }

			  if (i == uni(generate))
			  {
				  powers.powerBallX = bricks[i].m_x-0.08; powers.powerBallY = bricks[i].m_y; 
				  powerBallIncrease = true;
			  }

			  if (i == uni(generate))
			  {
				  powers.powerLifeX = bricks[i].m_x+0.08; powers.powerLifeY = bricks[i].m_y; 
				  powerLifeIncrease = true;
			  }

			  /*The above if statments use the random numbers generated (from the C++ engine from 0(min) - 65(max))
			   *so that the power ups are randomly distributed, for when the ball hits the brick on top, left, right
			   *or bottom. The ball speed and life powerups are offset slightly from the centre of the brick that they drop from,
			   *so that in the case that the random number is the same for two or more powerups, they can all be shown*/
			}
	}
	// Ball hits brick underneath
	if( (abs(ball.m_y - bricks[i].m_y + 0.5 * bricks[i].m_height) <= 0.01) && 
		((bricks[i].m_x - 0.5 * bricks[i].m_width) <= ball.m_x) &&
		(ball.m_x <= (bricks[i].m_x + 0.5 * bricks[i].m_width)))
	{
		if(bricks[i].life != 0)
			{
			 ball.m_vy = -ball.m_vy;
			 bricks[i].life -= 1;
			 scoreCount += 10;
			 totalBricks -= 1;
			 sounds.soundBrick();
			
			 //i = a randomly generated int from 0 - 65 (for three of the bricks displayed)
			  if(i == uni(generate) || i == uni(generate) || i == uni(generate)) 
			  {
				 powers.powerBatX = bricks[i].m_x; powers.powerBatY = bricks[i].m_y; 
			     powerBatIncrease = true;
			  }

			  if (i == uni(generate) || i == uni(generate) || i == uni(generate))
			     {
					 powers.powerBallX = bricks[i].m_x-0.08; powers.powerBallY = bricks[i].m_y; 
					 powerBallIncrease = true;
				 }

			  if (i == uni(generate) || i == 65)
			     {
					 powers.powerLifeX = bricks[i].m_x+0.08; powers.powerLifeY = bricks[i].m_y; 
					 powerLifeIncrease = true;
			     }
		    }
	}
	// Ball hits brick on the right
	if ( (abs(ball.m_x - bricks[i].m_x + 0.5 * bricks[i].m_width) <= 0.01) &&
		((bricks[i].m_y - 0.5 * bricks[i].m_height) <= ball.m_y) &&
		(ball.m_y <= (bricks[i].m_y + 0.5 * bricks[i].m_height)))
	{
		if(bricks[i].life != 0)
			{
			 ball.m_vx = -ball.m_vx;
			 bricks[i].life -= 1;
			 scoreCount += 10;
			 totalBricks -= 1;
			 sounds.soundBrick(); 
			   
			  if(i == uni(generate)) 
			  {
				  powers.powerBatX = bricks[i].m_x; powers.powerBatY = bricks[i].m_y; 
				  powerBatIncrease = true;
			  }

			  if (i == uni(generate)) 
			  {
				  powers.powerBallX = bricks[i].m_x-0.08; powers.powerBallY = bricks[i].m_y; 
				  powerBallIncrease = true;
			  }

			  if (i == uni(generate))
			  {
				  powers.powerLifeX = bricks[i].m_x+0.08; powers.powerLifeY = bricks[i].m_y; 
				  powerLifeIncrease = true;
			  }
		}
	}
	//Ball hits brick on the left
	if ( (abs(ball.m_x - bricks[i].m_x - 0.5 * bricks[i].m_width) <= 0.01) &&
		((bricks[i].m_y - 0.5 * bricks[i].m_height) <= ball.m_y) &&
		(ball.m_y <= (bricks[i].m_y + 0.5 * bricks[i].m_height)))
	{
		if(bricks[i].life != 0)
			{
		      ball.m_vx = -ball.m_vx;
		      bricks[i].life -= 1;
			  scoreCount += 10;
			  totalBricks -= 1;
			  sounds.soundBrick();
				
			  if(i == uni(generate))
			  {
				  powers.powerBatX = bricks[i].m_x; powers.powerBatY = bricks[i].m_y; 
				  powerBatIncrease = true;
			  }

			  if (i == uni(generate))
			  {
				  powers.powerBallX = bricks[i].m_x-0.08; powers.powerBallY = bricks[i].m_y; 
				  powerBallIncrease = true;
			  }

			   if (i == uni(generate))
			   {
				   powers.powerLifeX = bricks[i].m_x+0.08; powers.powerLifeY = bricks[i].m_y; 
			       powerLifeIncrease = true;
			   }
		    }
	  }

	    /*FLOAT VARIABLES FOR EACH CORNER OF THE BRICKS*/
		float Y_tr = bricks[i].m_y + (bricks[i].m_height / 2.0); //TOP RIGHT CORNER
		float X_tr = bricks[i].m_x + (bricks[i].m_width / 2.0); 

		float Y_tl = bricks[i].m_y + (bricks[i].m_height / 2.0); //TOP LEFT CORNER
		float X_tl = bricks[i].m_x - (bricks[i].m_width / 2.0); 
		
		float Y_bl = bricks[i].m_y - (bricks[i].m_height / 2.0); //BOTTOM LEFT CORNER
		float X_bl = bricks[i].m_x - (bricks[i].m_width / 2.0); 

		float Y_br = bricks[i].m_y - (bricks[i].m_height / 2.0); //BOTTOM RIGHT CORNER
		float X_br = bricks[i].m_x + (bricks[i].m_width / 2.0); 

		float error = ball.m_r / 2.0;

		//CORNER COLLISIONS START

		// Left bottom corner
		if ((-error < Y_bl - ball.m_y - ball.m_r < error) &&
			(-error < X_bl - ball.m_x - ball.m_r < error) &&
			ball.m_y < Y_bl &&
			ball.m_x < X_bl)
        {
			if(bricks[i].life != 0)
			{
				ball.m_vx = -ball.m_vx;
				ball.m_vy = -ball.m_vy;
				bricks[i].life -= 1;
				scoreCount += 10;  
			    totalBricks -= 1; 
			    sounds.soundBrick(); 
				std::cout << "Corner hit at Brick: " <<  i << std::endl; //Debug information to print to console
			}
		}
		// Right bottom corner
		if ((-error < Y_br - ball.m_y - ball.m_r < error) &&
			(-error < ball.m_x - X_br - ball.m_r < error) &&
			ball.m_y < Y_br &&
			ball.m_x > X_br)
        {
			if(bricks[i].life != 0)
			{
				ball.m_vx = -ball.m_vx;
				ball.m_vy = -ball.m_vy;
				bricks[i].life -= 1;
				scoreCount += 10;  
			    totalBricks -= 1; 
			    sounds.soundBrick(); 
				std::cout << "Corner hit at Brick: " << i << std::endl;
			}
		}
		// Top right corner
		if ((-error < ball.m_y - Y_tr - ball.m_r < error) &&
			(-error < ball.m_x - X_tr - ball.m_r < error) &&
			ball.m_y > Y_tr &&
			ball.m_x > X_tr)
        {
			if(bricks[i].life != 0)
			{
				ball.m_vx = -ball.m_vx;
				ball.m_vy = -ball.m_vy;
				bricks[i].life -= 1;
				scoreCount += 10;  
			    totalBricks -= 1; 
			    sounds.soundBrick(); 
				std::cout << "Corner hit at Brick: " <<  i << std::endl;
			}
		}
		// Top left corner
		if ((-error < ball.m_y - Y_tl - ball.m_r < error) &&
			(-error < X_tl - ball.m_x - ball.m_r < error) && 
			ball.m_y > Y_tl && 
			ball.m_x < X_tl)
        {
			if(bricks[i].life != 0)
			{
				ball.m_vx = -ball.m_vx;
				ball.m_vy = -ball.m_vy;
				bricks[i].life -= 1;
				scoreCount += 10;  
			    totalBricks -= 1; 
			    sounds.soundBrick(); 
				std::cout << "Corner hit at Brick: " << i << std::endl;
			}
		}

		//CORNER COLLISIONS END
   }
}

void batCollisions()
{
	// Ball hits bat on top
	if( (abs(ball.m_y - bat.m_y - 1.0 * bat.m_height) <= 0.01) && 
		((bat.m_x - 0.5 * bat.m_width) <= ball.m_x) &&
		(ball.m_x <= (bat.m_x + 0.5 * bat.m_width))) 
	{
		 ball.m_vy = -ball.m_vy;

		 ball.m_vx = (ball.m_x - bat.m_x) / (bat.m_width / 2) * ball.m_vy;

		 if(totalBricks != 0) //Don't play sound if all bricks are hit and win message is being displayed
		 {
			 sounds.soundBat(); //Play the sound file for if the ball hits the bat
		 }
	}

	powers.powerCollisions(); //Run the function from PowerUps.cpp that handles collisions between the power ups and bat

	/*// Ball hits bat on right
	if ( (abs(ball.m_x - bat.m_x + 0.5 * bat.m_width) <= 0.01) &&
		((bat.m_y - 0.5 * bat.m_height) <= ball.m_y) &&
		(ball.m_y <= (bat.m_y + 0.5 * bat.m_height)))
	{
		ball.m_vx = -ball.m_vx;
	}
	// Ball hits bat on left
	if ( (abs(ball.m_x - bat.m_x - 0.5 * bat.m_width) <= 0.01) &&
		((bat.m_y - 0.5 * bat.m_height) <= ball.m_y) &&
		(ball.m_y <= (bat.m_y + 0.5 * bat.m_height)))
	{
		ball.m_vx = -ball.m_vx;
	}*/
}

void set_level()
{
	switch (totalBricks)
	{
		case 139: //When number of bricks left = 139 (all level one bricks hit)

			/*The below if statement advances the level in a seemless fashion, 
			 *so the game continues until the levels are complete or all lives lost*/
			 if(ball.m_y < 0.05)
			 {
				 brickLayout->drawLayout2(); //Draw layout for level 2 when the ball gets to a certain point (< 0.05)
				 
			 }
		 break;

		case 76: //When number of bricks left = 76 (all level one and two bricks hit)
		
			 if(ball.m_y < 0.05)
			 {
				 brickLayout->drawLayout3(); //Draw layout for level 3 when the ball gets to a certain point (< 0.05)
			 }
			 break;
	}
}

void display(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(Start_Screen)//If start screen is true (equals true at the start on window opening)
	{
		//glEnable(GL_TEXTURE_2D); //Enable the texture
	    screens.start_screen(); //Draw the texture
	}

	if(game_over_screen) //If all lives gone game over screen = true
	{
		//glEnable(GL_TEXTURE_2D); //Enable the texture
		screens.game_over_screen(); //Draw the texture
	}

	if(win_screen) //If all bricks are hit, display screen with win message and total score
	{
		screens.game_win_screen();
		glColor3f(0.745, 1.0, 0.0);
		WinScreenMessage();
	}

	if(!Start_Screen && !game_over_screen && !win_screen) //If start, game over or win screens are false: draw game scene
	{
		 glBindTexture(GL_TEXTURE_2D, screens.backgroundID);
		 screens.background();

		 /*POSSIBLE TO BIND DIFFERENT BACKGROUND TEXTURES FOR EACH DIFFERENT LEVEL*/
		 /*if(totalBricks < 226 && totalBricks > 76) //>223
		 {
			  glBindTexture(GL_TEXTURE_2D, screens.background2ID);
			  screens.background();
		 }

		 if(totalBricks < 77) // < 223
		 {
			  glBindTexture(GL_TEXTURE_2D, screens.background3ID);
			  screens.background();
		 }*/

		 ball.Draw();
		 
		 if(powerBatIncrease) //If the power up is true (Power up brick is hit), then draw power up and give colour
		 {
			glColor3f(0.0,0.0,1.0);
			powers.batIncreaseDraw();
		 }

		 if(powerBallIncrease)
		 {
			glColor3f(1.0,0.0,0.0);
			powers.ballPowerDraw();
		 }

		 if(powerLifeIncrease)
		 {
			glColor3f(0.0,1.0,0.0);
			powers.lifePowerDraw();
		 }

		 bat.Draw();

		 text(); //Draw texts to be displayed

		 set_level(); //Run level function, to allow different layouts to be drawn when certain amount of bricks have been hit

		for (int i = 0; i < numofbricks; i++) {

			glBindTexture(GL_TEXTURE_2D, bricks[i].brickID);
			bricks[i].Draw(bricks[i].brickID); //Draw bricks with their main texture

			if(bricks[i].life == 2)
			{
				glBindTexture(GL_TEXTURE_2D, bricks[i].brick2ID);
				bricks[i].Draw(bricks[i].brick2ID); //Draw bricks (requiring two hits) with a top texture
			}
	}

		glColor3f(1.0,1.0,0.0);
		wall.Draw(); //Draw wall with yellow colour
	}	
	glutSwapBuffers();
}

void text()
{
	glColor3f(0.0, 1.0, 1.0);
	char lives[64]; //Set an array of characters with size of 64 (max 64 characters (0-63))
    sprintf_s(lives, "Lives:"); //Pass array and text to be printed to the C++ sprint function, formatted as a string
    printtext(-4.00, -1.93, lives); //Pass x, y and string values to printtext function

	char live_count[256];
	sprintf_s(live_count,"%d", lifeCount); //Use of %d for decimal format on lifeCount integer
	printtext(-3.65, -1.93, live_count);

	char score[64];
    sprintf_s(score, "Score:");
    printtext(3.45, -1.93, score);

	char score_count[256];
    sprintf_s(score_count, "%d", scoreCount);
    printtext(3.85, -1.93, score_count);
}

void printtext(float x, float y, std::string String)
{
	/***Position of text on screen from x and y float variables passed from text() using glRasterPos2f
	  **size_t is the usigned int type, get the size of the string and increment i...
	  **...for the length of the passed string value from text() function
	  **glutBitmapCharacter function, which sets the font and...
	  **...the number of characters within the string using the i variable***/

    glRasterPos2f(x,y);
    for (size_t i=0; i<String.size(); i++) 
    {                                      
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, String[i]);
    }
}

void WinScreenMessage()
{
	char final_score_count[256];
    sprintf_s(final_score_count, "%d", scoreCount);
    PrintWinScreen(0.0, -0.85, final_score_count);
}
void PrintWinScreen(float x, float y, std::string String)
{
	glRasterPos2f(x,y);
    for (size_t i=0; i<String.size(); i++) 
    {                                      
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, String[i]);
    }
}

void reshape(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	double ratio = 1.0* w / h;

	glutReshapeWindow(1200, 600);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0,     // eye's position
		      0.0,0.0,1.0,     // center of interest
			  0.0f,1.0f,0.0f); // up direction
}

void idle()
{
	if(gameRunning) //If gameRunning is true (when enter key is pressed) 
	{
	   moveBall(); //Run the moveBall function
	   PowerUps(); //Run the PowerUps() function
	   brickCollisions();
	   batCollisions();
	}
	glutPostRedisplay();  //Recall display method
}

void loadTexture(const char* filename, GLuint &ID)
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	//std::cout << ID << std::endl;
	
	Image* image = loadBMP(filename);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGB,
		image->width,
		image->height,
		0,
	    GL_RGB,
		GL_UNSIGNED_BYTE,
		image->pixels);

	delete image;
}

void init() {

	ball.m_r = 0.08;
	ball.m_x = 0;
	ball.m_y = -1.83;

	powers.power_vy = 0.0034;

	ball.m_vx = 0.070;
	ball.m_vy = 0.070;

	bat.setPosition(0, -1.98);

	wall.bottom = -2.0;
	wall.left   = -4.10;
	wall.right  = 4.10;
	wall.top    = 2.0;

	loadTexture("Images/bat.bmp", bat.batID);
	loadTexture("Images/ball.bmp", ball.ballID);
	loadTexture("Images/heart.bmp", powers.heartID);

	  for (int i = 0; i < numofbricks; i++) {

		 loadTexture("Images/brick.bmp", bricks[i].brickID);
		 loadTexture("Images/steel.bmp", bricks[i].brick2ID);
	  }

	brickLayout->drawLayout1();

	loadTexture("Images/background.bmp", screens.backgroundID);

	loadTexture("Screens/start-screen.bmp", screens.startID);
	loadTexture("Screens/game-over.bmp", screens.endID);
	loadTexture("Screens/win-screen.bmp", screens.winID);
}