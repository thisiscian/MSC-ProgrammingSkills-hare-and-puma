What Cian Did With His Time
===========================

04/10/12 11.50
--------------
- discussed what tasks we would split up
- I am doing the output
- created a very simple "output.h" and "output.cpp" system to write two arrays to files
- considered using "latitude" and "longitude" instead of the lengthy "horizontalPosition" and "verticalPosition" but decided that they were too complicated
- added skeleton functions (i.e. empty) for writing ppms and getting averages
- currently outputing two separate ppm files for pumas and hares, but could mix the two into one
- changed from using double arrays to board arrays, which were created by paddy
- removed calculating averages (was not my job)
- first compilation, had loads of bugs
- compilation bugs may have waited on paddy

04/10/12 14.10
--------------
- converted from using a pgm format to the correct ppm format
- corrected some output issues
- added in considerations for whether tile was land or water

04/10/12 16.50
--------------
- fixed output bug in ppm
- renamed ppm stuff
- started creating fancy PPM output
- made console output nicer, and switched console to using printf
- had some issues with row ordering, but it was all a big mistake, my code was fine
- switched simple ppm over to using fprintf
- changed current fancy style to 'adjustable' style, which has borders and arbitrary tile size
- started on the actual fancy size: need to find out how to draw pumas and hares

06/10/12 - 07/10/12
-------------------
- wrote a basic qt program

08/10/12 11.10
--------------
- switched from using printf to cout

08/10/12 19.00
--------------
- started coding for using wxwidgets (qt is a bit of a hassle)
- gave up on that, wxwidgets is not installed on cp-labs, probably safer this way
- might start ncurses work
- fixed the output stuff working correctly
- might have to change output to account for boundary data (easier for roar)

09/10/12
--------
- Created ncurses (g)ui, very rough, needs work, has a lot of promise
- Created statistics class, which outputs very basic statistics about the field of hares and pumas

10/10/12 11:10
--------------
- Enforced ncurses field image taking up no more than half the visible screen
- Need to be able to scale overly large images

10/10/12 14.00
--------------
- Simplified Ncurses display
- Added Key, statistics and Input windows
- fleshed out Key and Statistics windows
- made a nice class for Ncurses, everything is nicer, and it took bloody ages
- did some quick calculations, hares need to be 3-8 times larger to feed the pumas
- http://cheezdailysquee.files.wordpress.com/2011/09/aeeca634-041e-45ed-976f-6db73452da09.jpg
