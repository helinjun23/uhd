#!/usr/bin/python3
"""
Script for programming lmk05318 on the clocking aux board
"""
# pylint: disable=no-member

import time
import argparse
import re
from uhd.utils.mpmtools import MPMClient, MPM_RPC_PORT, InitMode

DESCRIPTION_TEST = '''reads LMK register file generated by TICS Pro and writes via mpm_shell
                      the commands on the USRP given by the --host parameter.'''
parser = argparse.ArgumentParser(epilog=DESCRIPTION_TEST,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument('reg_file', help='LMK register config file')
parser.add_argument('--host', default="localhost",
                    help='USRP host to be programmed, usrp-hwd must run there')
parser.add_argument('-p', '--program_to_eeprom', action='store_true',
                    help='write config to eeprom, be careful, only 100 write-cycles are supported')
parser.add_argument('-v', '--verify_eeprom', action='store_true',
                    help='read config from eeprom and compares it to given reg_file')

args = parser.parse_args()

def parse_reg_file(file):
    """
    Parse the register values from the provided register config file
    """
    regfile_regex = re.compile(r"^R(\d*)\t(0x[0-9A-F]*)")
    reg_dict = {}
    for line in open(file, 'r').readlines():
        if regfile_regex.match(line):
            [reg_str, reg_val] = line.strip().split('\t')
            reg_val = reg_val.split('0x')[1]
            reg_addr = reg_val[:4]
            reg_data = reg_val[4:]
            reg_dict[reg_str] = (hex(int(reg_addr, base=16)), hex(int(reg_data, base=16)))
    return reg_dict

mpm_c = MPMClient(InitMode.Claim, "localhost", MPM_RPC_PORT)

# read the register file containing the actual values to be programmed
print("read register values from {}".format(args.reg_file))
prog_regs = parse_reg_file(args.reg_file)

print("start programming the LMK registers")
mpm_c.clkaux_set_nsync_lmk_power_en(1)
mpm_c.clkaux_set_nsync_tcxo_en(1)
if not mpm_c.clkaux_get_nsync_chip_id_valid():
    raise RuntimeError("chip ID of LMK is not valid, skip programming")
print('EEPROM has been programmed {} times'.format(
       mpm_c.clkaux_get_nsync_lmk_eeprom_prog_cycles()))

# now write the commands to program the LMK
for reg in prog_regs:
    mpm_c.poke_clkaux(int(prog_regs[reg][0], 16), int(prog_regs[reg][1], 16))
    val = mpm_c.peek_clkaux(int(prog_regs[reg][0], 16)).lower()
    if prog_regs[reg][1] != val:
        print("warning, reg values are not as programmed: addr: {}, prog: {},  read: {}"
              .format(prog_regs[reg][0], prog_regs[reg][1], val))

if args.program_to_eeprom:
    print("programming register values into EEPROM")
    print('EEPROM has been programmed {} times'.format(
           mpm_c.clkaux_get_nsync_lmk_eeprom_prog_cycles()))
    mpm_c.clkaux_write_nsync_lmk_cfg_regs_to_eeprom("register_commit")
    mpm_c.clkaux_set_nsync_soft_reset(True)
    mpm_c.clkaux_set_nsync_soft_reset(False)
    mpm_c.clkaux_set_nsync_lmk_power_en(0)
    print("programming of LMK done, chip is powered down")

if args.verify_eeprom:
    time.sleep(1)
    VERIFY_OK = True
    print("start verification of EEPROM, powering chip up")
    mpm_c.clkaux_set_nsync_lmk_power_en(1)
    mpm_c.clkaux_set_nsync_tcxo_en(1)
    if not mpm_c.clkaux_get_nsync_chip_id_valid():
        raise RuntimeError("chip ID of LMK is not valid, skip verifying")
    for reg in prog_regs:
        val = mpm_c.peek_clkaux(int(prog_regs[reg][0], 16)).lower()
        if str(prog_regs[reg][1]) != val:
            VERIFY_OK = False
            print("warning, reg values are not as programmed: addr: {}, prog: {},  read: {}"
                  .format(prog_regs[reg][0], prog_regs[reg][1], val))
    if VERIFY_OK:
        print("SUCCESS: read back values are equal to programmed values")
    else:
        print("ERROR: EEPROM verification failed!")
