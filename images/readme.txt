Copyright Information

'Nixie2.gif' is taken from the Wikipedia Article about Nixie Tubes (https://en.wikipedia.org/wiki/Nixie_tube).
Images made by Hellbus, https://commons.wikimedia.org/wiki/User:Hellbus

The single image file where created using ImageMagick, with the following command line:

convert -coalesce Nixie2.gif WikipediaNixieDigit%01d.png

XPM files

ls -1 *.png|while read l; do convert ${l} $(basename $l .png).xpm; done



