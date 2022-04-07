add_library("mash" "source/lexer.cpp")
target_include_directories("mash" PUBLIC "include")
target_compile_features("mash" PUBLIC "cxx_std_20")
target_link_libraries(
    "mash" PUBLIC "ICU::data" "ICU::io" "ICU::uc" "magic_enum::magic_enum"
)
