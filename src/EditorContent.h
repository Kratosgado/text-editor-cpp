#if !defined(EditorContent_H)
#define EditorContent_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"
#include "Cursor.h"
#include "SelectionData.h"

class EditorContent {
private:
   TextDocument& document;
   sf::Font font;
   Cursor cursor;
   SelectionData selections;

public:
   EditorContent(TextDocument&);


   void createNewSelection(int anclaLine, int anclaChar);
   void createNewSelectionFromCursor();
   void updateLastSelection(int lineN, int charN);

   void removeSelections();
   SelectionData::Selection getLastSelection();

   void duplicateCursorLine();
   void swapCursorLine(bool swapWithUp);
   void swapSelectedLines(bool swapWithUp);

   bool isSelected(int lineNumber, int charIndexInLine);
   bool deleteSelections();
   sf::String copySelections();

   // TODO: Se puede pasar los valores por defecto al .cpp ?
   bool moveCursorLeft(bool updateActiveSelections = false);
   void moveCursorRight(bool updateActiveSelections = false);
   void moveCursorUp(bool updateActiveSelections = false);
   void moveCursorDown(bool updateActiveSelections = false);

   void moveCursorToEnd(bool updateActiveSelections = false);
   void moveCursorToStart(bool updateActiveSelections = false);

   void addTextInCursorPos(sf::String text);
   void deleteTextAfterCursorPos(int amount);
   void deleteTextBeforeCursorPos(int amount);

   int linesCount();
   int colsInLine(int line);
   sf::String getLine(int line);
   sf::String getCursorLine();

   void resetCursor(int line, int column);
   std::pair<int, int> cursorPosition();
   int getCharIndexOfColumn(int lineN, int column);
   int getColumnFromCharN(int lineN, int charN);


};

#endif // EditorContent_H
