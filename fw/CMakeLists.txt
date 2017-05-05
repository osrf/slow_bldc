set(CMAKE_TOOLCHAIN_FILE "stm32f3-toolchain.cmake")

cmake_minimum_required(VERSION 3.0.0)
project(slow_bldc)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting CMAKE_BUILD_TYPE to Debug explicitly")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# More linker flags in toolchain file.
set(CMAKE_EXE_LINKER_FLAGS "\
  ${CMAKE_EXE_LINKER_FLAGS} \
  -lc \
  -lgcc \
  -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/map,--cref \
  -T ${PROJECT_SOURCE_DIR}/common/stm32f303cx.ld \
")

function(slow_bldc_add_executable stem)
  add_executable(${stem}.elf ${ARGN})
  target_link_libraries(${stem}.elf common)
  add_custom_command(TARGET ${stem}.elf POST_BUILD
      COMMAND arm-none-eabi-objcopy -O binary ${stem}.elf ${stem}.bin
      COMMENT "creating ${stem}.bin")
  add_custom_command(TARGET ${stem}.elf POST_BUILD
      COMMAND arm-none-eabi-objdump -S -d ${stem}.elf > ${stem}.objdump
      COMMENT "disassembling ${stem}.elf")
  add_custom_target(${stem}.flash_swd
      DEPENDS ${stem}.elf
      COMMAND openocd -f interface/ftdi/olimex-arm-usb-tiny-h.cfg -f interface/ftdi/olimex-arm-jtag-swd.cfg -f target/stm32f3x.cfg -c "init; sleep 100; halt; sleep 100; flash write_image erase ${stem}.bin 0x08000000; verify_image ${stem}.bin 0x08000000; sleep 100; reset run; sleep 100; shutdown"
      VERBATIM)
  add_custom_target(${stem}.gdb_server
      COMMAND openocd ${openocd_preamble} -c "init; halt"
      VERBATIM)
  add_custom_target(${stem}.gdb
      DEPENDS ${stem}.elf
      COMMAND arm-none-eabi-gdb ${stem}.elf -x ${PROJECT_SOURCE_DIR}/common/gdb_init_commands
      VERBATIM)
endfunction()

include_directories(common)
include_directories(common/st)

add_subdirectory(common)
add_subdirectory(blink)
add_subdirectory(hello)
add_subdirectory(static_pwm)
add_subdirectory(enc_test)
add_subdirectory(rs485_rx_test)
add_subdirectory(rs485_tx_test)
add_subdirectory(voltage_mode_test)
