# Get all cpp-files in the current directory
file(GLOB time_check RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


foreach(time_check_filename ${time_check})
  # Get file name without extension
  get_filename_component(time_check ${time_check_filename} NAME_WE)

  # Add and configure executable file to be produced
  add_executable(${time_check} ${time_check_filename})
  target_link_libraries(${time_check} ${MP2_LIBRARY})
  set_target_properties(${time_check} PROPERTIES
    OUTPUT_NAME "${time_check}"
    PROJECT_LABEL "${time_check}"
    RUNTIME_OUTPUT_DIRECTORY "../")
endforeach()
