/* This code is dirty. Yes! Dirty code. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Command.h>
#include <assert.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <SDL/SDL.h>

int done = 0;

int draws(SDL_Surface *screen, int h)
{
SDL_Rect rec;
rec.x = 100; rec.y = 100; rec.h = 100; rec.w = 100; 
SDL_FillRect(screen, &rec, 3534535);
SDL_Flip(screen);
}

int keylistener(SDL_Event *ev)
{
	while(SDL_PollEvent(ev))
	{ switch(ev->type) {
	case SDL_QUIT:
		done = 1;
		break;
	case SDL_KEYDOWN:
		done = 1;
		break;
	} }
}

int main()
{
	SDL_Surface *screen;
	SDL_Event event;
//	SDL_putenv("SDL_VIDEO_X11_VISUALID=0xba");
	SDL_putenv("SDL_WINDOWID=0xba");
	int h=0; 

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
		{ printf("SDL_Init failed\n"); return(1); }
	if (!(screen = SDL_SetVideoMode(1024, 768, 24, 
		SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_HWPALETTE)))
		{ SDL_Quit(); printf("SDL_SetVideoMode failed\n"); return(1); }

	while(!done)
	{
		draws(screen, h++);
		keylistener(&event);
		SDL_Delay(10);
	}


}
