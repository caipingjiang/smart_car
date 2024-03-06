import os

# toolchains options
ARCH='arm'
CPU='cortex-m4'
CROSS_TOOL='keil'

if os.getenv('RTT_CC'):
	CROSS_TOOL = os.getenv('RTT_CC')

if  CROSS_TOOL == 'gcc':
	PLATFORM 	= 'gcc'
	EXEC_PATH 	= r'D:/xxx'
elif CROSS_TOOL == 'keil':
	PLATFORM 	= 'armcc'
	EXEC_PATH 	= 'D:/Keil'
elif CROSS_TOOL == 'iar':
    print('================ERROR============================')
    print('Not support iar yet!')
    print('=================================================')
    exit(0)

if os.getenv('RTT_EXEC_PATH'):
	EXEC_PATH = os.getenv('RTT_EXEC_PATH')

BUILD = 'debug'

if PLATFORM == 'gcc':
    # toolchains
    PREFIX = 'arm-none-eabi-'
    CC  = PREFIX + 'gcc'
    CXX = PREFIX + 'g++'
    AS = PREFIX + 'gcc'
    AR = PREFIX + 'ar'
    LINK = PREFIX + 'gcc'
    TARGET_EXT = 'elf'
    SIZE = PREFIX + 'size'
    OBJDUMP = PREFIX + 'objdump'
    OBJCPY = PREFIX + 'objcopy'

    DEVICE = ' -mcpu=' + CPU + ' -mthumb '
    CFLAGS = DEVICE
    AFLAGS = ' -c' + DEVICE + ' -x assembler-with-cpp'
    LFLAGS = DEVICE + ' -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T drivers/linker_scripts/link.lds'
    CXXFLAGS = CFLAGS
	
    CPATH = ''
    LPATH = ''

    if BUILD == 'debug':
        CFLAGS += ' -O0 -gdwarf-2'
        AFLAGS += ' -gdwarf-2'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = OBJCPY + ' -O binary $TARGET rtthread.bin\n' + SIZE + ' $TARGET \n'

elif PLATFORM == 'armcc':
    # toolchains
    CC = 'armcc'
    CXX = 'armcc'
    AS = 'armasm'
    AR = 'armar'
    LINK = 'armlink'
    TARGET_EXT = 'axf'

    DEVICE = ' --cpu ' + CPU + '.fp '
    CFLAGS = '-c ' + DEVICE + ' --apcs=interwork'
    AFLAGS = DEVICE + ' --apcs=interwork '
    LFLAGS = DEVICE + ' --scatter "drivers/linker_scripts/link.sct" --info sizes --info totals --info unused --info veneers --list rtthread.map --strict'

    CFLAGS += ' -I' + EXEC_PATH + '/ARM/ARMCC/INC'
    LFLAGS += ' --libpath ' + EXEC_PATH + '/ARM/ARMCC/LIB'
    CXXFLAGS = CFLAGS

    EXEC_PATH += '/arm/armcc/bin/'

    if BUILD == 'debug':
        CFLAGS += ' -g -O0'
        AFLAGS += ' -g'
    else:
        CFLAGS += ' -O2'

    POST_ACTION = 'fromelf --bin $TARGET --output rtthread.bin \nfromelf -z $TARGET'
