#if !defined(Cursor_H)
#define Cursor_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Cursor {
private:
   int lineN, charN;
   int maxCharReached;

   void updatePos(int posY, int posX);
public:
   Cursor();
   Cursor(int lineN, int charN);
};

#endif // Cursor_H
