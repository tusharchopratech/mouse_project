#ifndef MouseFunction_RealTime_Play_CPP
#define MouseFunction_RealTime_Play_CPP

#include "MouseFunctions.hpp"

void MouseFunctions::fireMouseEvent(char mouseButton, char mouseEvent)
{
    if (mouseButton == 'l')
    {
        if (mouseEvent == 'd')
        {

            if (isRealTimeRunning)
            {

                if (getLeftMouseStatus() == 0 && isLeftClickFiringAvaiable == true && (gb_getCurrentTimeInMillisecondsDouble() - lastLeftClickTimeStamp) > refractoryPeriodMs)
                // if (getLeftMouseStatus() == 0 && isLeftClickFiringAvaiable == true)
                {
                    // mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    impulseLeftClicksTimeStamps.push_back(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
                    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
                    {
                        cout << "IP Left Down Click at " << gb_getCurrentTimeInMilliseconds() << endl;
                    }
                    isLeftClickFiringAvaiable = false;
                    std::thread newThread(&MouseFunctions::unblockLeftClickFiring, this);
                    newThread.detach();
                }
            }
        }
        else if (mouseEvent == 'u')
        {
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
    }
    else if (mouseButton == 'r')
    {
        if (mouseEvent == 'd')
        {
            if (isRealTimeRunning)
            {
                if (getRightMouseStatus() == 0 && isRightClickFiringAvaiable == true && (gb_getCurrentTimeInMillisecondsDouble() - lastRightClickTimeStamp) > refractoryPeriodMs)
                {
                    // mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                    impulseRightClicksTimeStamps.push_back(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
                    if (gb_getCurrentEnvirnoment() == GB_ENV_DEVELOPMENT || gb_getCurrentEnvirnoment() == GB_ENV_STAGING)
                    {
                        cout << "IP Right Down Click at " << gb_getCurrentTimeInMilliseconds() << endl;
                    }
                    isRightClickFiringAvaiable = false;
                    std::thread newThread(&MouseFunctions::unblockRightClickFiring, this);
                    newThread.detach();
                }
            }
        }
        else if (mouseEvent == 'u')
        {
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
    }
}

void MouseFunctions::startRealTimePlay()
{
    osLeftClicksTimeStamps.clear();
    osRightClicksTimeStamps.clear();
    impulseLeftClicksTimeStamps.clear();
    impulseRightClicksTimeStamps.clear();
    lastLeftClickTimeStamp = 0.0;
    lastRightClickTimeStamp = 0.0;
    isRealTimeRunning = true;
}

void MouseFunctions::stopRealTimePlay()
{
    isRealTimeRunning = false;
}

void MouseFunctions::unblockLeftClickFiring()
{
    double currentTime = gb_getCurrentTimeInMillisecondsDouble();
    while (gb_getCurrentTimeInMillisecondsDouble() - currentTime < restPeriodMs)
    {
    }
    isLeftClickFiringAvaiable = true;
}

void MouseFunctions::unblockRightClickFiring()
{
    double currentTime = gb_getCurrentTimeInMillisecondsDouble();
    while (gb_getCurrentTimeInMillisecondsDouble() - currentTime < restPeriodMs)
    {
    }
    isRightClickFiringAvaiable = true;
}

// std::vector<double> MouseFunctions::getOSLeftClickTimestamps()
// {
//     return osLeftClicksTimeStamps;
// }

// std::vector<double> MouseFunctions::getOSRightClickTimestamps()
// {
//     return osRightClicksTimeStamps;
// }

// std::vector<double> MouseFunctions::getImpulseLeftClickTimestamps()
// {
//     return impulseLeftClicksTimeStamps;
// }

// std::vector<double> MouseFunctions::getImpulseRightClickTimestamps()
// {
//     return impulseRightClicksTimeStamps;
// }

#endif