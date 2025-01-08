#pragma once
#include <gui/ViewSwitcher.h>
#include "ViewItem.h"
#include "ViewDoc.h"

class SwitcherView : public gui::ViewSwitcher
{
private:
protected:
    ViewItem _viewItem;
    ViewDoc _viewTransaction;

public:
    SwitcherView()
        : gui::ViewSwitcher(2)
        , _viewTransaction()
    {
        addView(&_viewItem, true);
        addView(&_viewTransaction);
    }
};
