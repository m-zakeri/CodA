"""
CodA main driver module

"""

from antlr4 import *
from pathlib import Path
import os
import json

from coda.antlr_gen.cpp_parser.CPP14_v2Lexer import CPP14_v2Lexer
from coda.antlr_gen.cpp_parser.CPP14_v2Parser import CPP14_v2Parser

from coda.analysis.cfg.cfg_extractor_listener2 import CFGInstListener
from coda.analysis.paths.prime_path_extractor import ControlFlowGraph

# input_path=input("please enter the source code path:\n")
# test_cases_dir = input("please enter the testcases directory:\n")
input_path = 'test_data/2.cpp'
test_cases_dir = 'test_data/test/'

f = open(input_path, 'r')
name = Path(f.name).stem
cfg_path = 'extracted_cfgs/' + name
instrument_path = 'instrumented_programs/' + name

os.makedirs(cfg_path, exist_ok=True)
os.makedirs(instrument_path, exist_ok=True)

source = f.read()

stream = InputStream(source)

lexer = CPP14_v2Lexer(stream)

token_stream = CommonTokenStream(lexer)

parser = CPP14_v2Parser(token_stream)

pars_tree = parser.translationunit()

lexer.reset()
number_of_tokens = len(lexer.getAllTokens())
cfg_listener = CFGInstListener(token_stream, number_of_tokens, name)
walker = ParseTreeWalker()

walker.walk(cfg_listener, pars_tree)

quit()


def checkCoverWithDetour(primepath, exepath):
    exe_length = len(exepath)
    prime_length = len(primepath)
    for i in range(exe_length - prime_length + 1):
        j = 0
        k = 0
        if exepath[i + j] == primepath[k]:
            j += 1
            k += 1
            while k < prime_length and i + j < exe_length:
                if exepath[i + j] == primepath[k]:  # tour directly
                    j += 1
                    k += 1
                elif primepath[k] in exepath[i + j:]:  # tour with detour
                    j += exepath[i + j:].index(primepath[k])
                    k += 1
                else:
                    break
            if k == prime_length:
                return True
    return False


def checkCoverWithSidetour(primepath, exepath):
    exe_length = len(exepath)
    prime_length = len(primepath)
    for i in range(exe_length - prime_length + 1):
        j = 0
        k = 0
        if exepath[i + j] == primepath[k]:
            j += 1
            k += 1
            while k < prime_length and i + j < exe_length:
                if exepath[i + j] == primepath[k]:  # tour directly
                    j += 1
                    k += 1
                elif primepath[k - 1] in exepath[i + j:]:  # tour with sidetrip
                    j += exepath[i + j:].index(primepath[k - 1]) + 1
                else:
                    break
            if k == prime_length:
                return True
    return False


def checkCoverWithSideAndDetour(primepath, exepath):
    exe_length = len(exepath)
    prime_length = len(primepath)
    for i in range(exe_length - prime_length + 1):
        j = 0
        k = 0
        if exepath[i + j] == primepath[k]:
            j += 1
            k += 1
            while k < prime_length and i + j < exe_length:
                if exepath[i + j] == primepath[k]:  # tour directly
                    j += 1
                    k += 1
                elif primepath[k] in exepath[i + j:]:  # tour with detour
                    j += exepath[i + j:].index(primepath[k])
                    k += 1
                elif primepath[k - 1] in exepath[i + j:]:  # tour with sidetrip
                    j += exepath[i + j:].index(primepath[k - 1]) + 1
                else:
                    break
            if k == prime_length:
                return True
    return False


# compute prime_paths
function_prime_paths = {}
function_logs = {}
functions_json = open(cfg_path + '/functions.json', 'r')
function_dict = json.load(functions_json)

for f_code in function_dict:
    try:
        cfg_file = open(cfg_path + '/' + f_code + '.txt', 'r')
        cfg = ControlFlowGraph(cfg_file)
        cfg.computePrimePaths()
        for j in range(len(cfg.primePaths)):
            print(j + 1, cfg.primePaths[j])
        function_prime_paths[f_code] = cfg.primePaths
    except Exception as e:
        pass
primepaths_json = open(cfg_path + '/primepaths.json', 'w')
json.dump(function_prime_paths, primepaths_json)

