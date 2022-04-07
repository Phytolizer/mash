cmake_minimum_required(VERSION 3.20)

project(
    "mash"
    LANGUAGES CXX
    VERSION "0.1.0"
    DESCRIPTION "Mash is a mash of many languages into one."
    HOMEPAGE_URL "https://github.com/Phytolizer/mash"
)

include("cmake/CPM.cmake")

find_package("ICU" REQUIRED COMPONENTS "data" "io" "uc")

CPMAddPackage(
    NAME "magic_enum"
    GITHUB_REPOSITORY "Neargye/magic_enum"
    GIT_TAG "v0.7.3"
)

add_subdirectory("mash")
add_subdirectory("mashc")
