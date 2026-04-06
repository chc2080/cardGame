#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include <vector>
#include "models/UndoModel.h"

class UndoManager
{
public:
    UndoManager() = default;
    ~UndoManager() = default;

    // ³·ÏúÕ»Á÷×ª
    void pushRecord(const UndoModel& record);
    bool canUndo() const;
    UndoModel popRecord();
    void clear();

private:
    std::vector<UndoModel> _records;
};

#endif // __UNDO_MANAGER_H__