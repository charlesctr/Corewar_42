import sys
import subprocess
import ctypes
from pathlib import Path
from colorama import Fore

import c_struct


def get_vm_lib():
    # make dylib
    base_dir = Path(__file__).parent.parent.absolute()
    output = subprocess.run(["make", "dylib"])
    print('base_dir', base_dir)
    # open dylib to get all the C functions for vm
    lib_path = base_dir / "vm_lib.dylib"
    print('lib_path:',lib_path)
    vm_lib = ctypes.CDLL(str(lib_path))
    return vm_lib


vm_lib = get_vm_lib()


def user_input(stop, p_c_struct, vm_lib):
    u_input = input("-->")
    if u_input == "n":
        stop += 1
    elif u_input.isdigit() and int(u_input) > stop:
        stop = int(u_input)
    elif u_input == "q":
        raise SystemExit()
    else:
        print("usage:\n" "\tn: next_cycle\n" "\tnb : go to cycle ...\n" "\tq: quit\n")
        user_input(stop, p_c_struct, vm_lib)
    return stop


def print_mem(arena):
    for i in range(0, 4096):
        if i % 32 == 0:
            print(Fore.GREEN + "0x%04x : " % i, end="")
        if (arena[i]) != 0:
            print(Fore.RED + "%02x" % (arena[i]), end=" ")
        else:
            print(Fore.WHITE + "%02x" % (arena[i]), end=" ")
        if (i + 1) % 32 == 0:
            print()


class VM:
    """docstring for Vm"""

    def __init__(self):
        self.c_vm = c_struct.VM()
        self.p_c_vm = ctypes.pointer(self.c_vm)
        LP_c_char = ctypes.POINTER(ctypes.c_char)
        LP_LP_c_char = ctypes.POINTER(LP_c_char)
        vm_lib.init_vm(self.p_c_vm)
        argc = len(sys.argv)
        argv = (LP_c_char * (argc + 1))()
        for i, arg in enumerate(sys.argv):
            enc_arg = arg.encode("utf-8")
            argv[i] = ctypes.create_string_buffer(enc_arg)
        if vm_lib.parse(self.p_c_vm, argc, argv) and vm_lib.init_cursor_lst(
            self.p_c_vm
        ):
            vm_lib.player_to_arena(self.p_c_vm)

    def loop(self, stop=0):
        while self.c_vm.cursor_nb:
            while self.c_vm.delta_cycle_counter < self.c_vm.cycle_to_die:
                if self.c_vm.cycle_total >= stop:
                    print_mem(self.c_vm.arena)
                    print("cycle at: ", self.c_vm.cycle_total)
                    print("cycle_to_die:", self.c_vm.cycle_to_die)
                    print("processus_nb: ", self.c_vm.cursor_nb)
                    print("live_nb between check: ", self.c_vm.live_counter, "\n\n")
                    stop = user_input(stop, self.p_c_vm, vm_lib)

                if vm_lib.one_round(self.p_c_vm) == False:
                    return
            vm_lib.check(self.p_c_vm)
        vm_lib.declare_winner(self.p_c_vm)

    def __del__(self):
        vm_lib.free_vm(self.p_c_vm)


def main():
    if len(sys.argv) < 2:
        vm_lib.usage()
        raise SystemExit()
    vm = VM()
    vm.loop()


if __name__ == "__main__":
    main()
