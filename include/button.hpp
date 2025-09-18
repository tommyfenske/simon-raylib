#pragma once
#include "raylib.h"
#include <string>
using namespace std;

/** 
 * @class Button
 * @brief 
 */
class Button {
    private:
        int i; // index of the button, 0: top left, 1: top right, 2: bottom right, 3: bottom left

        Rectangle rect; // draw and collision rectangle object for button
        Rectangle hiRect; // rectangle used for an outline when drawing the button

        Color regColor; // default color 
        Color hiColor; // lighter, highlight color
        Color drawColor; // contains the color that is actually being drawn

        bool isAnimating; // true if the button is currently animating
        int frameCount; // how many frames the animation has animated
        int frameMax; // max length of the animation
        int animBuffer; // how many frames of a cooldown after the animation has finished

        Sound tone; // contains the loaded soundfx
    public:
        Button();
        Button(int i, Rectangle rec, Rectangle hiRec, Color regCol, Color hiCol, string tonePath);

        /**
         * @brief Called every update frame.
         */
        void Update();

        /**
         * @brief Called every draw frame.
         */
        void Draw();

        /**
         * @brief Prints the Button's information to console.
         */
        void Print();

        /**
         * @brief Checks button's collision with a given point
         * @return True if colliding with point, otherwise false
         */
        bool IsCollidingPt(Vector2 pt);

        /**
         * @brief Sets button's draw color to it's hilight color
         */
        void SetColorHi();

        /**
         * @brief Sets button's draw color to it's regular/default color
         */
        void SetColorReg();

        /**
         * @brief Returns the button's i attribute
         * @return i value
         */
        int GetI();

        /**
         * @brief Checks if the current button is in an animation
         * @return isAnimating attribute
         */
        bool IsAnimating();

        /**
         * @brief Triggers the button to start it's animation
         */
        void StartAnim();

        /**
         * @brief Contains logic for animating the draw color of the button to make it glow
         */
        void GlowAnimation();

        /**
         * @brief Prints the Button's drawColor to console.
         */
        void PrintDrawColor();

        /**
         * @brief Plays the buttons corresponding tone
         */
        void PlayTone();
};