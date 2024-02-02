#include "SelectionData.h"

SelectionData::SelectionData() : lastSelectionIndex(-1) {}

bool SelectionData::isSelected(int lineN, int charN) const {
   for (const Selection sel : this->selections)
   {
      if (!sel.active) continue;
      SelectionData::Extreme start;
      SelectionData::Extreme end;

      if (sel.begin < sel.extreme) {
         start = sel.begin;
         end = sel.extreme;
      }
      else {
         start = sel.extreme;
         end = sel.begin;
      }

      if (start.lineN <= lineN && lineN <= end.lineN) {
         if (start.lineN < lineN && lineN < end.lineN) return true;
         else if (start.lineN == lineN && lineN < end.lineN) {
            if (start.charN <= charN) return true;
         }
         else if (start.lineN < lineN && lineN == end.lineN) {
            if (charN < end.charN) return true;
         }
         else if (start.lineN == lineN && lineN == end.lineN) {
            if (start.charN <= charN && charN < end.charN) return true;
         }
      }
   }
   return false;
}