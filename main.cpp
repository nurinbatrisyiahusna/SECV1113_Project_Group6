#include <graphics.h>
#include <conio.h>
#include <winbgim.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

main(){
	// Create graphic window
	initwindow(800, 700);

	// set background
    setbkcolor(BLACK);
    cleardevice();


//? -------------------------------------------------------
//?     PRODUCT OUTLINE - COCA COLA CAN DRINK
//? -------------------------------------------------------

    // Draw can shape
    // line (x1, y1, x2, y2)
    setcolor(RED);
    line(300, 150, 430, 150);		    // top surface (_)
    line(294, 170, 435, 170);
    line(300, 150, 270, 220);		    // left curve (/)
    line(430, 150, 460, 220);		    // right curve (\)
    line(270, 220, 270, 360);		    // left body (|)
    line(460, 220, 460, 360);		    // right body (|)
    line(270, 360, 300, 400);   		// left curve (\)
    line(460, 360, 430, 400);   		// right curve (/)
    line(300, 400, 430, 400);   		// right slant (_)

    // Straw
    setcolor(BROWN);
    line(390, 70, 390, 150);
    line(410, 70, 410, 150);
    line(390, 70, 410, 70);

    // Straw pattern
    line(410, 70, 390, 80);
    line(410, 90, 390, 100);
    line(410, 110, 390, 120);
    line(410, 130, 390, 140);


    // Display brand name
    setcolor(WHITE);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 4);
    outtextxy(300, 230, "COCA");
    outtextxy(303, 280, "COLA");


//? -------------------------------------------------------
//?     DECORATIVE ELEMENT
//?  1. fizzing bubbles
//?  2. Ice
//?  3. Tagline
//? -------------------------------------------------------
        
    // Fizzing on top of the lid
    srand(time(0));
    setcolor(LIGHTBLUE);

    for(int i=0; i<10; i++){
        int x = 300 + rand() % 150;
        int y = 3 + rand() % 120;
        int r = 5 + rand() % 10;
        circle(x, y, r);
    }

   
    //Ice at the bottom can area
    setcolor(LIGHTGRAY);
    rectangle(230, 350, 260, 380);
    rectangle(210, 390, 240, 420);
    rectangle(260, 390, 290, 420);
    rectangle(500, 350, 530, 380);
    rectangle(510, 390, 540, 420);
    rectangle(460, 390, 490, 420);
    rectangle(330, 400, 350, 420);
    rectangle(360, 400, 380, 420);

    
    // Tagline
    setcolor(LIGHTRED);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(150, 470, "Real Magic - Taste the Feeling!");

    // Wave inside the can
    setcolor(BROWN);

    for(int x = 290; x < 450; x++) {
        int y1 = 345 + 8 * sin((x - 290) * 0.08);
        int y2 = 345 + 8 * sin((x + 1 - 290) * 0.08);

        line(x, y1, x + 1, y2);
    }

    getch();
    closegraph();
}
