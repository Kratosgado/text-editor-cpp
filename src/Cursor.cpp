#include "Cursor.h"

Cursor::Cursor() : Cursor(0, 0) {};

Cursor::Cursor(int lineN, int charN) {
   this->maxCharNReached = 0;
   this->updatePos(lineN, charN);
}

int Cursor::getLineN() {
   return this->lineN;
}

int Cursor::getCharN() {
   return this->charN;
}

void Cursor::updatePos(int l, int c) {
   this->lineN = l;
   this->charN = c;
}