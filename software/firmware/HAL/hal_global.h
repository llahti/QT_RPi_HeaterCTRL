#ifndef HAL_GLOBAL_H
#define HAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HAL_LIBRARY)
#  define HALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HALSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HAL_GLOBAL_H
