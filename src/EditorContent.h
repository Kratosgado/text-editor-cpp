#if !defined(EditorContent_H)
#define EditorContent_H

#include <SFML/Graphics.hpp>
#include "TextDocument.h"

class EditorContent {
private:
   TextDocument& document;
   sf::Font font;
   // cursor
   // selection data

public:
   EditorContent(TextDocument&);

};

#endif // EditorContent_H
