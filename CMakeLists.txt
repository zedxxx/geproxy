cmake_minimum_required(VERSION 3.11)

project(geproxy LANGUAGES C)

set(SOURCE_FILES src/main.c src/config.c src/winhttp_wrapper.c src/wininet_wrapper.c)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

if(MSVC)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /DEF:src\\geproxy.def")
else()    
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--kill-at -Wl,--enable-stdcall-fixup src/geproxy.def")
endif()

target_link_libraries(${PROJECT_NAME} winhttp wininet)
