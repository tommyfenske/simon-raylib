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
        bool drawHi;
        Color regColor;
        Color hiColor;
        Color drawColor;
    public:
        Button();
        Button(int i, Rectangle rec, Color regCol, Color hiCol);

        /**
         * @brief Called every update frame.
         */
        void update();

        /**
         * @brief Called every draw frame.
         */
        void draw();

        /**
         * @brief Prints the Map's grid to console.
         */
        void print();

        Rectangle getRect();

        void setColorHi();

        void setColorReg();
};