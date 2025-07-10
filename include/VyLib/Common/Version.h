#pragma once

#include "VyLib/Types/CoreTypes.h"
#include "VyLib/Types/StringTypes.h"
#include "VyLib/Platform.h"

namespace Vy
{
    enum class VersionState : u8
    {
        EXPERIMENTAL,
        ALPHA,
        BETA,
        STABLE
    };

    struct VersionInfo
    {
        u16 major = 0;
        u16 minor = 0;
        u16 patch = 0;

        VersionState state = VersionState::EXPERIMENTAL;
    };


    class Version final
    {
    public:
        explicit Version(const VersionInfo& info) : 
            MAJOR(info.major), 
            MINOR(info.minor), 
            PATCH(info.patch), 
            STATE(info.state)
        {
        }

        VYNODISCARD VYINLINE u16 GetMajor()          const { return MAJOR; }
        VYNODISCARD VYINLINE u16 GetMinor()          const { return MINOR; }
        VYNODISCARD VYINLINE u16 GetPatch()          const { return PATCH; }
        VYNODISCARD VYINLINE VersionState GetState() const { return STATE; }

        VYNODISCARD VYINLINE String ToString() const { return std::to_string(MAJOR) + "." + std::to_string(MINOR) + "." + std::to_string(PATCH); }

        VYNODISCARD VYINLINE bool operator < (const Version& other) const { return MAJOR <  other.MAJOR || MINOR <  other.MINOR || PATCH <  other.PATCH; }
        VYNODISCARD VYINLINE bool operator > (const Version& other) const { return MAJOR >  other.MAJOR || MINOR >  other.MINOR || PATCH >  other.PATCH; }
        VYNODISCARD VYINLINE bool operator <=(const Version& other) const { return MAJOR <= other.MAJOR || MINOR <= other.MINOR || PATCH <= other.PATCH; }
        VYNODISCARD VYINLINE bool operator >=(const Version& other) const { return MAJOR >= other.MAJOR || MINOR >= other.MINOR || PATCH >= other.PATCH; }
		VYNODISCARD VYINLINE bool operator ==(const Version& other) const { return MAJOR == other.MAJOR && MINOR == other.MINOR && PATCH == other.PATCH; }
		VYNODISCARD VYINLINE bool operator !=(const Version& other) const { return !(*this == other); }

    private:
        const u16 MAJOR;
        const u16 MINOR;
        const u16 PATCH;
        const VersionState STATE;
    };
}