#include <iostream>
#include <sstream>

#include "Application/VisualExpressions.hpp"
#include "Logger/Logger.hpp"
#include "ArgParser/ArgumentParser.hpp"


int main(int argc, char* argv[]){

    ArgumentParser arguments(argc,argv);

    if(arguments.getParamValue("debug","false") == "false")
        Logger::disable();

    auto app = Gtk::Application::create("id.perret.expressions");

    argc = 1;
    app->make_window_and_run<VisualExpressions>(argc,argv);

    return 0;
}
