#include <gtest/gtest.h>

#include <libspace/libspace.hpp>

// создание модулей, два варианта конструкторов, true
TEST(SpaceModule, CreateModuleWithoutArgs)
{
    // модуль по умолчанию
    space::SpaceModule module;
    // проверка
    EXPECT_EQ(module.GetInfo(), "SpaceModuleName: SpaceModule, OxygenLevel: 100.000000");
}

TEST(SpaceModule, CreateModuleWithArgs)
{
    // модуль с параметрами
    space::SpaceModule module("Module", 43.5);
    // проверка
    EXPECT_EQ(module.GetInfo(), "SpaceModuleName: Module, OxygenLevel: 43.500000");
}

TEST(SpaceModule, CreateModuleWithArgsInvalid)
{
    // модуль с параметрами, default 100
    space::SpaceModule module("Module", 140);
    EXPECT_EQ(module.GetInfo(), "SpaceModuleName: Module, OxygenLevel: 100.000000");  //!
}

TEST(SpaceModule, GetInfo)
{
    space::SpaceModule module("SpaceModule", 25);
    // проверка
    EXPECT_EQ(module.GetInfo(), "SpaceModuleName: SpaceModule, OxygenLevel: 25.000000");
}

TEST(SpaceModule, SetOxygenValid)
{
    space::SpaceModule module;
    space::ErrorCode err = module.SetOxygen(54);
    // проверка
    EXPECT_EQ(err, space::ErrorCode::kSuccess);
    EXPECT_EQ(module.GetInfo(), "SpaceModuleName: SpaceModule, OxygenLevel: 54.000000");
}

TEST(SpaceModule, SetOxygenInvalid)
{
    space::SpaceModule module("SpaceModule", 54);
    space::ErrorCode err = module.SetOxygen(125);
    EXPECT_EQ(err, space::ErrorCode::kInvalidValue);
    EXPECT_EQ(module.GetInfo(), "SpaceModuleName: SpaceModule, OxygenLevel: 54.000000");
}

TEST(SpaceStation, CreateStation)
{
    space::Station station;
    EXPECT_EQ(station.GetInfo(), "There are no modules at the station\n");
}

TEST(SpaceStation, AddModuleWithoutArgs)
{
    space::Station station;
    space::ErrorCode err = station.AddModule();
    // проверка
    EXPECT_EQ(err, space::ErrorCode::kSuccess);
    EXPECT_EQ(station.GetInfo(), "SpaceModuleName: SpaceModule, OxygenLevel: 100.000000\n");
}

TEST(SpaceStation, AddModuleWithArgsValid)
{
    space::Station station;
    space::ErrorCode err = station.AddModule("SpaceModule", 66.3);
    // проверка
    EXPECT_EQ(err, space::ErrorCode::kSuccess);
    EXPECT_EQ(station.GetInfo(),
              "SpaceModuleName: SpaceModule, OxygenLevel: " + std::to_string((float)66.3) + "\n");
}

TEST(SpaceStation, AddModuleWithArgsInvalid)
{
    space::Station station;
    space::ErrorCode err = station.AddModule("SpaceModule", 133.3);
    // проверка
    EXPECT_EQ(err, space::ErrorCode::kInvalidValue);
    EXPECT_EQ(station.GetInfo(), "There are no modules at the station\n");
}

TEST(SpaceStation, GetInfoNoModules)
{
    space::Station station;
    // проверка
    EXPECT_EQ(station.GetInfo(), "There are no modules at the station\n");
}

TEST(SpaceStation, GetInfoWithModules)
{
    space::Station station;
    station.AddModule();
    // проверка
    EXPECT_EQ(station.GetInfo(), "SpaceModuleName: SpaceModule, OxygenLevel: 100.000000\n");
}