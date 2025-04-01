#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#define ScreenWidth getmaxx()
#define ScreenHeight getmaxy()
#define GroundY ScreenHeight * 0.95

// Global game variables
int x = 100;         // Stickman x-position
int ldisp = 0;       // Leg displacement
int score = 0;       // Player score
int lives = 3;       // Player lives
bool isGameOver = false;

// Lightning variables
int lightningX = 0;  // Random x-position
int lightningY = 0;  // Random y-position
int lightningLength = 150;  // Length of lightning bolt
int lightningFrequency = 50;     // Controls how often lightning appears
int lightningDuration = 10;      // How many frames lightning stays visible
int minLightningLength = 100;    // Minimum lightning length
int maxLightningLength = 250;    // Maximum lightning length
int maxLightningX = 800;         // Maximum x-position
int minLightningX = 0;           // Minimum x-position
int maxLightningY = 300;         // Maximum y-position
int minLightningY = 0;           // Minimum y-position
bool isLightningActive = false;
int currentLightningFrame = 0;
int warningTimer = 0;

// Hit message variables
bool showHitMessage = false;
int hitMessageTimer = 0;

// Function to draw clouds
void drawClouds() {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    
    // Cloud 1 (Left cloud)
    circle(50, 90, 20);
    floodfill(51,91,WHITE);
    circle(108, 80, 20);
    floodfill(109,81,WHITE);
    circle(73, 80, 20);
    floodfill(74,81,WHITE);
    circle(130, 90, 10);
    floodfill(131,91,WHITE);
    circle(108, 90, 20);
    floodfill(109,101,WHITE);
    circle(73, 100, 22);
    floodfill(74,101,WHITE);

    // Cloud 2 (Right cloud)
    circle(350, 90, 20);
    floodfill(351,91,WHITE);
    circle(408, 80, 20);
    floodfill(409,81,WHITE);
    circle(373, 80, 20);
    floodfill(374,81,WHITE);
    circle(430, 90, 10);
    floodfill(431,91,WHITE);
    circle(408, 90, 20);
    floodfill(409,101,WHITE);
    circle(373, 100, 22);
    floodfill(374,101,WHITE);
}

// Function to draw background
void drawBackground() {
    // Field
    int field[]={0, GroundY-170, ScreenWidth, GroundY-170, ScreenWidth, GroundY, 0, GroundY, 0, GroundY-170};
    drawpoly(5, field);
    setfillstyle(SOLID_FILL, GREEN);
    fillpoly(5, field);

    // Road
    int road[]={0, GroundY-50, ScreenWidth, GroundY-50, ScreenWidth, GroundY, 0, GroundY, 0, GroundY-50};
    drawpoly(5, road);
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillpoly(5, road);
    
    //house
    int tri[]={100,150, 50, 200, 150, 200, 100, 150};
    drawpoly(4, tri);
    setfillstyle(INTERLEAVE_FILL, LIGHTGRAY);
    fillpoly(4, tri);

    int trec[]={50, 200, 150, 200, 150, 300, 50, 300, 50, 200};
    drawpoly(5, trec);
    setfillstyle(SOLID_FILL, LIGHTRED);
    fillpoly(5, trec);

    int tw[]={80, 210, 120, 210, 120, 240, 80, 240, 80, 210};
    drawpoly(5, tw);
    setfillstyle(LINE_FILL, DARKGRAY);
    fillpoly(5, tw);

    int td[]={75, 250, 125, 250, 125, 300, 75, 300, 75, 250};
    drawpoly(5, td);
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillpoly(5, td);
    circle(120, 275, 5);

    int rom[]={100, 150, 230, 150, 280, 200, 150, 200, 100, 150};
    drawpoly(5, rom);
    setfillstyle(INTERLEAVE_FILL, LIGHTGRAY);
    fillpoly(5, rom);

    int rrec[]={150, 200, 280, 200, 280, 300, 150, 300, 150, 200};
    drawpoly(5, rrec);
    setfillstyle(SOLID_FILL, LIGHTRED);
    fillpoly(5, rrec);

    int rw1[]={160, 210, 200, 210, 200, 240, 160, 240, 160, 210};
    drawpoly(5, rw1);
    setfillstyle(LINE_FILL, DARKGRAY);
    fillpoly(5, rw1);

    int rw2[]={230, 210, 270, 210, 270, 240, 230, 240, 230, 210};
    drawpoly(5, rw2);
    setfillstyle(LINE_FILL, DARKGRAY);
    fillpoly(5, rw2);

    int rd[]={190, 250, 240, 250, 240,300, 190, 300, 190, 250};
    drawpoly(5, rd);
    setfillstyle(SOLID_FILL, DARKGRAY);
    fillpoly(5, rd);
    circle(235, 275, 5);
}

// Enhanced Lightning Bolt Drawing Function
void drawLightningBolt(int startX, int startY, int length) {
    // More customizable lightning bolt
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    
    // Increased variability in lightning shape
    int bolt[] = {
        startX, startY,                      // Top start point
        startX + length/2, startY + length/3,  // First angle point
        startX, startY + length,              // Bottom point
        startX - length/3, startY + length/2, // Second angle point
        startX + length/4, startY + length/4, // Additional point for more jaggedness
        startX, startY                        // Close the shape
    };
    
    // Thicker lightning by drawing multiple times
    for (int thickness = 1; thickness <= 3; thickness++) {
        // Slight offset for each drawing to create a glow effect
        int offsetBolt[12];
        for (int i = 0; i < 12; i++) {
            offsetBolt[i] = bolt[i] + (rand() % (thickness * 2) - thickness);
        }
        
        drawpoly(6, offsetBolt);
        fillpoly(6, offsetBolt);
    }
    
    // Add a subtle glow effect
    setcolor(LIGHTCYAN);
    for (int i = 0; i < 5; i++) {
        int glowBolt[12];
        for (int j = 0; j < 12; j++) {
            glowBolt[j] = bolt[j] + (rand() % 10 - 5);
        }
        drawpoly(6, glowBolt);
    }
}

