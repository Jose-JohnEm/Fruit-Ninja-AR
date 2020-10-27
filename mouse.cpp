#include "mouse.hpp"
#include <string>

using namespace std;

Mouse::Mouse()
{
    this->position = getRealPosition();
}

Mouse::~Mouse()
{

}

void Mouse::leftClick()
{
    exec(_XEC + _LC);
}

void Mouse::leftClick(int x, int y, bool move)
{
    if (move) setPosition(this->position.x + x, this->position.y + y);
    else setPosition(x, y);
    leftClick();
}

void Mouse::leftClick(Vec2 pos, bool move)
{
    if (move) setPosition(pos + this->position);
    else setPosition(pos);
    leftClick();
}

void Mouse::rightClick()
{
    exec(_XEC + _RC);
}

void Mouse::rightClick(int x, int y, bool move)
{
    if (move) setPosition(this->position.x + x, this->position.y + y);
    else setPosition(x, y);
    rightClick();
}

void Mouse::rightClick(Vec2 pos, bool move)
{
    if (move) setPosition(pos + this->position);
    else setPosition(pos);
    rightClick();
}

Vec2 Mouse::getPosition()
{
    return this->position;
}

void Mouse::setPosition(int x, int y)
{
    this->position.x = x;
    this->position.y = y;

    exec(_XEC + _MOVE + toBatPos(this->position));
}

void Mouse::setPosition(Vec2 pos)
{
    this->position = pos;
    exec(_XEC + _MOVE + toBatPos(pos));
}

void Mouse::move(int x, int y)
{
    this->position.x += x;
    this->position.y += y;

    setPosition(this->position);
}

void Mouse::move(Vec2 pos)
{
    this->position += pos;

    setPosition(this->position);
}

void Mouse::dragBy(int x, int y)
{
    this->position.x += x;
    this->position.y += y;

    exec(_XEC + _MOVE + toBatPos(this->position));
    setPosition(this->setPosition);
}

void Mouse::dragBy(Vec2 pos)
{
    this->position += pos;
    exec(_XEC + _MOVE + toBatPos(this->position));
    setPosition(this->setPosition);
}

void Mouse::dragTo(int x, int y)
{
    exec(_XEC + _MOVE + toBatPos((Vec2){x, y}));
    setPosition((Vec2){x, y});
}

void Mouse::dragTo(Vec2 pos)
{
    exec(_XEC + _MOVE + toBatPos(pos));
    setPosition(pos);
}

int stoi(const char *s)
{
    int i;
    i = 0;
    while(*s >= '0' && *s <= '9')
    {
        i = i * 10 + (*s - '0');
        s++;
    }
    return i;
}



Vec2 Mouse::getRealPosition()
{
    string res = exec(_XEC + _POS);
    size_t pos = res.find('x');
    Vec2 nPos; 
    
    nPos.x = stoi(res.substr(0, pos).c_str());
    nPos.y = stoi(res.substr(pos + 1).c_str());

    return nPos;
}

int power(int nb, int pow)
{
    int res(nb);

    while (pow > 1) {
        res *= nb;
        pow--;
    }

    return res;
}

string toS(int x)
{
    int n(0);
    string res;

    for (int cp(x); cp != 0; n++) {
        cp /= 10;
    }
    n--;
    for (; n > 0; n--) {
        res.push_back((x / power(10, n)) + 48);

        x %= power(10, n);
    }
    res.push_back(x + 48);
    return res;
}

string Mouse::toBatPos(int x, int y)
{
    string res = toS(x);

    res.push_back('x');
    res += toS(y);
    return res;
}

string Mouse::toBatPos(Vec2 pos)
{
    string res = toS(pos.x);

    res.push_back('x');
    res += toS(pos.y);
    return res;
}

string Mouse::exec(string command)
{
   char buffer[128];
   string result = "";

   // Open pipe to file
   FILE* pipe = popen(command.c_str(), "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

   pclose(pipe);
   return result;
}
