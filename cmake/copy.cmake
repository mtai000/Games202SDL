macro(CopyDLL target_name file_name)
    set(dll_path $ENV{VCPKG_ROOT}/installed/x64-windows/bin/${file_name})
    set(target_path $<TARGET_FILE_DIR:${target_name}>/${file_name})
    add_custom_command(TARGET ${target_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${dll_path} ${target_path})
endmacro(CopyDLL)

macro(CopyAssets target_name folder)
    add_custom_command(TARGET ${target_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E remove_directory 
            $<TARGET_FILE_DIR:${target_name}>/${folder})
    add_custom_command(TARGET ${target_name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_SOURCE_DIR}/${folder} $<TARGET_FILE_DIR:${target_name}>/${folder})
endmacro(CopyAssets)