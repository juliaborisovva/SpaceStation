#include <libspace/libspace.hpp>

namespace space {

SpaceModule::SpaceModule(std::string name, float oxy_level) : name_(name)
{
    if (oxy_level >= 0 && oxy_level <= 100) {
        this->oxygen_level_ = oxy_level;
    } else {
        this->oxygen_level_ = 100.0;
    }
}

SpaceModule::~SpaceModule() {}

std::string SpaceModule::GetInfo()
{
    return "SpaceModuleName: " + this->name_ +
           ", OxygenLevel: " + std::to_string(this->oxygen_level_);
}

ErrorCode SpaceModule::SetOxygen(float oxy_level)
{
    ErrorCode code = ErrorCode::kInvalidValue;
    if (oxy_level >= 0 && oxy_level <= 100) {
        code = ErrorCode::kSuccess;
        this->oxygen_level_ = oxy_level;
    }
    return code;
}

}  // namespace space