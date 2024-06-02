include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
)

FetchContent_MakeAvailable(SFML)

target_link_libraries(${PROJECT_NAME} 
PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
)
