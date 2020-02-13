#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/xpm.h>
#include "vroot.h"
#include <stdio.h>
#include <time.h>

#include "images/WikipediaNixieDigit0.xpm"
#include "images/WikipediaNixieDigit1.xpm"
#include "images/WikipediaNixieDigit2.xpm"
#include "images/WikipediaNixieDigit3.xpm"
#include "images/WikipediaNixieDigit4.xpm"
#include "images/WikipediaNixieDigit5.xpm"
#include "images/WikipediaNixieDigit6.xpm"
#include "images/WikipediaNixieDigit7.xpm"
#include "images/WikipediaNixieDigit8.xpm"
#include "images/WikipediaNixieDigit9.xpm"

#define DIGIT_WIDTH 200
#define DIGIT_HEIGHT 200

static char **digits[]={WikipediaNixieDigit0,
			WikipediaNixieDigit1,
			WikipediaNixieDigit2,
			WikipediaNixieDigit3,
			WikipediaNixieDigit4,
			WikipediaNixieDigit5,
			WikipediaNixieDigit6,
			WikipediaNixieDigit7,
			WikipediaNixieDigit8,
			WikipediaNixieDigit9
			
};


int main ()
{

  struct timeval tv;
  fd_set in_fds;
  int x11_fd;
  
  tv.tv_sec = 5;
  tv.tv_usec = 0;
  
  // top/left coords of display
  
  Display *dpy;
  Window root;
  GC g;
  
  XImage *img;
  XImage *images[10];
  XWindowAttributes xwAttr;
  XEvent e;  
  int i=0;
  
  
  time_t rawtime;
  struct tm * timeinfo;

  char digs[4];
  
  
  dpy = XOpenDisplay (getenv ("DISPLAY"));
    
  
  x11_fd = ConnectionNumber(dpy);
  
  /* get the root window */
  root = DefaultRootWindow (dpy);
  
  Status ret = XGetWindowAttributes( dpy, root, &xwAttr );

  srand(time(0)); 
  int left=rand() % (xwAttr.width-4*DIGIT_WIDTH);
  int top=rand() %(xwAttr.height-DIGIT_HEIGHT);


  
  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);
  
  
  /* set foreground color */
  XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );
  
  for (i=0;i<10;i++)
    {
      XpmCreateImageFromData  (dpy, digits[i], &images[i], NULL, NULL);
    }
  
  
  XSelectInput(dpy, root, ExposureMask);
  
  while (1)
    {
      FD_ZERO(&in_fds);
      FD_SET(x11_fd, &in_fds);
      
      tv.tv_usec = 0;
      tv.tv_sec = 1;
      
      
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      
      digs[0]=(timeinfo->tm_hour / 10);
      digs[1]=(timeinfo->tm_hour % 10);
      digs[2]=(timeinfo->tm_min / 10);
      digs[3]=(timeinfo->tm_min % 10);
      
      
      int num_ready_fds = select(x11_fd + 1, &in_fds, NULL, NULL, &tv);
      
      if (num_ready_fds > 0)
	{}
	//	printf("Event Received!\n");
	
      else if (num_ready_fds == 0) {
	
	
	for (i=0;i<4;i++)
	  {
	    XPutImage(dpy,root,g,images[digs[i]],0,0,150+i*200,top,200,200);
	  }
	
	
      }
      
      
      
      while(XPending(dpy))
	{
	  XNextEvent(dpy, &e);
	  for (i=0;i<4;i++)
	    {
	      XPutImage(dpy,root,g,images[digs[i]],0,0,150+i*200,top,200,200);
	    }
	  
	}
      
      
    }
  
  XCloseDisplay (dpy);
  return 0;
}
