#include "MainWindow.h"

MainWindow::MainWindow()
    : gui::Window(gui::Geometry(0, 0, 1000, 500))
{
    setTitle(tr("appTitle"));
    _mainMenuBar.setAsMain(this);
    setToolBar(_toolBar);
    setCentralView(&_view);

}

bool MainWindow::onActionItem(gui::ActionItemDescriptor& aiDesc)
{
    auto [menuID, firstSubMenuID, lastSubMenuID, actionID] = aiDesc.getIDs();

    //only one menu now
    if (menuID == 10 && firstSubMenuID == 0 && lastSubMenuID == 0)
    {
        if (actionID == 10)
            _view.setNavigatorSelection(0);
        else if (actionID == 20)
            _view.setNavigatorSelection(1);
    }

    return true;
}
