"""
    t_vm (delclared in vm.h) is the main C structure for virtual machine.
    I use module "ctypes" to declare this structure in python,
    then pass it to C functions.
"""

from ctypes import *


MEM_SIZE = 4 * 1024
PROG_NAME_LENGTH = 128
COMMENT_LENGTH = 2048
CHAMP_MAX_SIZE = int(MEM_SIZE / 6)
MAX_PLAYERS = 4
REG_NUMBER = 16

# declare the c structure
class Bool(Structure):
    _fields_ = [("bool", c_int)]


class Cursor(Structure):
    pass


class Cursor(Structure):
    _fields_ = [
        ("regs", c_uint32 * (REG_NUMBER + 1)),
        ("live_counter", c_uint),
        ("c_id", c_uint),
        ("wait_cycle", c_int),
        ("no_live_cycle", c_int),
        ("pc", c_int16),
        ("op", c_uint8),
        ("carry", Bool),
        ("next", POINTER(Cursor)),
        ("prev", POINTER(Cursor)),
    ]


class Players(Structure):
    _fields_ = [
        ("prog_name", c_char * (PROG_NAME_LENGTH + 1)),
        ("comment", (c_char) * (COMMENT_LENGTH + 1)),
        ("prog_data", (c_uint8) * (CHAMP_MAX_SIZE)),
        ("file_size", c_uint),
        ("file", POINTER(c_uint8)),
        ("prog_size", c_int),
        ("live_counter", c_int),
        ("player_id", c_int8),
    ]


class VM(Structure):
    _fields_ = [
        ("players", Players * MAX_PLAYERS),
        ("arena", c_uint8 * MEM_SIZE),
        ("dump", c_int),
        ("player_nb", c_uint8),
        ("cycle_total", c_int),
        ("cycle_to_die", c_int),
        ("max_check_counter", c_int),
        ("delta_cycle_counter", c_int),
        ("live_counter", c_int),
        ("Cursor", POINTER(Cursor)),
        ("cursor_nb", c_int),
        ("winner", c_int),
        ("flags", c_char),
    ]
