function(update_git_submodules)
    find_package(Git)
    message("${PROJECT_SOURCE_DIR}")
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        message("Try to update git submodules.")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/external"
            RESULT_VARIABLE UPDATE_SUBMODULE_RESULT
        )
        if (NOT ${GIT_SUBMODULE_RESULT} EQUAL 0)
            message(FATAL_ERROR "${GIT_EXECUTABLE}  submodule update --init --recursive failed with return code ${UPDATE_SUBMODULE_RESULT}.")
        endif()
    endif()
endfunction()