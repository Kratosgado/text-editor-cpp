#if !defined(DOCUMENT_H)
#define DOCUMENT_H

#include <string>

class Document {
private:
   std::string content;
   std::string filename;
   bool saved = true;
public:
   // Document() = default;
   Document();

   // Getters and setters
   void setContent(const std::string& newContent);
   const std::string& getContent() const;

   void setFilename(const std::string& filename);
   const std::string& getFilename() const;

   // void setSaved(bool saved);
   bool isEmpty() const;
   bool loadFromFile();
   bool saveToFile();

   // void load(const std::string& filename);
   // void save(const std::string& filename);
   // void append(const std::string& text);
   // void insert(const std::string& text, std::size_t position);
   // void erase(std::size_t position, std::size_t length);
   // std::string get_text() const;
   // std::size_t get_length() const;
   // std::string get_filename() const;
   // bool is_saved() const;
   // void set_saved(bool saved);

};

#endif // DOCUMENT_H
