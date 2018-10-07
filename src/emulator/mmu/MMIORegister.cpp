#include "MMIORegister.hpp"
#include <type_traits>

namespace nsfgbe {

MMIOPermissions operator&(MMIOPermissions a, MMIOPermissions b) {
    return static_cast<MMIOPermissions> (
            static_cast<std::underlying_type<MMIOPermissions>::type>(a) &
            static_cast<std::underlying_type<MMIOPermissions>::type>(b)
    );
}

}
