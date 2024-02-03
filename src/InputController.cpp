#include "InputController.h"

using namespace sf;

InputController::InputController(EditorContent& editorContent) :editorContent(editorContent) {
   this->mouseDown = false;
   this->shiftPressed = false;
}
bool isKeyPressed(Keyboard::Key key, Keyboard::Key keyl = Keyboard::Unknown) {
   if (keyl != Keyboard::Unknown)
      return Keyboard::isKeyPressed(key) || Keyboard::isKeyPressed(keyl);
   return Keyboard::isKeyPressed(key);
}

void InputController::handleConstantInput(EditorView& textView, sf::RenderWindow& window) {
   // rotating
   if (isKeyPressed(Keyboard::LControl)) {
      if (isKeyPressed(Keyboard::R)) {
         if (isKeyPressed(Keyboard::Left)) {
            textView.rotateRight();
         }
         if (isKeyPressed(Keyboard::Right)) {
            textView.rotateRight();
         }
      }
   }

   if (this->isMouseDown()) {
      auto mousepos = sf::Mouse::getPosition(window);
      auto mousepos_text = window.mapPixelToCoords(mousepos);

      updateCursorInEditor(textView, mousepos_text.x, mousepos_text.y);

      float textViewTop = 0;
      float textViewBottom = window.getView().getSize().y - 5;
      float textViewLeft = 0;
      float textViewRight = window.getView().getSize().x;

      if (mousepos.x < textViewLeft) {
         textView.scrollLeft(window);
      }
      else if (mousepos.x > textViewRight) {
         textView.scrollRight(window);
      }
      if (mousepos.y < textViewTop) {
         textView.scrollUp(window);
      }
      else if (mousepos.y > textViewBottom) {
         textView.scrollDown(window);
      }
   }
}

void InputController::handleEvents(EditorView& textView,
   RenderWindow& window, Event& event) {
   // this->handleMouseEvents(textView, window, event);
   this->handleKeyPressedEvents(textView, event);
   this->handleKeyReleasedEvents(event);
   this->handleTextEnteredEvent(event);
}

void InputController::handleKeyPressedEvents(EditorView& textView, Event& event) {
   if (event.type == Event::KeyPressed) {
      bool isCtrlPressed = isKeyPressed(Keyboard::LControl, Keyboard::RControl);
      bool isShiftPressed = isKeyPressed(Keyboard::LShift, Keyboard::RShift);
      bool isEndPressed = isKeyPressed(Keyboard::End);
      bool isHomePressed = isKeyPressed(Keyboard::Home);


      if (event.key.code == Keyboard::LShift || event.key.code == Keyboard::RShift) {
         if (!this->shiftPressed && !isCtrlPressed) {
            this->shiftPressed = true;
            this->editorContent.removeSelections();
            this->editorContent.createNewSelectionFromCursor();
            return;
         }
      }
      if (isEndPressed) {
         editorContent.moveCursorToEnd(isShiftPressed);
         return;
      }
      else if (isHomePressed) {
         editorContent.moveCursorToStart(isShiftPressed);
         return;
      }
      bool ctrlAndShift = isCtrlPressed && isShiftPressed;
      if (isCtrlPressed) {
         if (event.key.code == sf::Keyboard::D) {
            editorContent.duplicateCursorLine();
         }
         else if (event.key.code == sf::Keyboard::U) {
            editorContent.deleteSelections();
            sf::String emoji = "\\_('-')_/";
            editorContent.addTextInCursorPos(emoji);
         }
         else if (event.key.code == sf::Keyboard::C) {  //Copy command, Ctrl + C
            this->stringCopied = editorContent.copySelections();
            if (this->stringCopied.isEmpty()) {
               this->stringCopied = editorContent.getCursorLine();
            }
         }
         else if (event.key.code == sf::Keyboard::V) {  //Paste command, Ctrl + V
            editorContent.addTextInCursorPos(stringCopied);
         }
         else if (event.key.code == sf::Keyboard::X) {  //Cut command, Ctrl + X
            this->stringCopied = editorContent.copySelections();
            editorContent.deleteSelections();
         }
      }
      if (event.key.code == sf::Keyboard::Up) {
         if (ctrlAndShift) {
            editorContent.swapSelectedLines(true);
            editorContent.moveCursorUp(true);
            return;
         }
         else {
            editorContent.moveCursorUp(this->shiftPressed);
            return;
         }
      }
      if (event.key.code == sf::Keyboard::Down) {
         if (ctrlAndShift) {
            editorContent.swapSelectedLines(false);
            editorContent.moveCursorDown(true);
            return;
         }
         else {
            editorContent.moveCursorDown(this->shiftPressed);
            return;
         }
      }
      if (event.key.code == sf::Keyboard::Left) {
         editorContent.moveCursorLeft(this->shiftPressed && !isCtrlPressed);
         return;
      }
      if (event.key.code == sf::Keyboard::Right) {
         editorContent.moveCursorRight(this->shiftPressed && !isCtrlPressed);
         return;
      }

      if (event.key.control) {
         if (event.key.code == sf::Keyboard::Add) {
            textView.zoomIn();
            return;
         }
         if (event.key.code == sf::Keyboard::Subtract) {
            textView.zoomOut();
            return;
         }
      }
   }
}

void InputController::handleKeyReleasedEvents(sf::Event& event) {
   if (event.type == sf::Event::KeyReleased) {
      if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
         this->shiftPressed = isKeyPressed(Keyboard::LShift, Keyboard::RShift);
      }
   }
}

void InputController::handleTextEnteredEvent(Event& event) {
   if (event.type == Event::TextEntered) {
      bool isCtrlPressed = isKeyPressed(Keyboard::LControl);
      sf::String input(event.text.unicode);

      // if (event.text.unicode == '\b') {
      //    bool selectionDeleted = editorContent.deleteSelections();
      //    if (!selectionDeleted) editorContent.deleteTextBeforeCursorPos(1);
      // }
      // else if (event.text.unicode == 127) { // 127 == delete(supr)
      //    bool selecionDeleted = editorContent.deleteSelections();
      //    if (!selecionDeleted) {
      //       editorContent.deleteTextAfterCursorPos(1);
      //    }
      // }
      // else if (!isCtrlPressed) {
      //    if (event.text.unicode = '\t') {
      //       std::cerr << "TABS NOT ACTIVATED" << std::endl;
      //       // todo
      //    }
      //    editorContent.deleteSelections();
      //    editorContent.addTextInCursorPos(input);
      // }
   }
}

bool InputController::isMouseDown() { return this->mouseDown; }

void InputController::updateCursorInEditor(EditorView& textView, float mouseX, float mouseY) {
   std::pair<int, int> docCoords = textView.getDocumentCoords(mouseX, mouseY);
   int line = docCoords.first;
   int column = docCoords.second;

   this->editorContent.resetCursor(line, column);

   // this->editorContent.updateLastSelection(line, column);
}