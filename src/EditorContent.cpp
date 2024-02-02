#include "EditorContent.h"

EditorContent::EditorContent(TextDocument& textDocument) : document(textDocument) {
   this->cursor = Cursor(0, 0);
}

bool EditorContent::isSelected(int lineNumber, int charIndexInLine) {
   return this->selections.isSelected(lineNumber, charIndexInLine);
}

sf::String EditorContent::getLine(int line) {
   return this->document.getLine(line);
}

std::pair<int, int> EditorContent::cursorPosition() {
   int lineN = this->cursor.getLineN();
   int charN = this->cursor.getCharN();
   int column = this->getColumnFromCharN(lineN, charN);

   return std::pair<int, int>(lineN, column);
}

int EditorContent::linesCount() {
   return this->document.getLineCount();
}

int EditorContent::getColumnFromCharN(int lineN, int charN) {
   sf::String line = this->getLine(lineN);
   // int len = this->colsInLine(lineN);  // El nombre esta mal, pero devuelve los chars
   int currentCol = 0;
   for (int charNact = 0; charNact < charN; charNact++) {
      if (line[charNact] == '\t') {
         currentCol += 4;
      }
      else {
         currentCol++;
      }
   }

   return currentCol;
}
