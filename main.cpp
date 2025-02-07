#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#define PI 3.14159265358979323846
#include <mmsystem.h>
#include <cstdlib>

//#define SHIP_SOUND "E:\\Codes\\CG\\ship-horn-distant-38390.wav"
//#define ROCKET_SOUND "E:\\Codes\\CG\\mixkit-sci-fi-rocket-engine-1723 (1).wav"



float rocketHight = -0.1f;
bool launch = false; // Launch command state
float scaleValue = 1.0f; // Scaling factor for the rocket
float translationValue = 0.0f; // Translation for upward motion
bool ignition = false; // Ignition state
bool  estop = false ; //engine state

float shipX = -1.0f;
float rocketY = 0.0f;
float waveOffset = 0.0f;

float rocketX = -1.2f;
float satelliteY = -1.2f;

bool DW = true  ; //w part display
bool DT = false ;
bool DS = false;


void Rectangle(float x1, float x2, float y1, float y2, int r, int g, int b) {
    glColor3ub(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x1, y2);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    glVertex2f(x1, y1);
    glEnd();
}

void Triangle(float x1, float x2, float x3, float y1, float y2, float y3, int r, int g, int b) {
    glColor3ub(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}
void drawCircle(float x, float y, float radius) {
    int triangleAmount = 100;
    float twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cosf(i * twicePi / triangleAmount)),
            y + (radius * sinf(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawCircle(float x, float y, float radius, int segments) {
    float angleStep = 2.0f * PI / segments;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        glVertex2f(x + radius * cosf(angle), y + radius * sinf(angle));
    }
    glEnd();
}

void drawWaves() {
    glColor3f(0.0f, 0.7f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (float x = -1.0f; x <= 1.0f; x += 0.02f) {
        float y = -0.45f + 0.02f * sinf(10 * x + waveOffset);
        glVertex2f(x, y);
    }
    glEnd();
}


void drawScene() {

    glColor3f(0.5f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();


    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.8f, 0.8f, 0.1f);


    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.6f, 0.7f, 0.1f);
    drawCircle(-0.5f, 0.7f, 0.15f);
    drawCircle(-0.4f, 0.7f, 0.1f);

    drawCircle(0.2f, 0.6f, 0.1f);
    drawCircle(0.3f, 0.6f, 0.15f);
    drawCircle(0.4f, 0.6f, 0.1f);


    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();


    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();


    drawWaves();


    glPushMatrix();
    glTranslatef(0.0f, rocketY, 0.0f);


    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(0.05f, 0.1f);
    glVertex2f(-0.05f, 0.1f);
    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05f, 0.1f);
    glVertex2f(0.05f, 0.1f);
    glVertex2f(0.0f, 0.2f);
    glEnd();


    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.03f, -0.05f);
    glVertex2f(0.03f, -0.05f);
    glVertex2f(0.0f, -0.15f);
    glEnd();

    glPopMatrix();


    float buildingColors[4][3] = {
        {0.8f, 0.2f, 0.2f},
        {0.2f, 0.8f, 0.2f},
        {0.2f, 0.2f, 0.8f},
        {0.8f, 0.8f, 0.2f}
    };
    float xStart = -0.8f;
    for (int i = 0; i < 4; i++) {
        glColor3f(buildingColors[i][0], buildingColors[i][1], buildingColors[i][2]);
        glBegin(GL_QUADS);
        glVertex2f(xStart, 0.0f);
        glVertex2f(xStart + 0.2f, 0.0f);
        glVertex2f(xStart + 0.2f, 0.5f);
        glVertex2f(xStart, 0.5f);
        glEnd();


        glColor3f(1.0f, 1.0f, 1.0f);
        float windowY = 0.1f;
        for (int j = 0; j < 2; j++) {
            glBegin(GL_QUADS);
            glVertex2f(xStart + 0.05f, windowY);
            glVertex2f(xStart + 0.1f, windowY);
            glVertex2f(xStart + 0.1f, windowY + 0.1f);
            glVertex2f(xStart + 0.05f, windowY + 0.1f);
            glEnd();
            windowY += 0.2f;
        }

        if (i == 2) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(xStart + 0.04f, 0.45f);
        const char* label = "Building3";
        for (const char* c = label; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
        } }

        xStart += 0.3f;
    }






    glPushMatrix();
    glTranslatef(shipX, -0.3f, 0.0f);


    glColor3f(0.5f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f, -0.1f);
    glVertex2f(0.4f, -0.1f);
    glVertex2f(0.3f, 0.05f);
    glVertex2f(-0.3f, 0.05f);
    glEnd();


    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, 0.05f);
    glVertex2f(0.3f, 0.05f);
    glVertex2f(0.3f, 0.12f);
    glVertex2f(-0.3f, 0.12f);
    glEnd();


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, 0.12f);
    glVertex2f(0.25f, 0.12f);
    glVertex2f(0.25f, 0.18f);
    glVertex2f(-0.25f, 0.18f);
    glEnd();


    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, 0.18f);
    glVertex2f(0.2f, 0.18f);
    glVertex2f(0.2f, 0.23f);
    glVertex2f(-0.2f, 0.23f);
    glEnd();


    glColor3f(1.0f, 0.5f, 0.0f);
    float chimneyX = -0.15f;
    for (int i = 0; i < 4; i++) {
    glBegin(GL_QUADS);
    glVertex2f(chimneyX, 0.23f);
    glVertex2f(chimneyX + 0.05f, 0.23f);
    glVertex2f(chimneyX + 0.05f, 0.35f);
    glVertex2f(chimneyX, 0.35f);
    glEnd();
    chimneyX += 0.1f;
}

  glPopMatrix();




    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.2f, -0.4f, 0.05f);
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, -0.45f);
    glVertex2f(-0.18f, -0.45f);
    glVertex2f(-0.18f, -0.55f);
    glVertex2f(-0.22f, -0.55f);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(-0.22f, -0.45f);
    glVertex2f(-0.25f, -0.5f);
    glVertex2f(-0.18f, -0.45f);
    glVertex2f(-0.15f, -0.5f);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(-0.22f, -0.55f);
    glVertex2f(-0.23f, -0.6f);
    glVertex2f(-0.18f, -0.55f);
    glVertex2f(-0.17f, -0.6f);
    glEnd();


    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.55f, -0.5f);
    glVertex2f(0.55f, -0.3f);
    glVertex2f(0.5f, -0.3f);
    glEnd();

    glColor3f(0.0f, 0.8f, 0.0f);
    drawCircle(0.525f, -0.25f, 0.1f);
    drawCircle(0.475f, -0.2f, 0.1f);
    drawCircle(0.575f, -0.2f, 0.1f);


}

