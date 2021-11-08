# in the name of allah

import os
from pathlib import Path

from antlr4 import *

from cfg_extractor_visitor import CFGExtractorVisitor
from gen.CPP14_v2Lexer import CPP14_v2Lexer
from gen.CPP14_v2Parser import CPP14_v2Parser


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
                elif primepath[k - 1] in exepath[i + j:]:  # tour with sidetrip
                    j += exepath[i + j:].index(primepath[k - 1]) + 1
                elif primepath[k] in exepath[i + j:]:  # tour with detour
                    j += exepath[i + j:].index(primepath[k])
                    k += 1
                else:
                    break
            if k == prime_length:
                return True
    return False


# input_path=input("please enter the source code path:\n")
input_path = 'test_source/5.cpp'
test_cases_dir = 'test_source/4/'
f = open(input_path, 'r')
name = Path(f.name).stem
print('name =', name)
# input("hello")
cfg_path = 'CFGS/v2/' + name
instrument_path = 'Instrument/v2/' + name
try:
    os.mkdir(cfg_path)
except:
    pass
try:
    os.mkdir(instrument_path)
except:
    pass

source = f.read()

stream = InputStream(source)

lexer = CPP14_v2Lexer(stream)

token_stream = CommonTokenStream(lexer)

parser = CPP14_v2Parser(token_stream)

pars_tree = parser.translationunit()

lexer.reset()
number_of_tokens = len(lexer.getAllTokens())

visitor = CFGExtractorVisitor(token_stream)
visitor.visit(pars_tree)

# walker.walk(cfg_listener, pars_tree)

# # compute primepaths
# function_prime_paths = {}
# function_logs = {}
# i = 1
# while True:
#     try:
#         cfg_file = open(cfg_path + '/' + str(i) + '.txt', 'r')
#         cfg = Graph(cfg_file)
#         cfg.computePrimePaths()
#         for j in range(len(cfg.primePaths)):
#             print(j + 1, cfg.primePaths[j])
#         function_prime_paths[i] = cfg.primePaths
#         i += 1
#     except Exception as e:
#         break
# primepaths_json = open(cfg_path + '/primepaths.json', 'w')
# json.dump(function_prime_paths, primepaths_json)
#
# # compute coverage
# instrument_path = 'Instrument\\v2\\' + name
# instrumented_source = instrument_path + '\instrumented_source.cpp'
# instrumented_exe = instrument_path + '\instrumented_source.exe'
# log_file_dir = 'log_file.txt'
# executed_paths = {}
# primepaths_coverage = {}
# i = 1
# # os.system("g++ {0} -o {1} -std=c++11".format(instrumented_source , instrumented_exe))
# test_case_files = [test_file for test_file in os.listdir(test_cases_dir)
#                    if os.path.isfile(os.path.join(test_cases_dir, test_file))]
# for test_case_file in test_case_files:
#     open(test_cases_dir + test_case_file, 'r')
#     executed_paths[i] = {}
#     primepaths_coverage[i] = {}
#     os.system("{0} < {1}".format(instrumented_exe, test_cases_dir + test_case_file))
#     log_file = open(log_file_dir, 'r')
#     log_lines = log_file.readlines()
#     for line in log_lines:
#         f_code, block = (int(x) for x in line.split(' '))
#         try:
#             executed_paths[i][f_code].append(block)
#         except:
#             executed_paths[i][f_code] = [block]
#     print(executed_paths)
#     for j in executed_paths[i]:
#         primepaths_coverage[i][j] = list()
#         primes = function_prime_paths[j]
#         for path in primes:
#             if checkCoverWithSideAndDetour(path, executed_paths[i][j]):
#                 primepaths_coverage[i][j].append(1)
#             else:
#                 primepaths_coverage[i][j].append(0)
#     i += 1
#
# percent_coverage = {}
# for testcase in primepaths_coverage:
#     percent_coverage[testcase] = {}
#     for function in primepaths_coverage[testcase]:
#         percent_coverage[testcase][function] = (sum(primepaths_coverage[testcase][function])
#                                                 / len(primepaths_coverage[testcase][function])) * 100
#
# exepath_file = open(instrument_path + '/exepaths.json', 'w')
# json.dump(executed_paths, exepath_file)
# primepaths_coverage_file = open(instrument_path + '/covered_primepaths.json', 'w')
# json.dump(primepaths_coverage, primepaths_coverage_file)
# percent_coverage_file = open(instrument_path + '/CoveragePercent.json', 'w')
# json.dump(percent_coverage, percent_coverage_file)
