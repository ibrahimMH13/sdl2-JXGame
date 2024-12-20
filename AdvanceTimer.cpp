#include <iostream>
#include <stdexcept>
#include "timer.h"



class AdvanceTimer: public ITimer {

    Uint32 mPausedTicks = 0 ;

    Uint32 mStartTicks = 0 ;

    bool mPaused = false ;

    bool mStarted = false ;

    void start() override {

        mStarted = true;
        mPaused = false;

        mStartTicks = SDL_GetTicks();

        mPaused = 0;
    }

    void stop() override {

        mStarted = false ;

        mPaused = false ;

        mStartTicks = 0 ;

        mPausedTicks = 0 ;
    }

    void pause() override {

        if (mStarted && !mPaused)
        {
            mPaused = true;

            mPausedTicks = SDL_GetTicks() - mStartTicks;

            mStartTicks = 0 ;
        }
        
    }

    void resume() override {

        mPaused = false;

        mStartTicks = SDL_GetTicks() - mPausedTicks;

        mPausedTicks = 0 ;
    }

   bool isStart() override {

        return mStarted;

   }

   bool isPause() override {

        return mPaused && mStarted;

   }

   Uint32 getTicks() override {

    Uint32 time = 0;

    if (mStarted)
    {
        if (mPaused)
        {
       
            time = mPausedTicks;
       
        }else{

            time = SDL_GetTicks() - mStartTicks;
        }
        
    }
    return time;
    
   }
};