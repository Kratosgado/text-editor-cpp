#include "TextEditor.h"
#include <iostream>

TextEditor::TextEditor() : window(sf::VideoMode(800, 600), "Text Editor") {}

void TextEditor::run() {
   while (window.isOpen()) {
      handleEvents();
      // update();
      render();
   }
}

void TextEditor::handleEvents() {
   sf::Event event;
   while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
         window.close();
      else if (event.type == sf::Event::KeyPressed) {
         if (event.key.code == sf::Keyboard::N && event.key.control) {
            createNewDocument();
         }
         else if (event.key.code == sf::Keyboard::O && event.key.control) {
            openDocument();
         }
         else if (event.key.code == sf::Keyboard::S && event.key.control) {
            saveDocument();
         }
      }
   }
}

void TextEditor::render() {
   window.clear();

   // render the document
   sf::Font font;
   if (!font.loadFromFile("CascadiaMono.ttf")) {
      std::cerr << "Error: Could not load font\n";
      return;
   }
   sf::Text text(document.getContent(), font, 20);
   window.draw(text);
   window.display();
}

void TextEditor::createNewDocument() {
   std::cin.ignore(); // clear newline from previous input
   std::string newContent;
   std::cout << "Enter the content of the new document:\n";
   std::getline(std::cin, newContent);
   document.setContent(newContent);
}

void TextEditor::openDocument() {
    std::string filename;
    std::cout << "Enter filename to open: ";
    std::cin >> filename;
    document.setFilename(filename);

    if (document.loadFromFile()) {
        std::cout << "Document opened successfully.\n";
    }
}

void TextEditor::saveDocument() {
    if (!document.isEmpty()) {
        std::string filename;
        std::cout << "Enter filename to save: ";
        std::cin >> filename;
        document.setFilename(filename);
        document.saveToFile();
    } else {
        std::cout << "The document is empty. Nothing to save.\n";
    }
}