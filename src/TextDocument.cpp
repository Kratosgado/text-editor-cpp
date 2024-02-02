#include "TextDocument.h"

bool TextDocument::init(string& filename) {
   std::ifstream inputFile(filename);
   if (!inputFile.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl;
      return false;
   }
   std::stringstream inputStringStream;
   inputStringStream << inputFile.rdbuf();

   this->buffer = this->toUtf32(inputStringStream.str());
   this->length = buffer.getSize();

   inputFile.close();
   this->initLineBuffer();
   return true;
}

bool TextDocument::saveFile(string& filename) {
   std::ofstream outFile(filename);
   if (!outFile.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl;
      return false;
   }
   std::stringstream toBeSaved;
   for (sf::Uint32 ch : this->buffer) {
      toBeSaved << SpecialChars::convertSpecialChar(ch, outFile);
   }
   outFile << toBeSaved.str();
   outFile.close();
   this->documentHasChanged = false;
   return true;
}

bool TextDocument::hasChanged() const { return this->documentHasChanged; }

bool TextDocument::initLineBuffer() {
   int lineStart = 0;
   this->lineBuffer.clear();
   this->lineBuffer.push_back(lineStart);

   for (int i = 0; i < this->buffer.getSize(); i++) {
      if (this->buffer[i] == '\n' || this->buffer[i] == 13) {
         lineStart = i + 1;
         this->lineBuffer.push_back(lineStart);
      }
   }
   return true;
}

sf::String TextDocument::toUtf32(const string& inString) {
   sf::String outString = "";
   auto iterEnd = inString.cend();

   // decode the string to sf::String
   for (auto iter = inString.cbegin(); iter != iterEnd;) {
      sf::Uint32 out;
      iter = sf::Utf8::decode(iter, iterEnd, out);
      outString += out;
   }
   return outString;

}

sf::String TextDocument::getLine(int lineNumber) {
   int lastLine = this->lineBuffer.size() - 1;

   if (lineNumber < 0 || lineNumber > lastLine) {
      std::cerr << "lineNumber " << lineNumber << " is not a valid number line. " << "Max is: " << lastLine << std::endl;
      return "";
   }
   if (lineNumber == lastLine) {
      return this->buffer.substring(this->lineBuffer[lineNumber]);
   }
   else {
      int bufferStart = this->lineBuffer[lineNumber];
      int nextBufferStart = this->lineBuffer[lineNumber + 1];// final no inclusive
      int cantidad = nextBufferStart - bufferStart - 1;
      return this->buffer.substring(bufferStart, cantidad);
   }
}

void TextDocument::addTextToPos(sf::String text, int line, int charN) {
   this->documentHasChanged = true;

   int textSize = text.getSize();
   // todo
}

int TextDocument::getLineCount() const {
   return (int)this->lineBuffer.size();
}