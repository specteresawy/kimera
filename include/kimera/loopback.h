#ifndef LOOPBACK_H
#define LOOPBACK_H

#include "kimera/state.h"

#if	  defined(KIMERA_LINUX)
#include "kimera/loopback/linux.h"
#elif defined(KIMERA_MACOS)
#include "kimera/loopback/macos/loopback.h"
#elif defined(KIMERA_WINDOWS)
#include "kimera/loopback/windows.h"
#endif

#endif