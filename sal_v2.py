# coding:utf-8
# SIMPLE ASSEMBLY LANGUAGE V2
# FOR ARDUINO VM
# PYTHON 3.5
# winxos 2016-12-19
import glob
import sys

keywords = {"INPUT": 0x10, "PRINT": 0x11,
            "LOAD": 0x20, "STORE": 0x21, "SET": 0x22,
            "ADD": 0x30, "SUB": 31, "MUL": 32, "DIV": 0x33, "MOD": 0x34, "INC": 0x35, "DEC": 0x36, "NEG": 0x37,
            "JMP": 0x40, "JMPN": 0x41, "JMPZ": 0x42, "HALT": 0x43,
            "AND": 0x50, "OR": 0x51, "XOR": 0x52,
            "PUSH": 0x60, "POP": 0x61, "SREGA": 0x62, "SREGB": 0x63, "SREGC": 0x64, "SREGD": 0x65,
            "PMOD": 0x70, "DWP": 0x71, "DRP": 0x72, "AWP": 0x73, "ARP": 0x74,
            "SLP": 0x80
            };
var_table = {}
label_table = {}


def pretranslate(src_code):
    after_code = []
    for line in src_code:
        cmds = str(line).split()
        if len(cmds) > 0:
            if cmds[0] == "DIM":  # vars
                if len(cmds) == 2:
                    cmds.append("0")
                if len(cmds) > 2:
                    if cmds[1] in var_table:
                        print("[error] VAR %s ALREADY DEFINED." % cmds[1])
                        return
                    var_table[cmds[1]] = cmds[2]
            elif cmds[0].startswith("."):  # label
                if cmds[0] in label_table:
                    print("[error] LABEL %s ALREADY DEFINED." % cmds[0])
                    return
                label_table[cmds[0]] = len(after_code)
            elif cmds[0].startswith(";"):  # comment
                pass
            else:  # normal code
                after_code.append(cmds)

    for i, n in enumerate(var_table):
        after_code.append(var_table[n])
        var_table[n] = len(after_code) - 1
    return after_code


def translate(codes):
    ml = []
    for index, code in enumerate(codes):
        if index >= len(codes) - len(var_table):
            ml += (codes[-len(var_table):])
            break
        operator = keywords[code[0]]
        operand = 0
        if code[0] == "JMP" or code[0] == "JMPN" or code[0] == "JMPZ" or code[0] == "CALL":
            if len(code) > 1:
                label = "." + code[1]
                if label in label_table:
                    operand = label_table[label]
                else:
                    print("[error] LABEL %S NOT FOUND." % code[1])
                    return;
            else:
                print("[waring] LINE % MISS LABEL." % index)
        else:
            if len(code) > 1:
                if code[1] in var_table:
                    operand = var_table[code[1]]
                elif code[0] == "SET" or code[0] == "PMOD" or code[0] == "DWP" or code[0] == "DRP" \
                        or code[0] == "AWP" or code[0] == "ARP" or code[0] == "SLP":
                    operand = int(code[1])
                else:
                    print("[error] VAR %s NOT FOUND." % code[1])
                    return;
            else:
                if code[0] == "HALT" or code[0] == "PUSH" or code[0] == "POP" \
                        or code[0] == "SREGA" or code[0] == "SREGB" or code[0] == "SREGC" or code[0] == "SREGD":
                    pass
                else:
                    print("[waring] LINE % MISS OPERAND." % index)
        ml.append("%02x%02x" % (operator, operand))
    return ("\n").join(ml)


def deal_sal(n):
    fn = str(n).split(".")[0] + ".sml"
    try:
        with open(n) as fi, open(fn, "w") as fo:
            fo.write(translate(pretranslate(fi.read().split("\n"))))
            print("[success] ASSEMBLY FILE %s TO %s" % (n, fn))
    except IOError as e:
        print("[error] %s" % str(e))


def console():
    print("WELCOME TO SIMPLE ASSEMBLER v1")
    print("\t\twinxos 2016-11-15")
    print("\n")
    print("ls\t\t[list .sal assembly file]")
    print("as file\t\t[assembly .sal file to .sml file]")
    print("exit\t\t[exit program]")
    while True:
        cmd = str(input("SAL >"))
        cmds = cmd.split(" ")
        if cmds[0] == "ls":
            print("\n".join(glob.glob(r"*.sal")))
        if cmds[0] == "as":
            deal_sal(cmds[1])
        if cmds[0] == "exit":
            sys.exit()


if __name__ == "__main__":
    if len(sys.argv) > 1:
        deal_sal(sys.argv[1])
    else:
        console()
