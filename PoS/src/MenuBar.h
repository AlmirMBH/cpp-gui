#pragma once
#include <gui/MenuBar.h>

class MenuBar : public gui::MenuBar
{
private:
    gui::SubMenu menuApp;

protected:
    void populateMenuApp()
    {
        auto& items = menuApp.getItems();
        items[0].initAsQuitAppActionItem(tr("Quit"), "q");
        items[1].initAsActionItem(tr("Items"), 10);
        items[2].initAsActionItem(tr("OutDocs"), 20);
    }

public:
    MenuBar()
    : gui::MenuBar(1) 
    , menuApp(10, tr("App"), 3) 
    {
        populateMenuApp();
        _menus[0] = &menuApp;
    }
    
    ~MenuBar()
    {
    }
};
