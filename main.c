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

XtAppContext app_context;

void quit_proc (Widget w, XtPointer client_data, XtPointer call_data)
{
  XtDestroyApplicationContext (app_context);
  exit(0);
}

int setmode()
{
	FILE *fd; int bigsize = 0;
	char buffer[100];
	fd = popen("ps -e | grep -os balls | wc -l | tr -d '\\n'", "r");
	if (fd == NULL) exit(1);
	fgets(buffer, 100, fd);
	pclose(fd);
	int num = atoi(buffer);
	if(num > 15) bigsize = 10;
//	if(num > 20 && !(num%4)) bigsize = 20;
	if(num == 25) bigsize = 20;
	if(num > 35) exit(1); // avoid fork bomb
	if(num > 25) return(bigsize+0); 
	else if(num > 20) return(bigsize+rand()%3);
	else if(num > 15) return(bigsize+1);
	else return(bigsize+0);
}

int main (int argc, char **argv)
{

	unsigned int buffer; int rando = 0;
	int fd = open("/dev/urandom", O_RDONLY);
	read(fd, &buffer, sizeof(unsigned int));
	close(fd);
	srand(buffer);
	int mode = setmode();
	int size = 16+(rand()%48);

	Display *dpy = XOpenDisplay(NULL);
	assert(dpy);
	Window w;
	XWindowAttributes ratt;
  	XSetWindowAttributes attributes;
  	attributes.override_redirect = true;
	attributes.border_pixmap = CopyFromParent;
	attributes.background_pixmap = CopyFromParent;
//	attributes.background_pixel = 0;
//	attributes.border_pixel = 0;
	Window root;
	if(argc > 1) root = RootWindow(dpy, (rand()%ScreenCount(dpy)));
	else root = DefaultRootWindow(dpy);
	XGetWindowAttributes(dpy, root, &ratt);
	int winx = ratt.width; int winy = ratt.height;
	long int counter = 0;
	int randoo;
	int yrun = winy; 	  
	int xrun = (winx/6)+1+(rand()%250)+(rand()%50)+(rand()%50); 
	int rety = 0; 	 	  int retx = -(rand())%2;
	int randy = 4+(rand()%5); int randx = 2+(rand()%3);

	rando = rand()%3;
	randoo = (rand()%2);
	if(randoo) counter = 999999999;

	if((mode/10) == 2) counter = 0;
	else if((mode/10) == 1) size = 32+(rand()%128);

	if(mode%10 == 1) 
		{ yrun = 40+(rand()%(winy-size)); xrun = -size-10; }
	if(mode%10 == 2) 
		{ xrun = 40+(rand()%(winx-size)); yrun = -size-10; }
		
//  	Window root = RootWindow(dpy, 0xe0000a);
	

	XPoint shape1[3]; 
	shape1[0].x = size/2; shape1[0].y = 0;
	shape1[1].x = 0; shape1[1].y = size;
	shape1[2].x = size; shape1[2].y = size;
	XPoint shape2[3]; 
	shape2[0].x = size/2; shape2[0].y = size;
	shape2[1].x = 0; shape2[1].y = 0;
	shape2[2].x = size; shape2[2].y = 0;
	XPoint shape3[3]; 
	shape3[0].x = 0; shape3[0].y = 0;
	shape3[1].x = 0; shape3[1].y = size;
	shape3[2].x = size; shape3[2].y = size/2;
	XPoint shape4[3]; 
	shape4[0].x = size; shape4[0].y = size;
	shape4[1].x = 0; shape4[1].y = size/2;
	shape4[2].x = size; shape4[2].y = 0;
	XPoint shape5[4]; 
	shape5[0].x = 0; shape5[0].y = 0;
	shape5[1].x = size; shape5[1].y = 0;
	shape5[2].x = size; shape5[2].y = size;
	shape5[3].x = 0; shape5[3].y = size;
	XPoint shape6[4]; 
	shape6[0].x = 0; shape6[0].y = 0;
	shape6[1].x = winx; shape6[1].y = 0;
	shape6[2].x = winx; shape6[2].y = winy;
	shape6[3].x = 0; shape6[3].y = winy;

	while(1)
	{
	if(randoo) counter--;
	else counter++;
	if((mode/10) == 2) 
	{
		w = XCreateWindow(dpy, root, 0, 0, winx, winy, 0, 
		CopyFromParent, CopyFromParent, CopyFromParent, 
		CWOverrideRedirect|CWBorderPixmap|CWBackPixmap, &attributes);
		if(counter > 22 || counter < -22) return(0);
	}
	else
	{
		w = XCreateWindow(dpy, root, xrun, yrun, size, size, 0, 
		CopyFromParent, CopyFromParent, CopyFromParent, 
		CWOverrideRedirect|CWBorderPixmap|CWBackPixmap, &attributes);
	}

	GC gc = XCreateGC(dpy, w, 0, NULL);
	XSetForeground(dpy, gc, 
		((rand())%9345834)+((rand())%3485783)*(rand())%3485783);
//	XFlush(dpy);
//	XDrawLine(dpy, w, gc, 0, 0, size, size);
//	XDrawLine(dpy, w, gc, size, 0, 0, size);
	XMapWindow(dpy, w);
	if((mode/10) == 2) 
		XFillPolygon(dpy,w,gc, shape6, 4, Nonconvex, CoordModeOrigin);
	else
	if(rando == 2) switch(((1+(counter%16))/4))
	{
	case 0: 
		XFillPolygon(dpy,w,gc, shape1, 3, Nonconvex, CoordModeOrigin);
		break;
	case 1: 
		XFillPolygon(dpy,w,gc, shape3, 3, Nonconvex, CoordModeOrigin);
		break;
	case 2: 
		XFillPolygon(dpy,w,gc, shape2, 3, Nonconvex, CoordModeOrigin);
		break;
	case 3: 
		XFillPolygon(dpy,w,gc, shape4, 3, Nonconvex, CoordModeOrigin);
		break;
	}
	else if(rando == 1) 
		XFillPolygon(dpy,w,gc, shape5, 4, Nonconvex, CoordModeOrigin);
//	else if(rando == 1) 
//		XFillArc(dpy, w, gc, 0, 0, size, size, 0, 23040);
	else if(!rando) 
		XFillArc(dpy, w, gc, 0, 0, size, size, 0, 23040);
	
	char text[100]; int u;
	XTextItem xit; 
	if((mode/10) == 2)
	{
		XSetForeground(dpy, gc, ((rand())%34883)*(rand())%1486883);
		sprintf(text, "%s", "++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++AWESOME++");
		xit.chars = text; xit.nchars = 164; xit.delta = 30; 
		xit.font = XLoadFont(dpy, 
			"-*-terminal-*-r-*-*-60-*-*-*-*-240-*-*");
//"-*-*-*-r-*-*-34-*-*-*-*-216-*-*");
		XSetFont (dpy,gc, xit.font);
		for(u = xit.delta*2; u < (1+(winx/72))*xit.delta*8; u+=xit.delta*8)
			XDrawText(dpy, w, gc, -1600+xrun, u, &xit, 1);
		for(u = xit.delta*6; u < (1+(winx/72))*xit.delta*8; u+=xit.delta*8)
			XDrawText(dpy, w, gc, winx-128-xrun, u, &xit, 1);
	}
	XFlush(dpy);
	if((mode/10) == 2) XUnloadFont(dpy, xit.font);
	if((mode/10) == 2) 
		usleep(190000);
	else
		usleep(10000);

	XDestroyWindow(dpy, w);
	if((mode/10) == 2) xrun += 1+((winx+400)/22);
	else if((mode/10) != 2) 
	{

	if(!(mode%10))
	{
	if(xrun <= 0) { retx = 1; }
	if(xrun >= winx-size) { retx = 0; }
	if(retx) xrun+=randx;
	else xrun-=randx;

	if(yrun >= 1 && !rety) yrun-=randy; 
	if (yrun <= 0)  { rety = 1; yrun = 1;}
	if(rety) yrun+=randy;

	if(rety && yrun > winy+size) return(0);
	}
	else if((mode%10) == 1)
		{ xrun += 1.5*randx; if(xrun > winx) return(0); }
	else if((mode%10) == 2)
		{ yrun += 1.5*randy; if(yrun > winy) return(0); }

	}
	}
}

