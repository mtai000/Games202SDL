macro(CopyShaders target_name)
    message("src:" ${PROJECT_SOURCE_DIR})
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${target_name}>/shaders)
endmacro(CopyShaders)

macro(CopyAssets target_name)
    message("src:" ${PROJECT_SOURCE_DIR})
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${target_name}>/assets)
endmacro(CopyAssets)

macro(CopyDLL target_name)
if(NOT EXISTS $<TARGET_FILE_DIR:${target_name}>)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${LOCAL_3RDPARTY}/SDL2/lib/x64/SDL2.dll $<TARGET_FILE_DIR:${target_name}>
        COMMAND ${CMAKE_COMMAND} -E copy ${LOCAL_3RDPARTY}/glew/bin/Release/x64/glew32.dll $<TARGET_FILE_DIR:${target_name}>)
endif()
endmacro(CopyDLL)