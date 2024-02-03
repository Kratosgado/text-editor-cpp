#include <SFML/Graphics.hpp>
#include "src/ImplementationUtils.h"
#include "src/text_handlers/TextDocument.h"
#include "src/editor_handlers/EditorContent.h"
#include "src/editor_handlers/EditorView.h"
#include "src/input_handlers/InputController.h"

int main(int argc, char const* argv[]) {
   std::string workingDir = ImplementationUtils::getWorkingDirectory(argv[0]);

   std::string saveFileName, loadFileName;

   saveFileName = loadFileName = workingDir + ((argc == 2) ? argv[1] : "txt/defaultName.txt");

   sf::RenderWindow window(sf::VideoMode(720, 405), "Gado Text");
   window.setVerticalSyncEnabled(true);
   sf::Color backgroundColor = sf::Color(21, 29, 45);

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
            editorView.setCameraBounds(event.size.width, event.size.height);
         }
         if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            if (document.hasChanged()) {
               document.saveFile(saveFileName);
               std::cout << "SAVED TO: " << saveFileName << "\n";
            }
         }
         inputController.handleEvents(editorView, window, event);
      }
      inputController.handleConstantInput(editorView, window);

      window.clear(backgroundColor);
      window.setView(editorView.getCameraView());
      editorView.draw(window);
      window.display();
   }
   return 0;
}
