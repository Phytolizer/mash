add_executable("mashc" "source/main.cpp")
target_compile_features("mashc" PRIVATE "cxx_std_20")
target_link_libraries("mashc" PRIVATE "mash")
