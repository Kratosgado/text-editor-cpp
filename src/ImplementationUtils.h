#if !defined(ImplementationUtils_H)
#define ImplementationUtils_H

#include <string>

class ImplementationUtils {
public:
   // returns the current working directory
   static std::string getWorkingDirectory(const std::string&);
};

#endif // ImplementationUtils_H
