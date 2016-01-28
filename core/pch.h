#ifndef PRECOMPILED_HEADER_H
#define PRECOMPILED_HEADER_H

// precompiled header, add all external dependency header used in cpp files
// or this project's header which doesn't change often


#include <cmath>
#include <thread>
#include <atomic>
#include <memory>
#include <random>
#include <string>
#ifdef __linux__
#include <X11/Xlib.h>
#undef None
#undef Status
#endif

#include <SFML/Graphics.hpp>


// headers which does not change often
#include "Exceptions.h"


#endif
