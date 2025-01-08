#pragma once
#include <gui/Window.h>
#include "MenuBar.h"
#include "ToolBar.h"
#include "../../Dialogs/src/NavigatorView.h"

class MainWindow : public gui::Window
{
protected:
    MenuBar _mainMenuBar;
    ToolBar _toolBar;
    NavigatorView _view;
public:
    MainWindow();
    
protected:
    
    bool onActionItem(gui::ActionItemDescriptor& aiDesc) override;
    
};
