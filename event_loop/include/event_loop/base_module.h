
namespace jas {
namespace loop {

class BaseModule
{
public:
    void start() {}
    inline void update() {}
    inline bool canTerminate() { return true;}
    inline void stop() {}
};

} // namespace loop
} // namespace jas