// Function to draw stickman
void drawStickman() {
    setcolor(WHITE);
    // Head
    circle(x, GroundY - 90, 10);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(x, GroundY - 90, WHITE);

    // Body
    line(x,GroundY-80,x,GroundY-40);
    
    // Arms
    line(x,GroundY-70,x+10,GroundY-60);
    line(x,GroundY-65,x+10,GroundY-55);
    line(x+10,GroundY-60,x+20,GroundY-70);
    line(x+10,GroundY-55,x+20,GroundY-70);

    // Umbrella
    line(x+20,GroundY-70,x+20,GroundY-120);
    setfillstyle(SOLID_FILL, BLUE);
    setcolor(WHITE);
    pieslice(x+20,GroundY-120,0,180,50);

    // Legs
    line(x,GroundY-40,x+ldisp,GroundY-8);
    line(x,GroundY-40,x-ldisp,GroundY-8);
}

// Function to generate rain
void generateRain() {
    setcolor(WHITE);
    int i, rx, ry;
    for (i = 0; i <= 700; i++) {
        rx = rand() % ScreenWidth;
        ry = rand() % ScreenHeight;
        if (ry < GroundY - 4) {
            if (ry < GroundY-120 || (ry > GroundY-120 && (rx < x-25 || rx > x+65)))
                line(rx, ry, rx + 0.5, ry + 4);
        }
    }
}

// Function to display game stats
void displayGameStats() {
    char scoreStr[50], livesStr[50];
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    
    sprintf(scoreStr, "Score: %d", score);
    sprintf(livesStr, "Lives: %d", lives);
    
    outtextxy(10, 10, scoreStr);
    outtextxy(10, 30, livesStr);
}

// Function to check if lightning hits the stickman
bool isStickmanHit(int lightX, int lightY, int lightLength) {
    // Define stickman's bounding box
    int stickmanLeft = x - 20;
    int stickmanRight = x + 40;
    int stickmanTop = GroundY - 120;
    int stickmanBottom = GroundY;

    // Check if lightning bolt intersects with stickman's area
    return (lightX >= stickmanLeft && lightX <= stickmanRight &&
            lightY + lightLength >= stickmanTop && lightY <= stickmanBottom);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    
    // Seed random number generator
    srand(time(NULL));
    
    // Initialize page flipping variables
    int page = 0;
    
    // Set initial pages
    setactivepage(1);
    setvisualpage(0);
    
    while(1) {
        // Set the active page (the one we draw to)
        setactivepage(page);
        cleardevice();
        
        // Break condition
        if (kbhit() && getch() == 27) break;  // ESC key to exit
        
        // Game over check
        if (isGameOver) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            setcolor(RED);
            outtextxy(ScreenWidth/2 - 150, ScreenHeight/2, "GAME OVER!");
            
            // Make sure the game over screen is visible
            setvisualpage(page);
            delay(2000);
            break;
        }
        
        // Background elements
        drawBackground();
        drawClouds();
        
        // Lightning mechanics
        if (!isLightningActive) {
            warningTimer++;
            
            if (warningTimer >= lightningFrequency && rand() % 10 < 7) {
                // Lightning generation with more variability
                lightningX = minLightningX + rand() % (maxLightningX - minLightningX);
                lightningY = minLightningY + rand() % (maxLightningY - minLightningY);
                lightningLength = minLightningLength + rand() % (maxLightningLength - minLightningLength);
                
                isLightningActive = true;
                currentLightningFrame = 0;
            }
        } else {
            // Draw lightning for multiple frames
            drawLightningBolt(lightningX, lightningY, lightningLength);
            
            // Check if stickman is hit
            if (isStickmanHit(lightningX, lightningY, lightningLength)) {
                lives--;
                showHitMessage = true;
                hitMessageTimer = 10;  // Show hit message for 10 frames
                
                // Check game over condition
                isGameOver = (lives <= 0);
            } else {
                score += 10;
            }
            
            currentLightningFrame++;
            if (currentLightningFrame >= lightningDuration) {
                isLightningActive = false;
                warningTimer = 0;
            }
        }
        
        // Player movement (non-blocking)
        if (kbhit()) {
            int key = getch();
            switch(key) {
                case 75:  // Left arrow
                    x = (x - 20 > 0) ? x - 20 : x;
                    break;
                case 77:  // Right arrow
                    x = (x + 20 < ScreenWidth) ? x + 20 : x;
                    break;
            }
        }
        
        // Draw stickman and rain
        drawStickman();
        generateRain();
        
        // Display game stats
        displayGameStats();
        
        // Show hit message if needed
        if (showHitMessage) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            setcolor(RED);
            outtextxy(ScreenWidth/2 - 100, ScreenHeight/2, "Lightning Hit!");
            hitMessageTimer--;
            if (hitMessageTimer <= 0) {
                showHitMessage = false;
            }
        }
        
        // Animation updates
        x = (x + 2) % ScreenWidth;
        ldisp = (ldisp + 2) % 20;
        
        // Flip pages
        setvisualpage(page);
        page = 1 - page;  // Toggle between 0 and 1
        
        delay(50);
    }
    
    closegraph();
    return 0;
}
