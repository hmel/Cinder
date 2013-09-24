include_directories(../../include/)
  
add_executable(windowTestApp
  src/windowTestApp.cpp)

target_link_libraries(windowTestApp cinder GL boost_system boost_filesystem png12 curl)

set_target_properties(windowTestApp PROPERTIES
  COMPILE_FLAGS -std=c++11)