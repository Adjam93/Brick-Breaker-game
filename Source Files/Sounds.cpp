#include "stdafx.h"
#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include "Sounds.h"

void Sounds::soundBrick()
{
	PlaySound(TEXT("Sounds/button-09.wav"), NULL, SND_FILENAME|SND_ASYNC); //Play sound for when brick is hit
	/*SND_ASYNC ensures the program continues to run after sound starts playing, otherwise the program would freeze
	 *until the sound finished playing*/
}

void Sounds::soundBat()
{
	PlaySound(TEXT("Sounds/bat-knock"), NULL, SND_FILENAME|SND_ASYNC);
}

void Sounds::powerUpSound()

{
	PlaySound(TEXT("Sounds/Power-Up.wav"), NULL, SND_FILENAME|SND_ASYNC);
}

void Sounds::lifeLostSound()
{
	PlaySound(TEXT("Sounds/Life-Lost.wav"), NULL, SND_FILENAME|SND_ASYNC);
}

void Sounds::GameOverSound()
{
	PlaySound(TEXT("Sounds/Game-Over.wav"), NULL, SND_FILENAME|SND_ASYNC);
}
