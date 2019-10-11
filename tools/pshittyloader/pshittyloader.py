#!/usr/bin/env python3

import sys
import serial
import os

bps=115200

args = int(len(sys.argv))

sys.stdout.write("\npshittyloader.py\n\n");

if args < 2:
        sys.stdout.write("   usage :  pshittyload.py DEV FILE\n\n")

else:
        devPath = sys.argv[1]
        filePath = sys.argv[2]

        filesize = os.path.getsize(filePath)

        nchunks = int(filesize / 2048)
        inputfile = open(filePath, 'rb')

        sys.stdout.write("Port:             {}\n".format(devPath))
        sys.stdout.write("Speed(bps):       {}\n".format(bps))
        sys.stdout.write("Executable:\n")
        sys.stdout.write("  Name:           {}\n".format(filePath))
        sys.stdout.write("  Size(bytes):    {}\n".format(filesize))

        ser = serial.Serial(devPath, bps, writeTimeout = 1)
        sys.stdout.write('\n- Waiting for remote device...\n')

        # send 'P', 'L' and expect '+' in response.
        b = b'!'
        while b != b'+':
            ser.flushInput()
            ser.flushOutput()
            ser.write(b'P')
            ser.write(b'L')
            b = ser.read()
            if b != b'+':
                sys.stdout.write("Bad sync response: {}\n".format(b))

        sys.stdout.write('- Sending File...\n')

        i = 1
        while i <= nchunks:
            d = inputfile.read(2048)
            ser.write(d)
            sys.stdout.write('- [%s%s]\r' % ((int((100/nchunks) * i)), "%"))
            sys.stdout.flush()
            i += 1

        sys.stdout.write('\n- Done!\n')
