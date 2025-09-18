#pragma once
#include "raylib.h"

/** 
 * @class Button
 * @brief 
 */
class Button {
    private:
        int i;
        Rectangle rect;
        Rectangle hiRect;
        bool drawHi;
        Color regColor;
        Color hiColor;
        Color drawColor;
        bool isAnimating;
        int frameCount;
        int frameMax;
        int animBuffer;
    public:
        Button();
        Button(int i, Rectangle rec, Rectangle hiRec, Color regCol, Color hiCol);

        /**
         * @brief Called every update frame.
         */
        void Update();

        /**
         * @brief Called every draw frame.
         */
        void Draw();

        /**
         * @brief Prints the Map's grid to console.
         */
        void Print();

        bool IsCollidingPt(Vector2 pt);

        void SetColorHi();

        void SetColorReg();

        bool IsAnimating();

        void StartAnim();

        void GlowAnimation();

        void PrintDrawColor();
};