import os

# toolchains options
ARCH='arm'
CPU='realview-a8-vmm'
CROSS_TOOL='gcc'

if os.getenv('RTT_CC'):
    CROSS_TOOL = os.getenv('RTT_CC')

PLATFORM    = 'gcc'
# EXEC_PATH = r'/opt/arm-2012.09/bin'
EXEC_PATH   = r'C:\Program Files (x86)\CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_EABI\bin'
EXEC_PATH   = '/opt/gcc-arm-none-eabi-4_8-2014q1_gri/bin'

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

    DEVICE = ' -march=armv7-a -mtune=cortex-a8 -mfpu=vfpv3-d16 -ftree-vectorize -ffast-math -mfloat-abi=softfp'
    CFLAGS = DEVICE + ' -Wall'
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp -D__ASSEMBLY__'
    LINK_SCRIPT = 'realview_vmm.lds'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=realview.map,-cref,-u,system_vectors'+\
                      ' -T %s' % LINK_SCRIPT

    CPATH = ''
    LPATH = ''

    # generate debug info in all cases
    AFLAGS += ' -gdwarf-2'
    CFLAGS += ' -g -gdwarf-2'

    if BUILD == 'debug':
        CFLAGS += ' -O0'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' +\
                  SIZE + ' $TARGET \n' +\
                  OBJDUMP + ' -S $TARGET > rtt.S\n'
