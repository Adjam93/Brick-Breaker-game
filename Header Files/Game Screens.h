#ifndef SCREENS_H
#define SCREENS_H

class Screens {
public:
	
	void start_screen();
	void game_over_screen();
	void game_win_screen();
	void background();

	GLuint startID;
	GLuint endID;
	GLuint winID;
	GLuint backgroundID, background2ID, background3ID;
};
#endif