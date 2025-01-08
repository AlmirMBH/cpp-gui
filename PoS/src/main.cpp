#include "Application.h"
#include <td/StringConverter.h>
#include <gui/WinMain.h>



int main(int argc, const char * argv[])
{

    MyApp app(argc, argv);
    app.init("EN"); 

    if(!app.connectToDB())
    {
        mu::setLogLevel(1000);
        mu::logError("ERROR", "Put database at: %HOME%/Work/CPProjects/Lab_GUI1/Database.db\n");
        return 1;
    }

    return app.run();
}