#ifndef LIBSPACE_HPP
#define LIBSPACE_HPP
#include <iostream>
#include <vector>

namespace space {

enum class ErrorCode { kSuccess = 0, kInvalidValue = -1 };

class SpaceModule
{
   private:
    std::string name_;
    float oxygen_level_;

   public:
    SpaceModule(std::string name = "SpaceModule", float oxy_level = 100.0);
    ~SpaceModule();
    std::string GetInfo();
    ErrorCode SetOxygen(float oxy_level);
};

class Station
{
   private:
    std::vector<SpaceModule> module_;

   public:
    Station();
    ~Station();
    ErrorCode AddModule(std::string name = "SpaceModule", float oxy_level = 100.0);
    std::string GetInfo();
};

}  // namespace space

#endif  // LIBSPACE_HPP
