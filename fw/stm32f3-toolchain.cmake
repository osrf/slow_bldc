set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_VERSION   1)
set(CMAKE_SYSTEM_PROCESSOR arm-eabi)

set(CMAKE_C_COMPILER       arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER     arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER     arm-none-eabi-as)
set(CMAKE_OBJCOPY          arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP          arm-none-eabi-objdump)

SET(CMAKE_C_FLAGS
  "-mthumb -mcpu=cortex-m3 -fno-builtin -Wall -std=gnu99 -fdata-sections -ffunction-sections"
  CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS
  "-mthumb -mcpu=cortex-m3 -fno-builtin -Wall  -fdata-sections -ffunction-sections"
  CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS
  "-mthumb -mcpu=cortex-m3"
  CACHE INTERNAL "asm compiler flags")

SET(CMAKE_EXE_LINKER_FLAGS
  "-mthumb -mcpu=cortex-m3 --specs=nosys.specs"
  CACHE INTERNAL "exe link flags")
