#ifndef PRECOMPILED_HEADER_H
#define PRECOMPILED_HEADER_H

// precompiled header, add all external dependency header used in cpp files
// or this project's header which doesn't change often

#include <cmath>
#include <thread>
#include <atomic>
#include <memory>
#include <string>
#ifdef __linux__
#include <X11/Xlib.h>
#undef None
#undef Status
#endif

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/CircleShape.hpp>



// headers which do not change very often
#include "gamewindow.h"
#include "processes.h"
#include "utility.h"
#include "particlesystem/particle.h"




#endif
