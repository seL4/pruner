#!/usr/bin/env python

'''
Script for reflowing C code.

This script is intended to be run on arbitrarily messy - but valid - C code,
which it then attempts to reformat into something more readable. Usage is
pretty straightforward. Note that you will need a recent version of Clang to
avoid common bugs in its AST printing mode.
'''

import re, subprocess, sys

def main():
    for h in ['--help', '-h', '-?']:
        if h in sys.argv[1:]:
            print 'Usage: %s args...\n' \
                  ' Any arguments will be interpreted as parameters to the Clang frontend.\n' \
                  ' E.g. -triple arm-none-eabi if you are parsing ARM code.' % sys.argv[0]
            return 0

    try:
        output = subprocess.check_output(
            ['clang', '-cc1', '-ast-print'] + sys.argv[1:])
    except OSError:
        print >>sys.stderr, 'Clang not found'
        return -1
    except subprocess.CalledProcessError as e:
        # Clang threw an error
        return e.returncode

    # http://llvm.org/bugs/show_bug.cgi?id=21106
    output = re.sub(r'(\s)register\s+([^ ]+)\s+([^ ]+)\s*=\s*(.+)\s+(asm\(".*"\));',
        r'\1register \2 \3 \5 = \4;', output)

    # http://lists.cs.uiuc.edu/pipermail/cfe-dev/2014-September/039366.html
    # The algorithm below isn't bulletproof, but it's good enough for our
    # purposes for now.
    offset = 0
    asm_re = re.compile(r'(\sasm\s+(?:volatile\s*)?)\((.*)\);')
    arg_re = re.compile(r'(".*?"\s)([^,:]+)\s?([,:])')
    while True:
        asm_block = asm_re.search(output, offset)
        if asm_block is None:
            break
        prefix = asm_block.group(1)
        args = arg_re.sub(r'\1(\2) \3', asm_block.group(2))
        replacement = '%s (%s);' % (prefix, args)
        output = output[:asm_block.start()] + replacement + output[asm_block.end():]
        offset = asm_block.start() + len(replacement)

    print output

    return 0

if __name__ == '__main__':
    sys.exit(main())
