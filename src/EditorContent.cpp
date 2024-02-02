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

int EditorContent::linesCount() {
   return this->document.getLineCount();
}