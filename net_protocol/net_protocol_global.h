#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NET_PROTOCOL_LIB)
#  define NET_PROTOCOL_EXPORT Q_DECL_EXPORT
# else
#  define NET_PROTOCOL_EXPORT Q_DECL_IMPORT
# endif
#else
# define NET_PROTOCOL_EXPORT
#endif
