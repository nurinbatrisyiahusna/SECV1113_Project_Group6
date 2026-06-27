// PROJECT SECV1113 SEM2 2025/2026
// Product name: Coca Cola 

// STUDENT 1 : NAME: DHIVYESH KUMAR A/L SIVAKUMAR               MATRIC NO.: A25CS0212
// STUDENT 2 : NAME: NAJWA NAJIBAH BINTI MOHAMAD NOR            MATRIC NO.: A25CS0288
// STUDENT 3 : NAME: NURIN BATRISYIA HUSNA BINTI MOHD HAZRY     MATRIC NO.: A25CS0328
// STUDENT 4 : NAME: TOR SI JIE                                 MATRIC NO.: A25CS0369

#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

bool startAnimation = false;
int canOffsetX = -500;
int shakeOffset = 0;
int shakeCount = 0;
bool strawBounce = false;
int strawOffsetY = -250;	
int stage = 0;
int iceOffsetY = -450;
float iceAngle = 0;
float bubbleScale = 0.0f;
bool showTagline = false;

typedef float Matrix3x3[3][3];

void setIdentity(Matrix3x3 mat) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) mat[i][j] = 1.0f;
            else mat[i][j] = 0.0f;
        }
    }
}

void multiplyMatrix(Matrix3x3 result, Matrix3x3 A, Matrix3x3 B) {
    Matrix3x3 temp = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = 0.0f;
            for (int k = 0; k < 3; k++) {
                temp[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = temp[i][j];
        }
    }
}

// Linear Interpolation
float lerp(float start, float end, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return start + t * (end - start);
}

// Interpolation
float trigonometricInterpolation(float start, float end, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    float smoothFactor = (1.0f - cos(t * 3.14159265f)) * 0.5f;
    return start + smoothFactor * (end - start);
}
//Translation
void translate(Matrix3x3 current, float tx, float ty){
	Matrix3x3 T;
	setIdentity(T);
	T[0][2] = tx;
	T[1][2] = ty;

	multiplyMatrix(current, T, current);
}

//Rotation
void rotate(Matrix3x3 current, float angle) {
	Matrix3x3 R;
	setIdentity(R);

	float radian = angle * 3.14159265f / 180.0f;
	float cosTheta = cos(radian);
	float sinTheta = sin(radian);

	R[0][0] = cosTheta;
	R[0][1] = -sinTheta;
	R[1][0] = sinTheta;
	R[1][1] = cosTheta;

	multiplyMatrix(current, R, current);
}

//Scaling
void scale(Matrix3x3 current, float sx, float sy){
	Matrix3x3 S;
	setIdentity(S);
	S[0][0] = sx;
	S[1][1] = sy;

	multiplyMatrix(current, S, current);
}

//Shearing
void shear(Matrix3x3 current, float shx, float shy){
	Matrix3x3 Sh;
	setIdentity(Sh);
	Sh[0][1] = shx;
	Sh[1][0] = shy;

	multiplyMatrix(current, Sh, current);
}
void shape(int offsetX)
{
    // Top can
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(305 + offsetX, 150, 445 + offsetX, 160);

    // Body can
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    bar(300 + offsetX, 160, 450 + offsetX, 390);

    // Bottom can
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(305 + offsetX, 390, 445 + offsetX, 400);

    // Wave
    setcolor(WHITE);

    int baseX = 410 + offsetX;
    int amp = 8;
    float freq = 0.05;

    for(int y = 170; y < 380; y++)
    {
        for(int w = -1; w <= 1; w++)
        {
            int x1 = baseX + w + (int)(amp * sin((y - 170) * freq));
            int x2 = baseX + w + (int)(amp * sin((y + 1 - 170) * freq));

            line(x1, y, x2, y + 1);
        }
    }
}

void brandName(int offsetX)
{
    // Red patch behind the text
    setfillstyle(SOLID_FILL, RED);
    bar(350 + offsetX, 190, 395 + offsetX, 355);

    setbkcolor(RED);          // Only while drawing text
    setcolor(WHITE);
    settextstyle(GOTHIC_FONT, VERT_DIR, 2);

    outtextxy(355 + offsetX, 280, (char*)"COCA");
    outtextxy(355 + offsetX, 190, (char*)"COLA");

    setbkcolor(BLACK);        // Restore for the rest of the scene
}

void straw(int offsetX, int offsetY)
{
    setcolor(BROWN);

    // Straw body
    line(390 + offsetX, 70 + offsetY,
         390 + offsetX, 150 + offsetY);

    line(410 + offsetX, 70 + offsetY,
         410 + offsetX, 150 + offsetY);

    line(390 + offsetX, 70 + offsetY,
         410 + offsetX, 70 + offsetY);

    // Straw stripes
    line(410 + offsetX, 70 + offsetY,
         390 + offsetX, 80 + offsetY);

    line(410 + offsetX, 90 + offsetY,
         390 + offsetX, 100 + offsetY);

    line(410 + offsetX, 110 + offsetY,
         390 + offsetX, 120 + offsetY);

    line(410 + offsetX, 130 + offsetY,
         390 + offsetX, 140 + offsetY);
}