void drawSun() {
    float sunX = -1.0f, sunY = 1.0f; // Top-left corner position
    float sunRadius = 0.7f; // Big Sun covering 1/4 of the screen
    int segments = 100;

    // Outer Layer (Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(sunX, sunY, sunRadius, segments);

    // Middle Layer (Orange)
    glColor3f(1.0f, 0.5f, 0.0f);
    drawCircle(sunX, sunY, sunRadius * 0.7f, segments);

    // Inner Layer (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(sunX, sunY, sunRadius * 0.4f, segments);
}

// Function to draw the rocket
void drawRocket() {
    glPushMatrix();
    glTranslatef(rocketX, 0.0f, 0.0f);

    // Rocket Body (Gray)
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, -0.05f);
    glVertex2f(0.2f, -0.05f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(-0.2f, 0.1f);
    glEnd();

    // Rocket Nose (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2f, -0.05f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.3f, 0.03f);
    glEnd();

    // Fire at the bottom (Orange)
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2f, -0.04f);
    glVertex2f(-0.2f, 0.09f);
    glVertex2f(-0.3f, 0.03f);
    glEnd();

    glPopMatrix();
}

// Function to draw the galaxy scene
void drawGalaxy() {
    // Background (Black Space)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Stars (Small & Yellow)
    glColor3f(1.0f, 1.0f, 0.0f);
    srand(10);
    for (int i = 0; i < 100; i++) {
        float x = ((rand() % 200) / 100.0f) - 1.0f;
        float y = ((rand() % 200) / 100.0f) - 1.0f;
        float size = (rand() % 3 + 1) / 200.0f;
        drawCircle(x, y, size, 10);
    }

    // Draw the Sun in the top-left corner (after stars, so it overlaps them)
    drawSun();

    // Planets
    glColor3f(0.5f, 0.0f, 1.0f);
    drawCircle(-0.3f, 0.5f, 0.1f, 50);

    glColor3f(0.0f, 1.0f, 0.0f);
    drawCircle(0.4f, -0.3f, 0.12f, 50);

    glColor3f(1.0f, 0.5f, 0.0f);
    drawCircle(-0.2f, -0.6f, 0.08f, 50);

    glColor3f(0.0f, 0.7f, 1.0f);
    drawCircle(0.6f, 0.4f, 0.09f, 50);

    glColor3f(1.0f, 0.0f, 0.5f);
    drawCircle(-0.5f, -0.2f, 0.1f, 50);

    // Rocket
    drawRocket();

    // Satellite moving from bottom to top
    glPushMatrix();
    glTranslatef(0.0f, satelliteY, 0.0f);

    // Satellite Body (Gray)
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(0.05f, 0.05f);
    glVertex2f(-0.05f, 0.05f);
    glEnd();

    // Solar Panels (Blue)
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, -0.02f);
    glVertex2f(-0.05f, -0.02f);
    glVertex2f(-0.05f, 0.02f);
    glVertex2f(-0.15f, 0.02f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.05f, -0.02f);
    glVertex2f(0.15f, -0.02f);
    glVertex2f(0.15f, 0.02f);
    glVertex2f(0.05f, 0.02f);
    glEnd();

    glPopMatrix();
}

