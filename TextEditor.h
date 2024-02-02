#if !defined(TEXTEDITOR_H)
#define TEXTEDITOR_H

#include "Document.h"
#include <SFML/Graphics.hpp>

class TextEditor {
private:
   Document document;
   sf::RenderWindow window;

   // private functions
   void handleEvents();
   void createNewDocument();
   void openDocument();
   void saveDocument();
   void render();
public:
   TextEditor();
   void run();
   // void update();
};

#endif // TEXTEDITOR_H
