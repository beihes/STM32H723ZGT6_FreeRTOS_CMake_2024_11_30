# THIS FILE IS AUTO GENERATED FROM THE TEMPLATE! DO NOT CHANGE!
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.20)

# specify cross compilers and tools
set(TOOLPATH "D:/ToolPath/Arm-None-Eabi-Gcc/Base_File/10 2021.10/bin/arm-none-eabi-")

# set(TOOLPATH "E:/ToolPath/ArmNoneEabiGcc/Base_File/13.3 rel1/bin/arm-none-eabi-")

# 环境选择
if(WIN32)
    MESSAGE(STATUS "Now is windows!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++.exe)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc.exe)
    set(CMAKE_AR ${TOOLPATH}ar.exe)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy.exe)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump.exe)
    set(SIZE ${TOOLPATH}size.exe)
elseif(UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS!")
    set(CMAKE_C_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}g++)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}gcc)
    set(CMAKE_AR ${TOOLPATH}ar)
    set(CMAKE_OBJCOPY ${TOOLPATH}objcopy)
    set(CMAKE_OBJDUMP ${TOOLPATH}objdump)
    set(SIZE ${TOOLPATH}size)
else()
    MESSAGE(STATUS "Unsupported system!")
endif()

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project(STM32H723ZGT6_CMake_2024_11_30 C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Uncomment for hardware floating point
add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING;USE_FULL_LL_DRIVER)
add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

# Uncomment for software floating point
# add_compile_options(-mfloat-abi=soft)
add_compile_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

# uncomment to mitigate c++17 absolute addresses warnings
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

# Enable assembler files preprocessing
add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(VERBOSE "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(VERBOSE "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(VERBOSE "Maximum optimization for size")
    add_compile_options(-Os)
else()
    message(VERBOSE "Minimal optimization, debug info included")
    add_compile_options(-Og -g)
endif()

add_compile_options(-Wall)

# 库文件
include_directories(
    ./App
    ./App/FreeRTOS
    ./App/Led
    ./CMyLib
    ./CMyLib/Define
    ./CMyLib/Dts
    ./CMyLib/Inc
    ./CMyLib/Usart
    ./System
    ./System/CMSIS/Include
    ./System/FreeRTOS/CMSIS_RTOS_V2
    ./System/FreeRTOS/include
    ./System/FreeRTOS/portable/GCC/ARM_CM4F
    ./System/STM32H7xx/Include
    ./System/STM32H7xx_HAL_Driver/Inc
    ./System/STM32H7xx_HAL_Driver/Inc/Legacy
    ./User/Inc)

add_definitions(-DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx)

# 源文件
file(GLOB_RECURSE SOURCES
    "App/FreeRTOS/*.c"
    "App/Led/*.c"
    "CMyLib/Define/*.c"
    "CMyLib/Dts/*.c"
    "CMyLib/Src/stm32h7xx_hal_msp.c"
    "CMyLib/Src/sysmem.c"
    "CMyLib/Src/syscalls.c"
    "CMyLib/Usart/*.c"

    # tim三选一
    # "CMyLib/Src/TimeBase/stm32h7xx_hal_timebase_alarm.c"
    # "CMyLib/Src/TimeBase/stm32h7xx_hal_timebase_wakeup.c"
    "CMyLib/Src/TimeBase/stm32h7xx_hal_timebase_tim.c"

    "System/*.c"
    "System/Startup/*.s"
    "System/STM32H7xx_HAL_Driver/Src/*.c"
    "System/STM32H7xx_HAL_Driver/Src/Legacy/*.c"
    "User/Src/*.c"
)

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/Ld/STM32H723ZGTX_FLASH.ld

    # ${CMAKE_SOURCE_DIR}/STM32H7xx/Source/STM32H723ZGTX_RAM.ld
)

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m7 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})

add_link_options(-specs=nano.specs -specs=nosys.specs -u _printf_float)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")