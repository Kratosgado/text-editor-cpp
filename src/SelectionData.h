#if !defined(SelectionData_H)
#define SelectionData_H

#include <iostream>
#include <vector>
#include "TextDocument.h"

class SelectionData {
private:
   struct Extreme {
      Extreme() : lineN(-1), charN(-1) {}
      Extreme(int lineN, int charN) : lineN(lineN), charN(charN) {};
      int lineN;
      int charN;

      bool operator<(const Extreme& ex) const {
         return lineN < ex.lineN || (lineN <= ex.lineN && charN < ex.charN);
      }
   };

public:
   SelectionData();
   struct Selection {
      bool active;
      SelectionData::Extreme extreme;
      SelectionData::Extreme begin;
      Selection() : active(false), begin(), extreme() {}
      Selection(int beginLine, int beginChar) : active(false), begin(beginLine, beginChar), extreme() {};
   };
   bool isSelected(int lineN, int charN) const;

private:
   std::vector<Selection> selections;
   int lastSelectionIndex;
   
};

#endif // SelectionData_H
