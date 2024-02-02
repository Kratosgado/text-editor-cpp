#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0) {};

Cursor::Cursor(int lineN, int charN) {
   this->maxCharReached = 0;
   this->updatePos(lineN, charN);
}



void Cursor::updatePos(int l, int c) {
   this->lineN = l;
   this->charN = c;
}