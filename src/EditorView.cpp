#include "EditorView.h"

EditorView::EditorView(
   const sf::RenderWindow& window,
   const sf::String& workinDir,
   EditorContent& editorContent
) : content(editorContent),
camera(sf::FloatRect(-50, 0, window.getSize().x, window.getSize().y)),
deltaScroll(20), deltaRotation(2), deltaZoomIn(0.8f), deltaZoomOut(1.2f) {
   this->font.loadFromFile(workinDir + "fonts/CascadiaMono.ttf");
   this->bottomLimitPx = 1;
   this->rightLimitPx = 1;

   this->setFontSize(18); // important to call

   this->marginXOffset = 45;
   this->colorMargin = sf::Color(32, 44, 68);

   this->colorChar = sf::Color::White;
   this->colorSelection = sf::Color(106, 154, 232);
}

void EditorView::setFontSize(int fontSize) {
   this->fontSize = fontSize;
   this->lineHeight = fontSize;

   // HACK: Because I use only monospace fonts, every char is the same width
    //       so I get the width drawing a single character (A WIDE ONE TO BE SURE)
   sf::Text tmpText;
   tmpText.setFont(this->font);
   tmpText.setCharacterSize(this->fontSize);
   tmpText.setString("_");
   this->charWidth = tmpText.getLocalBounds().width;
}

void EditorView::draw(sf::RenderWindow& window) {
   this->drawLines(window);

   for (int lineNumber = 0; lineNumber < this->content; lineNumber++)
   {
      /* code */
   }
   
}