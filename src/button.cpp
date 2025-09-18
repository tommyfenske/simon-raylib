#include "button.hpp"

#include <iostream>
using namespace std;


Button::Button(){};
Button::Button(int i, Rectangle rec, Color regCol, Color hiCol)
{
    this->i = i;
    this->rect = rec;
    this->drawHi = false;
    this->regColor = regCol;
    this->hiColor = hiCol;
    this->drawColor = regColor;
}

void Button::update()
{
            
}

void Button::draw()
{
    DrawRectangleRec(rect, drawColor);
}

void Button::print()
{
    cout << "Button" << endl;
}

Rectangle Button::getRect()
{
    return rect;
}

void Button::setColorHi()
{
    drawColor = hiColor;
}

void Button::setColorReg()
{
    drawColor = regColor;
}