#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace std;

const string _XEC = "mouse.exe ";
const string _LC = "leftClick";
const string _RC = "rightClick";
const string _POS = "position";
const string _MOVE = "moveTo ";
cosnt string _DR = "dragTo";

struct Vec2
{
    int x;
    int y;

    Vec2 operator+(const Vec2 &a)
    {
        this->x += a.x;
        this->y += a.y;
        return *this;
    }
    
    Vec2& operator+=(const Vec2 &a)
    {
        this->x += a.x;
        this->y += a.y;
        return *this;
    }

};

class Mouse
{
    
    public:
        Mouse();
        ~Mouse();

        void leftClick();               // Do a left click
        void leftClick(int x, int y, bool move = false);   // Do a left click at position
        void leftClick(Vec2 position, bool move = false);

        void rightClick();              // Do a right click
        void rightClick(int x, int y, bool move = false);  // Do a right click at position
        void rightClick(Vec2 position, bool move = false);

        Vec2 getPosition();     // Get Position x,y of the cursor

        void setPosition(int x, int y);
        void setPosition(Vec2 position);

        void move(int x, int y);
        void move(Vec2 position);

        void dragBy(int x, int y);
        void dragBy(Vec2 position);

        void dragTo(int x, int y);
        vois dragTo(Vec2 position);
    
    private:
        Vec2 position;

        Vec2 getRealPosition();
        string toBatPos(Vec2 position);
        string toBatPos(int x, int y);
        string exec(string command); // éxécute les commandes

};

#endif