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
// Functions
static void PlaySequence(void);
static void AddToSequence(void);

//Variables
Button buttons[4];
vector<int> sequence = {0, 1, 2, 3}; // each int corresponds to the button to be pressed
bool isAnimating = false;
int indexAnimating = -1;

int userIndex = -1;
int userGuess = -1;

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

// SOUNDS
static const string btnTones[4] = {
	"assets/tone-1.wav",
	"assets/tone-2.wav",
	"assets/tone-3.wav",
	"assets/tone-4.wav"
};

int main() {
	InitWindow(screenWidth, screenHeight, "S I M O N");
	InitAudioDevice();
	//ToggleFullscreen();

	InitGame();
	SetTargetFPS(60);

	PlaySequence(); // TODO: move to a better spot later

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
	static const Rectangle btnHiRecs[4] = {
		{ screenWidth/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, screenHeight/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH },	// UPLEFT
		{ screenWidth/2.0f + BUTTON_MARGIN, screenHeight/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH },					// UPRIGHT
		{ screenWidth/2.0f + BUTTON_MARGIN, screenHeight/2.0f + BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH },								// DOWNRIGHT
		{ screenWidth/2.0f - BUTTON_WIDTH - BUTTON_MARGIN, screenHeight/2.0f + BUTTON_MARGIN, BUTTON_WIDTH, BUTTON_WIDTH }					// DOWNLEFT
	};
	// Populate Buttons
	for (int i = 0; i < 4; i++) {
		Button b = Button(i, btnRecs[i], btnHiRecs[i], btnRegColors[i], btnHiColors[i], btnTones[i]);
		buttons[i] = b;
	}
	
}

void UpdateGame(void)
{
	// UPDATE BUTTONS
    for (int i = 0; i < 4; i++) {

		if (!isAnimating) {
			// Highlight if colliding
			if ( buttons[i].IsCollidingPt( GetMousePosition() ) ) {
				buttons[i].SetColorHi();
			} else {
				buttons[i].SetColorReg();
			}
		}

		buttons[i].Update();
    }

	
	if (isAnimating) { // ANIMATE SEQUENCE
		// If current animation has finished
		if ( ! buttons[ sequence.at(indexAnimating) ].IsAnimating() ) {
			// If more buttons in sequence
			if (++indexAnimating < int(sequence.size() ) ) {
				// Start next button animation
				buttons[ sequence.at(indexAnimating) ].StartAnim();
			} else {
				// End Sequence Animation
				isAnimating = false;
				AddToSequence();
			}
		}	
	} else { // GET USER SEQUENCE

	}
}

void DrawGame(void)
{
	BeginDrawing();
    
    	ClearBackground(BLACK);
		DrawFPS(10, 10);

		for (Button b : buttons) {
        	b.Draw();
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

void PlaySequence()
{
	indexAnimating = 0;
	isAnimating = true;

	buttons[ sequence.at(indexAnimating) ].StartAnim();
}

void AddToSequence()
{
	sequence.push_back( GetRandomValue(0,3) );
	PlaySequence();
}