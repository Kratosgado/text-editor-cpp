#if !defined(InputController_H)
#define InputController_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../editor_handlers/EditorView.h"
#include "../editor_handlers/EditorContent.h"

class InputController {
private:
   void handleMouseEvents(EditorView& view, sf::RenderWindow& window, sf::Event& event);
   void handleKeyPressedEvents(EditorView& view, sf::Event& event);
   void handleKeyReleasedEvents(sf::Event& event);
   void handleTextEnteredEvent(sf::Event& event);

   void updateCursorInEditor(EditorView& textView, float mouseX, float mouseY);

   bool mouseDown;
   bool shiftPressed;
   sf::String stringCopied;

   EditorContent& editorContent;

public:
   InputController(EditorContent& editorContent);
   void handleConstantInput(EditorView& view, sf::RenderWindow& window);
   void handleEvents(EditorView& view, sf::RenderWindow& window, sf::Event& event);
   bool isMouseDown();
};

#endif // InputController_H
