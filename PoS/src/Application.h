#pragma once
#include <gui/Application.h>
#include "MainWindow.h"
#include <dp/IDatabase.h>

class MyApp : public gui::Application
{
protected:

    gui::Window* createInitialWindow()
    {
        return new MainWindow;
    }
public:
    MyApp(int argc, const char** argv)
    : gui::Application(argc, argv)
    {
    }

    bool connectToDB()
    {

        dp::IDatabase* pDB = dp::create(dp::IDatabase::ConnType::CT_SQLITE, dp::IDatabase::ServerType::SER_SQLITE3);

        fo::fs::path home;
        mu::getHomePath(home);
        fo::fs::path DBPath = (home / "Work/CPProjects/Lab_GUI1/Database.db");

        if (!pDB->connect(DBPath.string().c_str()))
            return false;
       
        dp::setMainDatabase(pDB);
        return true;
    }
};
