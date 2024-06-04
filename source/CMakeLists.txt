add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	Application.cpp Application.hpp
	Shape.cpp Shape.hpp
	InputHandler.cpp InputHandler.hpp
	Scene.cpp Scene.hpp
)
