#pragma once
#include <gui/VerticalNavigator.h>
#include "SwitcherView.h"
#include "../../common_files/include/DialogsLib.h"

class DIALOGS_LIB_API NavigatorView : public gui::View
{
private:
protected:
    gui::HorizontalLayout _hl;
    gui::VerticalNavigator _navigator;
    gui::Image _imgItems;
    gui::Image _imgDoc;
    SwitcherView _switcherView;
public:
    NavigatorView()
        : _hl(2)
        , _navigator(2)
        , _imgItems(":imgItem")
        , _imgDoc(":imgDoc")
    {
        setMargins(0, 0, 0, 0);
        _navigator.setItem(0, &_imgItems, tr("Items"));
        _navigator.setItem(1, &_imgDoc, tr("OutDocs"));
        _hl.append(_navigator);
        _hl.append(_switcherView);
        setLayout(&_hl);
    }
    void setNavigatorSelection(td::UINT2 sel)
    {
        _navigator.setCurrentSelection(sel);
        _switcherView.showView((int)sel);

    }

protected:

    virtual bool onChangedSelection(gui::Navigator* pNav)
    {
        td::UINT2 currSelection = pNav->getCurrentSelection();
        _switcherView.showView((int)currSelection);
        return true;
    }

};