# compute coverage
instrument_path = 'instrumented_programs/' + name
instrumented_source = instrument_path + '/instrumented_source.cpp'
instrumented_exe = instrument_path + '/instrumented_source.exe'
log_file_dir = 'log_file.txt'
executed_paths = {}
primepaths_coverage = {}
os.system("g++ {0} -o {1} -std=c++11".format(instrumented_source, instrumented_exe))
test_case_files = [test_file for test_file in os.listdir(test_cases_dir)
                   if os.path.isfile(os.path.join(test_cases_dir, test_file))]

side_and_de = 'with sidetrip and detour'
side = 'with sidetrip'
detour = 'with detour'

primepaths_coverage[side_and_de] = {}
primepaths_coverage[side] = {}
primepaths_coverage[detour] = {}

for f_code in function_dict:
    executed_paths[f_code] = {}
    primepaths_coverage[side_and_de][f_code] = {}
    primepaths_coverage[side][f_code] = {}
    primepaths_coverage[detour][f_code] = {}

for test_case_file in test_case_files:
    for f_code in function_dict:
        executed_paths[f_code][test_case_file] = list()
        primepaths_coverage[side_and_de][f_code][test_case_file] = list()
        primepaths_coverage[side][f_code][test_case_file] = list()
        primepaths_coverage[detour][f_code][test_case_file] = list()

    open(test_cases_dir + '/' + test_case_file, 'r')
    os.system("{0} < {1}".format(instrumented_exe, test_cases_dir + '/' + test_case_file))
    log_file = open(log_file_dir, 'r')
    log_lines = log_file.readlines()
    for line in log_lines:
        f_code, block = (x for x in line.split(' '))
        block = int(block)
        executed_paths[f_code][test_case_file].append(block)

    for f_code in function_dict:
        primes = function_prime_paths[f_code]
        for path in primes:
            # with sidetrip and detour
            if checkCoverWithSideAndDetour(path, executed_paths[f_code][test_case_file]):
                primepaths_coverage[side_and_de][f_code][test_case_file].append(1)
            else:
                primepaths_coverage[side_and_de][f_code][test_case_file].append(0)
            # with sidetrip
            if checkCoverWithSidetour(path, executed_paths[f_code][test_case_file]):
                primepaths_coverage[side][f_code][test_case_file].append(1)
            else:
                primepaths_coverage[side][f_code][test_case_file].append(0)
            # with detour
            if checkCoverWithDetour(path, executed_paths[f_code][test_case_file]):
                primepaths_coverage[detour][f_code][test_case_file].append(1)
            else:
                primepaths_coverage[detour][f_code][test_case_file].append(0)

percent_coverage = {side_and_de: {}, side: {}, detour: {}}
for f_code in function_dict:
    if len(function_prime_paths[f_code]) > 0:
        total_cover = [0] * len(function_prime_paths[f_code])
        for testcase in primepaths_coverage[side_and_de][f_code]:
            total_cover = [x or y for x, y in zip(total_cover, primepaths_coverage[side_and_de][f_code][testcase])]
        percent_coverage[side_and_de][f_code] = (sum(total_cover) / len(total_cover) * 100)

        total_cover = [0] * len(function_prime_paths[f_code])
        for testcase in primepaths_coverage[side][f_code]:
            total_cover = [x or y for x, y in zip(total_cover, primepaths_coverage[side][f_code][testcase])]
        percent_coverage[side][f_code] = (sum(total_cover) / len(total_cover) * 100)

        total_cover = [0] * len(function_prime_paths[f_code])
        for testcase in primepaths_coverage[detour][f_code]:
            total_cover = [x or y for x, y in zip(total_cover, primepaths_coverage[detour][f_code][testcase])]
        percent_coverage[detour][f_code] = (sum(total_cover) / len(total_cover) * 100)
    else:
        percent_coverage[side_and_de][f_code] = 0
        percent_coverage[side][f_code] = 0
        percent_coverage[detour][f_code] = 0

exepath_file = open(instrument_path + '/exepaths.json', 'w')
json.dump(executed_paths, exepath_file)
primepaths_coverage_file = open(instrument_path + '/covered_primepaths.json', 'w')
json.dump(primepaths_coverage, primepaths_coverage_file)
percent_coverage_file = open(instrument_path + '/CoveragePercent.json', 'w')
json.dump(percent_coverage, percent_coverage_file)
