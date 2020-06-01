#ifndef LOOPBACK_H
#define LOOPBACK_H

#ifdef __unix__
#include "kimera/loopback/linux/loopback.h"
#elif __APPLE__
#include "kimera/loopback/macos/loopback.h"
#endif

#endif