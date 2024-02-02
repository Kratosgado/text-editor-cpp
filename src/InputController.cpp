#include "InputController.h"

InputController::InputController(EditorContent& editorContent) :editorContent(editorContent) {
   this->mouseDown = false;
   this->shiftPressed = false;
}