#!/usr/bin/env ruby

# save some typing
def sin angle
  Math.sin(angle)
end

ENC_RES        = 16384
NUM_POLE_PAIRS =    11
LOOKUP_TABLE_LEN = ENC_RES / NUM_POLE_PAIRS

tf = File.new('tables.txt','w')

File.open('tables.c','w') do |f|
  om = 1.0 #/ 0.86603; # overmodulation factor
  a3 = 0 #1.0 / 6.0; # 3rd order harmonic injection scalar
  f.puts <<EOHEADER1
#include <stdint.h>
#include "tables.h"

// AUTO-GENERATED. EDITS WILL BE LOST!

const float g_tables_motor_modulation[TABLE_LEN] =
{
EOHEADER1
  LOOKUP_TABLE_LEN.times do |i|
    th = i * 2 * 3.14159 / LOOKUP_TABLE_LEN
    s = om * (sin(th) + a3*sin(3*th))
    f.puts "  #{s}f,  // #{i} = #{th}"
    tf.puts s
  end
  f.puts <<EOHEADER2
};

const float g_tables_sine[TABLE_LEN] =
{
EOHEADER2
  LOOKUP_TABLE_LEN.times do |i|
    th = i * 2 * 3.14159 / LOOKUP_TABLE_LEN
    s = sin(th)
    f.puts "  #{s}f,  // #{i} = #{th}"
  end
  f.puts "};"
end

