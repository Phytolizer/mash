add_library("mash" INTERFACE)
target_include_directories("mash" INTERFACE "include")
target_link_libraries(
    "mash" INTERFACE "ICU::data" "ICU::io" "ICU::uc" "magic_enum::magic_enum"
)
