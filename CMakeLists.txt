project(webcar)
cmake_minimum_required(VERSION 2.8)


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries (${PROJECT_NAME} LINK_PUBLIC uWS z)


install (TARGETS webcar DESTINATION bin)

INSTALL(FILES webcar.init DESTINATION /etc/init.d/)

INSTALL(FILES virtualjoystick.js DESTINATION /var/www/localhost/html/)
INSTALL(FILES webcar.html DESTINATION /var/www/localhost/html/)