void DrawTree(float x, float y) {
    // Tree trunk
    Rectangle(x - 0.02f, x + 0.02f, y, y + 0.2f, 139, 69, 19); // Brown trunk
    // Tree foliage
    Triangle(x - 0.1f, x, x + 0.1f, y + 0.2f, y + 0.4f, y + 0.2f, 212, 91 , 18); // Green foliage
}
void DrawRocketStation(float x, float y) {
    // Large building structure
    Rectangle(x- 0.1f, x + 0.5f, y, y + 0.6f, 100, 100, 100);
    Rectangle(x + 0.5f, x + 0.9f, y, y + 0.6f, 100, 100, 100);
    // Two large doors
    Rectangle(x + 0.01f, x + 0.15f, y, y + 0.3f, 50, 50, 50);
    Rectangle(x + 0.21f, x + 0.35f, y, y + 0.3f, 50, 50, 50);

}
void DrawSecondRS(float x,float y ) {

    Rectangle(x, x + 0.2f, y, y + 0.25f, 165, 165, 165);
    Rectangle(x + 0.05f, x + 0.15f, y + 0.25f, y + 0.7f, 100, 100, 100);
    Rectangle(x + 0.2f, x + 0.3f, y + 0.3f , y + 0.75f, 255,255,255);

    Triangle(x + 0.2f, x + 0.3f,x + 0.25f , y+ 0.75f,y + 0.75f , y + 0.85f ,255,0,0);
    glColor3ub(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(x+ 0.15f,y + 0.4f);
    glVertex2f(x+ 0.2f,y + 0.4f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x+ 0.15f,y + 0.6f);
    glVertex2f(x+ 0.2f,y + 0.6f);
    glEnd();


}


static void RocketSecondary(float x1, float y1) {
    Rectangle(x1, x1 - 0.1f, y1, y1 + 0.38f, 200, 200, 200);
    Triangle(x1, x1 - 0.05f, x1 - 0.1f, y1 + 0.38f, y1 + 0.48f, y1 + 0.38f, 200, 200, 200);
    Rectangle(x1, x1 - 0.1f, y1, y1 + 0.1f, 20, 20, 20);
}

static void RocketBase(float x1, float y1) {
    Rectangle(x1, x1 - 0.16f, y1, y1 + 0.4f, 210, 210, 50);
    Triangle(x1 - 0.16f, x1 - 0.08f, x1, y1 + 0.4f, y1 + 0.5f, y1 + 0.4f, 210, 210, 50);
}

static void RocketMain(float x1, float y1) {
    Triangle(x1 - 0.08f, x1 - 0.12f, x1 - 0.16f, y1 + 0.39f, y1 + 0.46f, y1 + 0.39f, 230, 230, 230);
    Triangle(x1, x1 - 0.08f, x1 - 0.08f, y1 + 0.04f, y1 + 0.14f, y1 + 0.04f, 230, 230, 230);
    Triangle(x1 - 0.16f, x1 - 0.16f, x1 - 0.24f, y1 + 0.04f, y1 + 0.14f, y1 + 0.04f, 230, 230, 230);
    Rectangle(x1, x1 - 0.08f, y1, y1 + 0.04f, 220, 220, 220);
    Rectangle(x1 - 0.16f, x1 - 0.24f, y1, y1 + 0.04f, 220, 220, 220);
    Rectangle(x1 - 0.05f, x1 - 0.11f, y1 - 0.04f, y1 + 0.04f, 230, 230, 230);
    Rectangle(x1 - 0.13f, x1 - 0.19f, y1 - 0.04f, y1 + 0.04f, 230, 230, 230);
    Rectangle(x1 - 0.08f, x1 - 0.16f, y1 + 0.02f, y1 + 0.39f, 230, 230, 230);
}

static void Rocket(float x1, float y1) {

    RocketBase(x1 - 0.05f, y1 + 0.1f);
    RocketSecondary(x1 -0.157f, y1);
    RocketSecondary(x1, y1);
    RocketMain(x1 - 0.01f, y1 + 0.08f);
}
void DrawFire(float x, float y) {
    Triangle(x - 0.05f, x, x + 0.05f, y, y - 0.13f, y, 255, 140, 0);
    Triangle(x - 0.03f, x, x + 0.03f, y - 0.05f, y - 0.18f, y - 0.05f, 255, 69, 0);
}


void initOpenGL() {
    glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void initOpenGLS() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}



void displayT() {
    DW= false ;
    DT= true ;
    DS= false ;
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    glutSwapBuffers();
}

void displayS() {
    DW= false ;
    DT= false ;
    DS= true ;
    glClear(GL_COLOR_BUFFER_BIT);
    drawGalaxy();
    glutSwapBuffers();
}

void update(int value) {

if(DW){
    if (ignition && !estop) {
        if (translationValue <=15) {
            translationValue += 0.05f;
            if (scaleValue > 0.1f) {
               scaleValue -= 0.01f;
           }
        } else {
            translationValue = 15;
            ignition = false;
        }
    }
    if (estop) {
        if (translationValue  > 0.1f) {
            translationValue -= 0.05f;
           if (scaleValue >= 0.1f) {
               scaleValue += 0.01f;
            }
        } else {
            translationValue = 0.1f;
            ignition = false;
            estop = false;
        }
    }

}
if(DS){
    rocketX += 0.013f;
    if (rocketX > 1.2f) rocketX = -1.2f;

    satelliteY += 0.005f;
    if (satelliteY > 1.2f) satelliteY = -1.2f;
}

if(DT){
    shipX += 0.0018f;
    if (shipX > 1.0f) {
        shipX = -1.0f;
    }


    waveOffset += 0.01f;


    rocketY += 0.015f;
    if (rocketY > 2.0f) {
        rocketY = 0.0f;
    }
}

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 'e') {
        ignition = true;
    }
    if( key== 'b'){
        estop = true  ;
    }
    glutPostRedisplay();

    /*if (key == 'x' || key == 'X') {
        PlaySound(SHIP_SOUND, NULL, SND_FILENAME | SND_ASYNC);
    } else if (key == 'y' || key == 'Y') {
        PlaySound(NULL, NULL, 0);
        PlaySound(ROCKET_SOUND, NULL, SND_FILENAME | SND_ASYNC);
    }*/
    if( key== 'w'){
    DW= true ;
    DT= false ;
    DS= false ;
    }

    if (key == 't') {
    DW= false ;
    DT= true ;
    DS= false ;
    }
    if( key== 's'){
    DW= false ;
    DT= false ;
    DS= true ;
    }


}

