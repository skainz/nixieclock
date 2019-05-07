

#include <stdlib.h>
#include <X11/Xlib.h>
#include "vroot.h"

#include "images/WikipediaNixieDigit0.xpm"

int main(int argc, char **argv)
{
  Display *dpy;
  /* other variables: see below */
  Window root;
  GC g;
  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));

  root = DefaultRootWindow (dpy);
   g = XCreateGC (dpy, root, 0, NULL);

//   printf("root w: %d\n",root);
 XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );

     while (1)
    {
      /* draw a square */
      XFillRectangle (dpy, root, g, random()%500, random()%500, 50, 40);


      /* once in a while, clear all */
      if( random()%500<1 )
        XClearWindow(dpy, root);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }
     
printf ("si: %d\n",sizeof(WikipediaNixieDigit0));
}

