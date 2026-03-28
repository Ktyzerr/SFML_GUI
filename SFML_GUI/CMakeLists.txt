file(GLOB_RECURSE SFML_GUI_SOURCES src/*.cpp)
file(GLOB_RECURSE SFML_GUI_HEADERS include/*.h include/*.hpp)

add_library(SFML_GUI STATIC ${SFML_GUI_SOURCES} ${SFML_GUI_HEADERS})

target_include_directories(SFML_GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(SFML_GUI PUBLIC 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)