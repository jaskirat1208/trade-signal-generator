namespace jas {
namespace strategy {

/**
 * @brief Construct a new SMAStrategy::SMAStrategy object
 * 
 */
template<class BASE>
SMAStrategyModule<BASE>::SMAStrategyModule() : BASE() {}

/**
 * @brief 
 * 
 */
template<class BASE>
void SMAStrategyModule<BASE>::start() {
    BASE::start();
    BASE::registerSubscriber(platform::EVENT_TYPE::FEED, std::make_shared<SMAStrategy>(strategy));
}


template<class BASE>
void SMAStrategyModule<BASE>::update() {
    BASE::update();
}
/**
 * @brief 
 * 
 */
template<class BASE>
void SMAStrategyModule<BASE>::stop() {
    BASE::stop();
}

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
template<class BASE>
bool SMAStrategyModule<BASE>::canTerminate() {
    return BASE::canTerminate();
}

} // namespace platform
} // namespace jas
