#include "Document.h"
#include <iostream>
#include <fstream>

Document::Document() : content(""), filename(""), saved(true) {}

void Document::setContent(const std::string& newContent) {
   content = newContent;
   saved = false;
}

const std::string& Document::getContent() const { return content; }

void Document::setFilename(const std::string& newFilename) {
   filename = newFilename;
   saved = false;
}

const std::string& Document::getFilename() const { return filename; }

bool Document::isEmpty() const { return content.empty(); }

bool Document::loadFromFile() {
   std::ifstream file(filename);
   if (file.is_open()) {
      std::string line;
      content = "";
      while (std::getline(file, line)) {
         content += line + "\n";
      }
      file.close();
      saved = true;
      return true;
   }
   else {
      std::cout << "Error: Could not open file\n";
      return false;
   }
}

bool Document::saveToFile() {
   std::ofstream file(filename);
   if (file.is_open()) {
      file << content;
      file.close();
      saved = true;
      return true;
   }
   else {
      std::cout << "Error: Could not save file\n";
      return false;
   }
}

