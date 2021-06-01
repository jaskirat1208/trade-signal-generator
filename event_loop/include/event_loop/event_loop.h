#pragma once
namespace jas
{
namespace loop
{

template<class Module>
class EventLoop : public Module
{
public:
    EventLoop();
    void loop();
};

template<class Module>
EventLoop<Module>::EventLoop() {}

/**
 * @brief Loop update function. Depends on the module this is being called
 * 
 * @tparam Module 
 */
template<class Module>
void EventLoop<Module>::loop() {
    Module::start();
    while(1) {
        if(Module::canTerminate())
            break;
        Module::update();
    }
    Module::stop();
}


} // namespace loop
} // namespace jas