void bubbles(int offsetX, float scale)
{
    setcolor(LIGHTBLUE);

    for(int i = 0; i < 10; i++)
    {
        int x = 300 + offsetX + rand() % 150;
        int y = 30 + rand() % 120;

        int r = (int)((5 + rand() % 10) * scale);

        if(r > 0)
            circle(x, y, r);
    }
}

const float PI = 3.14159265f;

void rotatePoint(int cx, int cy, int &x, int &y, float angle)
{
    float rad = angle * PI / 180.0f;

    float dx = x - cx;
    float dy = y - cy;

    int newX = cx + (int)(dx * cos(rad) - dy * sin(rad));
    int newY = cy + (int)(dx * sin(rad) + dy * cos(rad));

    x = newX;
    y = newY;
}
void drawIceCube(int cx, int cy, int size, float angle)
{
    int x1 = cx - size;
    int y1 = cy - size;

    int x2 = cx + size;
    int y2 = cy - size;

    int x3 = cx + size;
    int y3 = cy + size;

    int x4 = cx - size;
    int y4 = cy + size;

    rotatePoint(cx, cy, x1, y1, angle);
    rotatePoint(cx, cy, x2, y2, angle);
    rotatePoint(cx, cy, x3, y3, angle);
    rotatePoint(cx, cy, x4, y4, angle);

    int poly[] =
    {
        x1,y1,
        x2,y2,
        x3,y3,
        x4,y4,
        x1,y1
    };

    setcolor(LIGHTGRAY);
    setfillstyle(SOLID_FILL,LIGHTGRAY);

    fillpoly(5, poly);
}
void ice(int offsetX, int offsetY, float angle)
{
    drawIceCube(245 + offsetX,370 + offsetY,15,angle);

    drawIceCube(227 + offsetX,407 + offsetY,13,-angle);

    drawIceCube(277 + offsetX,407 + offsetY,13,angle);

    drawIceCube(517 + offsetX,370 + offsetY,13,-angle);

    drawIceCube(527 + offsetX,407 + offsetY,13,angle);

    drawIceCube(477 + offsetX,407 + offsetY,13,-angle);

    drawIceCube(342 + offsetX,412 + offsetY,9,angle);

    drawIceCube(372 + offsetX,412 + offsetY,9,-angle);
}

void tagline()
{
    setcolor(LIGHTRED);
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);

    char text[] = "Real Magic - Taste the Feeling!";

    int textWidth = textwidth(text);

    // Center under the can
    int x = 375 - textWidth / 2;
    int y = 440;

    outtextxy(x, y, text);
}
void drawScene(int offsetX)
{
    shape(canOffsetX);
	brandName(canOffsetX);
	straw(canOffsetX, strawOffsetY);
	bubbles(canOffsetX, bubbleScale);
	ice(canOffsetX, iceOffsetY, iceAngle);

	if(showTagline)
    tagline();
}
void startScreen()
{
    cleardevice();

    setcolor(WHITE);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(230, 320, (char*)"Press S to Start");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(285, 360, (char*)"Press ESC to Exit");
}
int main()
{
    initwindow(800,700);
    srand(time(0));

    startScreen();
	
	while(true)
{
    if(kbhit())
    {
        char key = getch();

        if(key == 's' || key == 'S')
            break;

        if(key == 27)   // ESC
        {
            closegraph();
            return 0;
        }
    }

    delay(20);
}
    while(true)
{
    cleardevice();

    // Animation
    if(stage == 0)
    {
        canOffsetX += 8;

        if(canOffsetX >= 0)
        {
            canOffsetX = 0;
            stage = 1;
        }
    }else if(stage == 1)
{
    if(!strawBounce)
    {
        // Falling
        strawOffsetY += 8;

        if(strawOffsetY >= 0)
        {
            strawOffsetY = 10;      // Go slightly below
            strawBounce = true;
        }
    }
    else
    {
        // Bounce back up
        strawOffsetY -= 2;

        if(strawOffsetY <= 0)
        {
            strawOffsetY = 0;
            stage = 2;              // Continue to bubbles
        }
    }

}else if(stage == 2)
{
    // Shake the can for a short time
    if(shakeCount < 12)
    {
        if(shakeCount % 2 == 0)
            shakeOffset = -4;
        else
            shakeOffset = 4;

        shakeCount++;
    }
    else
    {
        shakeOffset = 0;

        // Start bubble animation
        bubbleScale += 0.08f;

        if(bubbleScale >= 1.2f)
        {
            bubbleScale = 1.2f;
            stage = 3;
        }
    }
}else if(stage == 3)
{
    iceOffsetY += 6;
    iceAngle += 8;

    if(iceOffsetY >= 0)
    {
        iceOffsetY = 0;
        showTagline = true;
        stage = 4;
    }
}

    // Draw objects
    shape(canOffsetX + shakeOffset);
	brandName(canOffsetX + shakeOffset);
	straw(canOffsetX + shakeOffset, strawOffsetY);
	bubbles(canOffsetX + shakeOffset, bubbleScale);
	ice(canOffsetX + shakeOffset, iceOffsetY, iceAngle);

	if(showTagline)
    tagline();

    delay(30);
}

    getch();
    closegraph();
    return 0;
}
