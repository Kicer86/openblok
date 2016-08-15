#include "system/EventCollector.h"
#include "system/GraphicsContext.h"
#include "system/Log.h"

#include <memory>


class App {
public:
    bool init();

    std::unique_ptr<GraphicsContext> gcx;
    std::unique_ptr<EventCollector> events;
};

bool App::init()
{
    const std::string log_tag = "init";
    try {
        Log::info(log_tag) << "Initializing video...\n";
        gcx = GraphicsContext::create();

        Log::info(log_tag) << "Initializing event system...\n";
        events = EventCollector::create();
    }
    catch (const std::exception& err) {
        Log::error(log_tag) << err.what() << std::endl;
        return false;
    }

    return true;
}


int main(int argc, char const *argv[])
{
    Log::info("main") << "OpenBlok v0.0.0 by Mátyás Mustoha\n";
    App app;
    if (!app.init())
        return 1;

    while (!app.events->quit_requested()) {
        auto events = app.events->collect();

        app.gcx->render();
    }

    return 0;
}
