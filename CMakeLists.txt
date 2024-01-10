cmake_minimum_required(VERSION 3.16)

project(rpcdb C CXX)

set(CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

add_compile_options(-O3)

set(rpc_dir /usr/include/tirpc)
set(client_dir ${CMAKE_SOURCE_DIR}/client)
set(server_dir ${CMAKE_SOURCE_DIR}/server)
set(status_dir ${CMAKE_SOURCE_DIR}/status_codes)

set(client_subdirs
  ${client_dir}
  ${client_dir}/command
  ${client_dir}/input_controller
  ${client_dir}/request
  ${client_dir}/response
  ${client_dir}/rpc
  )

set(server_subdirs
  ${server_dir}
  ${server_dir}/command
  ${server_dir}/request
  ${server_dir}/response
  )

include_directories(${rpc_dir} ${status_dir})

file(GLOB_RECURSE client_cpp_sources ${client_dir}/*.cpp ${client_dir}/*.c ${status_dir}/*.cpp)
file(GLOB_RECURSE server_cpp_sources ${server_dir}/*.cpp ${server_dir}/*.c ${status_dir}/*.cpp)

add_custom_target(rpc
  COMMAND cp ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME}.x ${CMAKE_PROJECT_NAME}.x
  COMMAND rpcgen -C ${CMAKE_PROJECT_NAME}.x

  COMMAND cp ${CMAKE_PROJECT_NAME}.h ${client_dir}/
  COMMAND cp ${CMAKE_PROJECT_NAME}_xdr.c ${client_dir}/
  COMMAND mv ${CMAKE_PROJECT_NAME}_clnt.c ${client_dir}/

  COMMAND mv ${CMAKE_PROJECT_NAME}.h ${server_dir}/
  COMMAND mv ${CMAKE_PROJECT_NAME}_xdr.c ${server_dir}/
  COMMAND rm ${CMAKE_PROJECT_NAME}_svc.c
)

add_custom_command(TARGET rpc PRE_BUILD
  COMMAND cp compile_commands.json ../)

add_executable(client ${client_cpp_sources})
# add_dependencies(client rpc)
target_link_libraries(client nsl tirpc)
target_include_directories(client PUBLIC ${client_subdirs})


add_executable(server ${server_cpp_sources})
# add_dependencies(server rpc)
target_link_libraries(server nsl tirpc)
target_include_directories(server PUBLIC ${server_subdirs})
