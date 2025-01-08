#pragma once
#include <gui/ToolBar.h>
#include <gui/Image.h>
#include <gui/Symbol.h>

class ToolBar : public gui::ToolBar
{
protected:
    gui::Image _imgItems;
    gui::Image _imgDoc;
public:
    ToolBar()
    : gui::ToolBar("mainTB", 2)
    , _imgItems(":imgItem")
    , _imgDoc(":imgDoc")
    {
        addItem(tr("Items"),     &_imgItems,     tr("ShowItems"),     10, 0, 0, 10);
        addItem(tr("OutDocs"),   &_imgDoc,       tr("ShowOutDocs"),   10, 0, 0, 20);

    }
};

