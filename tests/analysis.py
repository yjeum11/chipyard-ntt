#!/usr/bin/env python3

import os
import sys
import subprocess
import csv

def main():
    if len(sys.argv) != 2:
        sys.exit("Specify a file")
    path = sys.argv[1]

    instrs = dict()

    if os.path.exists(path):
        if path.endswith(".dump"):
            print(f"Counting instructions in {path} using objdump output...")
            instrs = count_instrs(path)
        elif path.endswith(".s"):
            print(f"Counting instructions in {path} using GCC output...")
            instrs = count_instrs_gcc(path)
        else:
            sys.exit(f"Use a file that ends with .dump or .s")
    else:
        sys.exit("File doesn't exist")


    # Print number of add, sub, mul
    num_adds = instrs.get("add", 0) + instrs.get("addi", 0)
    num_subs = instrs.get("sub", 0)
    num_muls = 0
    total_count = 0
    for key in instrs:
        total_count += instrs.get(key, 0)
        if "mul" in key:
            num_muls += instrs.get(key, 0)

    tot = 0
    with open(f"{path.split()[0]}.csv", 'w') as csv_file:  
        writer = csv.writer(csv_file)
        writer.writerow(["instruction", "count"])
        for w in sorted(instrs, key=instrs.get, reverse=True):
            print(w, instrs[w])
            writer.writerow([w, instrs[w]])
            tot += instrs[w]
        writer.writerow(["total", tot])

    print(f"Total instruction count: {total_count}")
    print(f"add(i): {num_adds}")
    print(f"sub: {num_subs}")
    print(f"mul: {num_muls}")
    print(f"sum: {num_adds + num_subs + num_muls}")

def count_instrs(path):
    instrs = dict()
    with open(path, "r") as file:
        for line in file:
            if line[:3] == "   " and len(line.split()) > 2:
                instruction = line.split()[2]
                instrs[instruction] = instrs.get(instruction, 0) + 1
    return instrs

def count_instrs_gcc(path):
    instrs = dict()
    with open(path, "r") as file:
        found_head = False
        for line in file:
            if line == "ntt8bigint:\n":
                found_head = True
            if found_head:
                if ".size" in line:
                    found_head = False
                    continue
                if line != "" and line[0] == "\t" and line.strip() != "" and line.strip()[0] != "#":
                    line_list = line.split()
                    instrs[line_list[0]] = instrs.get(line_list[0], 0) + 1
    return instrs



if __name__ == "__main__":
    main()
