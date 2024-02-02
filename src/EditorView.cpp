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

   for (int lineNumber = 0; lineNumber < this->content.linesCount(); lineNumber++) {
      int lineHeight = 1;
      int blockHeight = lineHeight * this->fontSize;

      sf::Text lineNumberText;
      lineNumberText.setFillColor(sf::Color::White);
      lineNumberText.setFont(this->font);
      lineNumberText.setString(std::to_string(lineNumber));
      lineNumberText.setCharacterSize(this->fontSize - 1);
      lineNumberText.setPosition(this->marginXOffset, blockHeight * (lineNumber - 1));

      sf::RectangleShape marginRect(sf::Vector2f(this->marginXOffset - 5, blockHeight));
      marginRect.setFillColor(this->colorMargin);
      marginRect.setPosition(-this->marginXOffset, blockHeight * (lineNumber - 1));

      window.draw(marginRect);
      window.draw(lineNumberText);
   }
   // todo draw cursor
}


int colsOf(sf::String& currentLineText) {
   int cols = 0;
   for (char c : currentLineText) {
      if (c == '\t') {
         cols += 4;
      }
      else {
         cols++;
      }
   }
   return cols;
}

void EditorView::drawLines(sf::RenderWindow& window) {
   this->bottomLimitPx = this->content.linesCount() * this->fontSize;
   for (int lineNumber = 0; lineNumber < this->content.linesCount(); lineNumber++) {
      sf::String line = this->content.getLine(lineNumber);
      sf::String currentLineText = "";

      this->rightLimitPx = std::max((int)this->rightLimitPx, (int)(this->charWidth * line.getSize()));

      float offsetx = 0;
      bool previousSelected = false;

      for (int charIndexInLine = 0; charIndexInLine < (int)line.getSize(); charIndexInLine++) {
         bool currentSelected = content.isSelected(lineNumber, charIndexInLine);

         if (currentSelected != previousSelected || charIndexInLine == (int)line.getSize()) {
            sf::Text texto;
            texto.setFillColor(this->colorChar);
            texto.setFont(font);
            texto.setString(currentLineText);
            texto.setCharacterSize(this->fontSize);
            texto.setPosition(offsetx, lineNumber * this->fontSize);

            if (previousSelected) {
               int currentColsAmount = colsOf(currentLineText);
               // todo
            }
            window.draw(texto);
            previousSelected = currentSelected;
            offsetx += this->charWidth * colsOf(currentLineText);
            currentLineText = "";
         }
         currentLineText += line[charIndexInLine];
      }
   }
}

sf::View EditorView::getCameraView() {
   return this->camera;
}