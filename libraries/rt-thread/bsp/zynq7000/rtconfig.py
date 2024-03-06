import os

# toolchains options
ARCH='arm'
CPU='zynq7000'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

# only support GNU GCC compiler
PLATFORM 	= 'gcc'
EXEC_PATH 	= '/opt/arm-none-eabi-gcc'

if os.getenv('RTT_EXEC_PATH'):
    EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'
    #ARCH    = -mcpu=cortex-a9 -mfpu=vfpv3 
    DEVICE = ' -Wall -mcpu=cortex-a9 -mfpu=vfpv3 -ftree-vectorize -ffast-math -mfloat-abi=softfp'
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LINK_SCRIPT = 'zynq7000.ld'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=zynq7000.map,-cref,-u,system_vectors -T %s' % LINK_SCRIPT

    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
            SIZE + ' $TARGET \n'
