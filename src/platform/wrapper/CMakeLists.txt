cmake_minimum_required(VERSION 3.15)

if(WIN32)
    set(PLATFORM_SRC win32/platform_win32.cpp)
elseif(APPLE)
    set(PLATFORM_SRC macos/platform_macos.mm)
endif(WIN32)


add_library(GPlatformWrapper SHARED graphics_wrapper.cpp
                                    ${PLATFORM_SRC})

target_include_directories(GPlatformWrapper PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(GPlatformWrapper PRIVATE G_EXPORT_WRAPPER)

if(APPLE)
find_library(APPKIT_LIBRARY AppKit REQUIRED)
target_link_libraries(GPlatformWrapper ${APPKIT_LIBRARY})
endif()