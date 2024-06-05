add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

set(sources
	main.cpp
	Config.hpp
	Application.cpp Application.hpp
	Shape.cpp Shape.hpp
	InputHandler.cpp InputHandler.hpp
	Scene.cpp Scene.hpp
	Math.hpp Math.cpp
)

set(collision
	Collision/CollisionDetector.cpp Collision/CollisionDetector.hpp
	Collision/CollisionManager.cpp Collision/CollisionManager.hpp
)

source_group("Collision" FILES ${collision})

target_sources(${PROJECT_NAME}
PRIVATE
	${sources}
	${collision}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
