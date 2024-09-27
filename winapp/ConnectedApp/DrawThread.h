#pragma once
#include "CommonObject.h"

/**
 * @class DrawThread
 * @brief Class representing the thread responsible for the graphical user interface.
 */
class DrawThread
{
public:
    /**
     * @brief Operator function to run the draw thread.
     * @param common Reference to the common objects shared between threads.
     */
    void operator()(CommonObjects& common);
};
