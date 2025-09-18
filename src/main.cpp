#include <iostream>
using namespace std;
#include <vector>

// Raylib Headers
#include "raylib.h"
#include "raymath.h"

// Simon Headers
#include "button.hpp"

// Compile command:
// gcc src/*.cpp -o simon.exe -O1 -Wall -std=c++2c -lstdc++ -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm


// Global Variables
static const int screenWidth = 640;
static const int screenHeight = 360;

// Declare Raylib Game Functions
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

// Simon Declarations
Button buttons[4];
// COLORS
// https://lospec.com/palette-list/vanilla-milkshake
static const Color btnRegColors[4] = {
	{0xff, 0xc3, 0x84, 0xff},	// ffc384 ORANGE
	{0xb0, 0xa9, 0xe4, 0xff},	// b0a9e4 BLUE
	{0x87, 0xa8, 0x89, 0xff},	// 87a889 GREEN
	{0xf9, 0x82, 0x84, 0xff}	// f98284 RED
};
static const Color btnHiColors[4] = {
	{0xff, 0xf7, 0xa0, 0xff},	// fff7a0 ORANGE
	{0xac, 0xcc, 0xe4, 0xff},	// accce4 BLUE
	{0xb0, 0xeb, 0x93, 0xff},	// b0eb93 GREEN
	{0xfe, 0xaa, 0xe4, 0xff}	// feaae4 RED
};

int main() {
	InitWindow(screenWidth, screenHeight, "S I M O N");
	//ToggleFullscreen();

	InitGame();
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		UpdateDrawFrame();
	}

	UnloadGame();
	CloseWindow();
	return 0;
}

void InitGame(void)
{
	// Calculate Button Rectangle Objects
	const int BUTTON_WIDTH = 120;
	const int BUTTON_MARGIN = 5;
	static const Rectangle btnRecs[4] = {
		{ screenWidth/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, screenHeight/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH },	// UPLEFT
		{ screenWidth/2.0f + BUTTON_MARGIN, screenHeight/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH },					// UPRIGHT
		{ screenWidth/2.0f + BUTTON_MARGIN, screenHeight/2.0f + BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH },								// DOWNRIGHT
		{ screenWidth/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, screenHeight/2.0f + BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH }					// DOWNLEFT
	};
	// Populate Buttons
	for (int i = 0; i < 4; i++) {
		Button b = Button(i, btnRecs[i], btnRegColors[i], btnHiColors[i]);
		buttons[i] = b;
	}
}

void UpdateGame(void)
{
	Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < 4; i++) {
        // Highlight if colliding
        if ( CheckCollisionPointRec( mousePos, buttons[i].getRect() ) ) {
			buttons[i].setColorHi();
		} else {
			buttons[i].setColorReg();
		}
    }
}

void DrawGame(void)
{
	BeginDrawing();
    
    	ClearBackground(BLACK);
		DrawFPS(10, 10);

		for (Button b : buttons) {
        	b.draw();
    	}

	EndDrawing();
}

void UnloadGame(void)
{

}

void UpdateDrawFrame(void)
{
	UpdateGame();
  	DrawGame();
}