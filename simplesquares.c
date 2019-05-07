#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/xpm.h>
#include "vroot.h"


#include "images/WikipediaNixieDigit0.xpm"
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


 if (XpmCreateImageFromData  (dpy, WikipediaNixieDigit0, &img, NULL, NULL)) {
//      printf ("Error reading image\n");
      exit (1);
}

  /* draw something */
  while (1)
    {
      /* draw a square */
      XFillRectangle (dpy, root, g, random()%500, random()%500, 50, 40);

   XPutImage(dpy,root,g,img,0,0,0,0,200,200);

      /* once in a while, clear all */
      if( random()%500<1 )
        XClearWindow(dpy, root);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
