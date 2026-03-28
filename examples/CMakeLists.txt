add_executable(example_app main.cpp)

target_link_libraries(example_app PRIVATE SFML_GUI)

if(WIN32)
    add_custom_command(TARGET example_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:SFML::Graphics>"
        "$<TARGET_FILE:SFML::Window>"
        "$<TARGET_FILE:SFML::System>"
        "$<TARGET_FILE_DIR:example_app>"
        COMMAND_EXPAND_LISTS
    )
endif()