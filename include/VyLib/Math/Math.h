#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VyLib/Types/CoreTypes.h"

/**
 * 
 * https://openframeworks.cc/documentation/glm/
 */
namespace Vy
{

    template<SIZE_T T, SIZE_T Q>
    using Vec= glm::vec<T, Q>;
    
    
    using Vec2  = glm::vec2;
    using Vec3  = glm::vec3;
    using Vec4  = glm::vec4;
    
    using Vec2i = glm::ivec2;
    using Vec3i = glm::ivec3;
    using Vec4i = glm::ivec4;
    
    using Vec2d = glm::dvec2;
    using Vec3d = glm::dvec3;
    using Vec4d = glm::dvec4;

    using Vec2u = glm::uvec2;
    using Vec3u = glm::uvec3;
    using Vec4u = glm::uvec4;
    
    using Mat2  = glm::mat2;
    using Mat3  = glm::mat3;
    using Mat4  = glm::mat4;
    
    using Quat  = glm::quat;
    
    
    
}