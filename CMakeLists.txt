cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("calc")

add_executable (calc "calc.cpp"  "Calculator.cpp" "Calculator.h" "DllReader.h" "DllReader.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET calc PROPERTY CXX_STANDARD 20)
endif()

add_library(funcsin SHARED ./plugins/funcsin.cpp "plugins/funcsin.cpp" "DllReader.cpp" "DllReader.h")
add_library(funccos SHARED ./plugins/funccos.cpp "plugins/funccos.cpp" "DllReader.cpp" "DllReader.h")
add_library(functan SHARED ./plugins/functan.cpp "plugins/functan.cpp" "DllReader.cpp" "DllReader.h")
add_library(funcln SHARED ./plugins/funcln.cpp "plugins/funcln.cpp" "DllReader.cpp" "DllReader.h")
add_library(funclog SHARED ./plugins/funclog.cpp "plugins/funclog.cpp" "DllReader.cpp" "DllReader.h")
add_library(funcasin SHARED ./plugins/funcasin.cpp "plugins/funcasin.cpp" "DllReader.cpp" "DllReader.h")

target_link_libraries(calc funcsin funccos functan funcln funclog funcasin)
