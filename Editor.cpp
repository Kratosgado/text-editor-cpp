#include <SFML/Graphics.hpp>
#include "src/ImplementationUtils.h"
#include "src/TextDocument.h"
#include "src/EditorContent.h"
#include "src/EditorView.h"
#include "src/InputController.h"

int main(int argc, char const* argv[]) {
   std::string workingDir = ImplementationUtils::getWorkingDirectory(argv[0]);

   std::string saveFileName;
   std::string loadFileName;

   // if (argc == 2) {
   //    saveFileName = loadFileName = workingDir + argv[1];
   // }
   // else {
   //    saveFileName = loadFileName = workingDir + "txt/defaultName.txt";
   //  }
   saveFileName = loadFileName = workingDir + ((argc == 2) ? argv[1] : "txt/defaultName.txt");

   sf::RenderWindow window(sf::VideoMode(720, 405), "Gado Text");
   window.setVerticalSyncEnabled(true);
   sf::Color backgroundColor = sf::Color(21, 29, 45);

   // Todo:: create text documents
   TextDocument document;
   document.init(loadFileName);

   EditorContent editorContent(document);
   EditorView editorView(window, workingDir, editorContent);

   InputController inputController(editorContent);

   while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) window.close();
         if (event.type == sf::Event::Resized) {
            // todo:: handle resize
         }
         if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            // todo:: handle saving
         }
      }
      // todo:: input controlls

      window.clear(backgroundColor);
      window.setView(editorView.getCameraView());
      editorView.draw(window);
      window.display();
   }
   return 0;
}
