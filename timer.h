#include <cstdint> 

#ifndef ITMER_H
#define ITMER_H

class ITimer
{

public:

    ~ITimer() = default;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void pause() = 0;

    virtual void resume() = 0;

    virtual Uint32 getTicks() = 0;

    virtual bool isStart() = 0;

    virtual bool isPause() = 0;
};

#endif