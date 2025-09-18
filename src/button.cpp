#include "button.hpp"

#include <iostream>
using namespace std;

Button::Button(){};
Button::Button(int i, Rectangle rec, Rectangle hiRec, Color regCol, Color hiCol, string tonePath)
{
    this->i = i;

    this->rect = rec;
    this->hiRect = hiRec;

    this->regColor = regCol;
    this->hiColor = hiCol;
    this->drawColor = regColor;

    this->isAnimating = false;
    this->frameCount = 0;
    this->frameMax = 60;
    this->animBuffer = 15;

    this->tone = LoadSound(tonePath.c_str());
}

void Button::Update()
{
    if (isAnimating) {
        GlowAnimation();
    }
}

void Button::Draw()
{
    DrawRectangleRounded(rect, 0.2, 1, drawColor);
    DrawRectangleRoundedLinesEx(hiRect, 0.2, 1, 3, regColor);
}

void Button::Print()
{
    cout << "Button" << endl;
}

bool Button::IsCollidingPt(Vector2 pt)
{
    return CheckCollisionPointRec(pt, rect);
}

void Button::SetColorHi()
{
    drawColor = hiColor;
}

void Button::SetColorReg()
{
    drawColor = regColor;
}

bool Button::IsAnimating()
{
    return isAnimating;
}

void Button::StartAnim()
{
    frameCount = 0;
    isAnimating = true;
    PlaySound(tone);
}

void Button::GlowAnimation()
{
    //cout << i << " : Animating : " << frameCount << endl;
 
    if (frameCount < frameMax) {
        SetColorHi();
        frameCount++;
    } else if (frameCount < frameMax + animBuffer) {
        SetColorReg();
        frameCount++;
    } else {
        isAnimating = false;
        drawColor = regColor;
    }
}

void Button::PrintDrawColor()
{
    printf("%x, %x, %x", drawColor.r, drawColor.g, drawColor.b);
}