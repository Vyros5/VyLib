#pragma once

#include "VyLib/Platform.h"

#include "VyLib/Assert/Assert.h"

#include "VyLib/Log/Log.h"

/* Types */
#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Types/StringTypes.h"

/* Pointers */
#include "VyLib/Pointers/Ptrs.h"

#include "VyLib/Common/Common.h"
#include "VyLib/Common/Buffer.h"

#include "VyLib/Math/Math.h"

#include "VyLib/Containers/Span.h"
#include "VyLib/Containers/Array.h"
#include "VyLib/Containers/Vector.h"
#include "VyLib/Containers/Map.h"
#include "VyLib/Containers/Set.h"

#include "VyLib/Utils/ClassUtils.h"
#include "VyLib/Utils/EnumUtils.h"

#include "VyLib/Event/Event.h"

#include <iostream>


#define VY_DEBUG_MODE 1
#define VY_VK_LAYERS_ENABLED  1
#define VY_VK_LAYERS_GPU_ASSISTED 0
#define VY_VK_VERBOSE_CB_ENABLED 1
#define VY_VK_INFO_CB_ENABLED    1
#define VY_VK_WARN_CB_ENABLED    1
#define VY_VK_ERROR_CB_ENABLED   1
#define VY_VK_DEBUG_CB_ENABLED   1

#if VY_DEBUG_MODE
#   define assertMsg( condition, message ) \
    if( !(condition) ) { \
        std::cerr << "Assert:  " << (#condition) << std::endl; \
        std::cerr << "Message: " << message  << std::endl; \
        std::cerr << "File:    " << __FILE__ << std::endl; \
        std::cerr << "Line:    " << __LINE__ << std::endl << std::endl; \
    }
#else
#   define assertMsg( condition, message )
#endif // DEBUG

#define assertMsgReturnVoid( condition, message ) \
    assertMsg( condition, message )\
    if( !(condition) ) { \
        return;\
    }

#define assertMsgReturnValue( condition, message, return_value ) \
    assertMsg( condition, message )\
    if( !(condition) ) { \
        return return_value;\
    }