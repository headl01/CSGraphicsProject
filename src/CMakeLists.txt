add_library (cs4212-util
  ArgumentParsing.cpp ArgumentParsing.h
  handleGraphicsArgs.cpp handleGraphicsArgs.h
  model_obj.cpp model_obj.h
  Framebuffer.h Framebuffer.cpp
  vec3/vec3.h
  camera.h
  ray.h
  PerspectiveCamera.h
 "camera.cpp" "PerspectiveCamera.cpp" "sphere.h" "shape.h" "sphere.cpp")

target_compile_definitions(cs4212-util PUBLIC HAS_GLM)
target_link_libraries(cs4212-util PRIVATE Boost::program_options)
target_link_libraries(cs4212-util PUBLIC glm::glm)



add_executable(render
 render.cpp
 "camera.cpp" "PerspectiveCamera.cpp" "sphere.h" "shape.h" "sphere.cpp")
target_link_libraries(render PRIVATE cs4212-util)
target_link_libraries(render PRIVATE ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(render PRIVATE PNG::PNG)
target_link_libraries(render PRIVATE ZLIB::ZLIB)
