#include <libspace/libspace.hpp>

namespace space {
Station::Station() {}

Station::~Station() {}

ErrorCode Station::AddModule(std::string name, float oxy_level)
{
    ErrorCode code = ErrorCode::kInvalidValue;
    if (oxy_level >= 0 && oxy_level <= 100) {
        code = ErrorCode::kSuccess;
        this->module_.push_back(SpaceModule(name, oxy_level));
    }
    return code;
}

std::string Station::GetInfo()
{
    std::string info = "";
    // если модулей нет
    if (this->module_.begin() == this->module_.end()) {
        info = "There are no modules at the station\n";
    } else {
        for (auto it = this->module_.begin(); it != this->module_.end(); ++it) {
            // получаем инфу от модулей
            info += it->GetInfo() + "\n";
        }
    }
    return info;
}

}  // namespace space