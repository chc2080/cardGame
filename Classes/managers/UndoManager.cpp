#include "managers/UndoManager.h"

void UndoManager::pushRecord(const UndoModel& record) { _records.push_back(record); }
bool UndoManager::canUndo() const { return !_records.empty(); }
void UndoManager::clear() { _records.clear(); }

UndoModel UndoManager::popRecord()
{
    if (_records.empty()) return UndoModel();
    UndoModel last = _records.back();
    _records.pop_back();
    return last;
}