#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/xpm.h>
#include "vroot.h"


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
main ()
{
  Display *dpy;
  Window root;
  GC g;

    XImage *img;

  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  /* set foreground color */
  XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );


 if (XpmCreateImageFromData  (dpy, digits[2], &img, NULL, NULL)) {
//      printf ("Error reading image\n");
      exit (1);
}

  /* draw something */
  while (1)
    {
      /* draw a square */
      XFillRectangle (dpy, root, g, random()%500, random()%500, 50, 40);

   XPutImage(dpy,root,g,img,0,0,random()%500,random()%500,200,200);

      /* once in a while, clear all */
      if( random()%500<1 )
        XClearWindow(dpy, root);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
