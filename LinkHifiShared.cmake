MACRO(LINK_HIFI_SHARED_LIBRARY TARGET)
    if (NOT TARGET HifiShared)
        add_subdirectory(../shared ../shared)
    endif (NOT TARGET HifiShared)
    
    include_directories(../shared/src)
    get_directory_property(HIFI_SHARED_LIBRARY DIRECTORY ../shared DEFINITION HIFI_SHARED_LIBRARY)
    add_dependencies(${TARGET} ${HIFI_SHARED_LIBRARY})
    target_link_libraries(${TARGET} ${HIFI_SHARED_LIBRARY})
    
    if (APPLE)
      # link in required OS X framework
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework CoreServices")
    endif (APPLE)
ENDMACRO(LINK_HIFI_SHARED_LIBRARY _target)