void initW() {
    glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
}

static void displayW(void) {
    DW= true ;
    DT= false ;
    DS= false ;
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(scaleValue, scaleValue, 1);
    glTranslatef(0, translationValue + rocketHight, 0);
    Rocket(0.0f, -0.5f);
    if (ignition && !estop) {
        DrawFire(-0.05f, -0.5f );
        DrawFire(-0.2f, -0.5f );
    }
    glPopMatrix();

    // Draw ground
    Rectangle(-1.0f, 1.0f, -1.0f, -0.6f, 34, 139, 34); // Green ground
    //Rectangle(0.75f,0.8f,0.1f,0.0f,192,192,192);
    Rectangle(-1.0f, 1.0f, -1.0f, -0.6f, 34, 139, 34);//rocket station
    DrawRocketStation(0.5f, -0.6f);


    DrawSecondRS(-0.95f,-0.6f);

    // Draw trees
    DrawTree(-0.8f, -0.9f);//Left tree
    DrawTree(-0.5f, -0.94f);
    DrawTree(0.5f, -0.87f);//right tree
    DrawTree(0.8f, -0.98f);
    DrawTree(0.0f, -0.97f);//middle tree
    DrawTree(0.4f, -0.98f);




    glFlush();
    glutSwapBuffers();
}
void display(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if(DW){
        glPushMatrix();
        initW();
        displayW();
        glPopMatrix();
    }
    if(DT){
        glPushMatrix();
        initOpenGL();
        displayT();
        glPopMatrix();
    }
    if(DS){
        glPushMatrix();
        initOpenGLS();
        displayS();
        glPopMatrix();
    }


}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rocket Launch Animation");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return EXIT_SUCCESS;
}
