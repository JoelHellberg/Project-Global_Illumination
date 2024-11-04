#define WIN32_LEAN_AND_MEAN // Exclude rarely-used services from windows.h
#define NOGDI               // Exclude graphics types like RECT
#define NOMINMAX            // Prevents min/max macros
#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>

namespace CpuManagement {

    double GetCurrentCpuUsage() {
        FILETIME idleTime, kernelTime, userTime;
        GetSystemTimes(&idleTime, &kernelTime, &userTime);

        static ULARGE_INTEGER previousIdleTime, previousKernelTime, previousUserTime;
        ULARGE_INTEGER currentIdleTime = *reinterpret_cast<ULARGE_INTEGER*>(&idleTime);
        ULARGE_INTEGER currentKernelTime = *reinterpret_cast<ULARGE_INTEGER*>(&kernelTime);
        ULARGE_INTEGER currentUserTime = *reinterpret_cast<ULARGE_INTEGER*>(&userTime);

        ULARGE_INTEGER idleDiff = { currentIdleTime.QuadPart - previousIdleTime.QuadPart };
        ULARGE_INTEGER totalDiff = { currentKernelTime.QuadPart + currentUserTime.QuadPart -
                                    previousKernelTime.QuadPart - previousUserTime.QuadPart };

        previousIdleTime = currentIdleTime;
        previousKernelTime = currentKernelTime;
        previousUserTime = currentUserTime;

        return totalDiff.QuadPart > 0 ? (1.0 - (double)idleDiff.QuadPart / (double)totalDiff.QuadPart) * 100.0 : 0.0;
    }

    void WaitForCpuBelowThreshold(double threshold = 80.0) {
        while (true) {
            double cpuUsage = GetCurrentCpuUsage();
            if (cpuUsage < threshold) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Check every 100 ms
        }
    }

}
