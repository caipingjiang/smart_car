/*!
*******************************************************************************
**
** \file      gd_sflash.h
**
** \brief     Serail Flash memory driver.
**
**            (C) Goke Microelectronics China 2002 - 2007
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
*******************************************************************************
*/
#ifndef GD_SFLASH_H
#define GD_SFLASH_H

#include <gtypes.h>
#include <gmodids.h>
#include "gd_spi.h"
/*!
*******************************************************************************
**
** \brief Flash channel number.
**
*******************************************************************************
*/
typedef enum
{
    GD_SFLASH_CHANNEL_0 = 0,     // used gk6202 sflash module, channel 0
    GD_SFLASH_CHANNEL_1,         // used gk6202 sflash module, channel 1
    GD_SFLASH_SPI_CHANNEL_0_0,   // used gk7101 spi module, spi 0, channel 0
    GD_SFLASH_SPI_CHANNEL_0_1,   // used gk7101 spi module, spi 0, channel 1
    GD_SFLASH_SPI_CHANNEL_0_4,   // used gk7101 spi module, spi 0, channel 4
    GD_SFLASH_SPI_CHANNEL_0_5,   // used gk7101 spi module, spi 0, channel 5
    GD_SFLASH_SPI_CHANNEL_0_6,   // used gk7101 spi module, spi 0, channel 6
    GD_SFLASH_SPI_CHANNEL_0_7,   // used gk7101 spi module, spi 0, channel 7
    GD_SFLASH_SPI_CHANNEL_1_0,   // used gk7101 spi module, spi 1, channel 0
   GD_SFLASH_CHANNEL_NUM
}GD_SFLASH_CHANNEL_E;

/*!
*******************************************************************************
**
** \brief Flash IOx Mode.
**
*******************************************************************************
*/
typedef enum
{
   GD_SFLASH_IO1_MODE = 1,
   GD_SFLASH_IO2_MODE = 2,
   GD_SFLASH_IO4_MODE = 4
}GD_SFLASH_IO_MODE_E;

/*!
*******************************************************************************
**
** \brief Flash read or write.
**
*******************************************************************************
*/
typedef enum
{
   GD_SFLASH_READ = 0,
   GD_SFLASH_WRITE
}GD_SFLASH_RW_E;

/*!
*******************************************************************************
**
** \brief Flash Type.
**
*******************************************************************************
*/
typedef enum
{
   GD_SPI_NOR = 0,     // normal SPI nor-flash
   GD_SPI_NAND         // SPI nand-flash
}GD_SFLASH_TYPE_E;

/*
*******************************************************************************
**
** serial flash specific commands and statis register bit definitions
**
*******************************************************************************
*/
typedef struct
{
    U8  readID;        // command to read the chip identification
    U8  writeEnable;   // command to enable a write/erase sequence
    U8  writeDisable;  // command to disable a write/erase sequence
    U8  readStatus;    // command to read from status register
    U8  writeStatus;   // command to write to status register
    U8  readData;      // command to read data
    U8  readDataFast;  // command to read data in fast mode
    U8  eraseSector;   // command to erase a single sector
    U8  eraseChip;     // command to erase the entire chip
    U8  programPage;   // command to program a sector page
    U32 statusMaskWIP; // status register mask for bit write-in-progress
    U32 statusMaskWEL; // status register mask for bit write-enable-latch
    U8  readData2;     // command to read data by IO2
    U8  readData4;     // command to read data by IO4
    U8  programPage2;  // command to program a sector page by IO2
    U8  programPage4;  // command to program a sector page by IO4
    U8  pageRead;      // command to read page to cache,                 new added for spi-nand
    U8  programExecute;// command to execute program from cache to page, new added for spi-nand
}GD_SFLASH_CMD_S;

/*
*******************************************************************************
**
** serial flash specific geometry and information data structure
**
*******************************************************************************
*/
typedef struct
{
    U8               manufactureID;   // Manufacture identification
    U16              deviceID;        // Device identification (memory type/capacity)
    char*            manufactureName; // Pointer to manufacture name
    char*            deviceName;      // Pointer to device name
    U32              deviceBytes;     // Size of flash device in bytes
    U32              sectorCount;     // Number of sectors
    U32              sectorBytes;     // Size of a single flash sector in bytes
    U32              sectorPages;     // Number of pages per sector
    U32              pageBytes;       // Size of a programmable page in bytes
    GD_SFLASH_CMD_S* commands;        // Device specific access commands
    U32              ioMode;          // bit[0:3] for read, bit[4:7] for write
    GD_SFLASH_TYPE_E type;            // SPI nor flash or nand flash
    GD_SFLASH_CHANNEL_E channel;      //
    U32              devicechannel;   // SFLAH/SPI CS channel
}GD_SFLASH_DEV_S;

typedef struct
{
    void (*GH_SFLASH_set_Handle)(GD_SPI_STATUS_PARAMS_S*);
    void (*GH_SFLASH_set_Command)(U32);
    void (*GH_SFLASH_set_Data)(U32);
    U32  (*GH_SFLASH_get_Data)(void);
    void (*GH_SFLASH_set_CE)(U32);
    U32  (*GH_SFLASH_get_CE)(void);
    U8   (*GH_SFLASH_get_CE_CHSELECT)(void);
    void (*GH_SFLASH_set_Speed)(U32);
    void (*GH_SFLASH_set_CE_CHSELECT)(U8);
}GD_SFLASH_FUNC_S;

/*!
*******************************************************************************
**
** \anchor gd_sflash_error_base
** \brief he base error code for the serial flash device driver.
**
*******************************************************************************
*/
#define GD_SFLASH_ERR_BASE (GD_SFLASH_MODULE_ID<<16)

/*!
*******************************************************************************
**
** \brief Flash driver error codes.
**
*******************************************************************************
*/
enum
{
    GD_ERR_SFLASH_TYPE_NOT_SUPPORTED = GD_SFLASH_ERR_BASE, //!< Device not supported.
    GD_ERR_SFLASH_IN_USE,                                  //!< Read error.
    GD_ERR_SFLASH_READ,                                    //!< Read error.
    GD_ERR_SFLASH_WRITE,                                   //!< Write error.
    GD_ERR_SFLASH_ERASE,
    GD_ERR_UNLOCK_FAIL
};

// TODO: to be confirmed for each clock value
// FPGA: SCLK = 40MHz
// EVM: SCLK = 135MHz
// 000: SCLK/2
// 001: SCLK/4
// 010: SCLK/6
// 011: SCLK/8
// 100: SCLK/10
typedef enum
{
   GD_SFLASH_FREQ_DIV2 = 0,
   GD_SFLASH_FREQ_DIV4,
   GD_SFLASH_FREQ_DIV6,
   GD_SFLASH_FREQ_DIV8,
   GD_SFLASH_FREQ_DIV10,
}GD_SFLASH_SPEED_MODE;


/*-------------------------------------------------------------------------------*/
/* \brief Flash I/O feature.                                                     */
/*-------------------------------------------------------------------------------*/

typedef enum
{
   GD_SFLASH_FEATURE_IO1 = 0,
   GD_SFLASH_FEATURE_IO2,
   GD_SFLASH_FEATURE_IO4
}GD_SFLASH_FEATURE;


/*******************************************************************************************************************************************
*   sflash cmd attribute
*   sflash cmd register bit definition
*   bit 31    30    29    28    27    26    25    24    23    22    21         20        19           18    17
        | rsrd    | hold time | transfer data bytes       |data cycle|adr and dummy cycle | cmd cycle |
                      00-100ns   11111 -- 4 bytes                                                           00 -x1
                      01-3us      other(e.g.,n) -- n bytes   0-3 cycle        0-3 cycle              01 -x2
                      10-100us                                                                                      10 -x4

    bit       16           15          14        13        12        11     10     9            8                      [7: 0]
        |         RWN            |  dummy cycle number   |  adr byte num    |                        |      cmd to DF                 |
          00 - rd data for SF     0 - 7 bytes cycle            0-7 bytes          1 - send cmd
          01 - wr data to SF                                                                0 - no send cmd        see specific flash cmd
          11 - nothing to do

********************************************************************************************************************************************/
/* send cmd or not [ 8]*/
#define SFLASH_SEND_CMD                 0x00000100
#define SFLASH_NO_SEND_CMD              0x00000000

/* byte number of address to send [11:9]*/
#define SFLASH_SEND_ADDR_BYTE_NUM_0     0x00000000
#define SFLASH_SEND_ADDR_BYTE_NUM_1     0x00000200
#define SFLASH_SEND_ADDR_BYTE_NUM_2     0x00000400
#define SFLASH_SEND_ADDR_BYTE_NUM_3     0x00000600
#define SFLASH_SEND_ADDR_BYTE_NUM_4     0x00000800
#define SFLASH_SEND_ADDR_BYTE_NUM_5     0x00000a00
#define SFLASH_SEND_ADDR_BYTE_NUM_6     0x00000c00
#define SFLASH_SEND_ADDR_BYTE_NUM_7     0x00000e00

/* byte number of dummy cycle to send [14:12] */
#define SFLASH_SEND_DUMMY_BYTE_NUM_0    0x000000000
#define SFLASH_SEND_DUMMY_BYTE_NUM_1    0x000001000
#define SFLASH_SEND_DUMMY_BYTE_NUM_2    0x000002000
#define SFLASH_SEND_DUMMY_BYTE_NUM_3    0x000003000
#define SFLASH_SEND_DUMMY_BYTE_NUM_4    0x000004000
#define SFLASH_SEND_DUMMY_BYTE_NUM_5    0x000005000
#define SFLASH_SEND_DUMMY_BYTE_NUM_6    0x000006000
#define SFLASH_SEND_DUMMY_BYTE_NUM_7    0x000007000

/* command operation[16:15]: 00 for read data from SF; 01 for write data to SF; 11 for nothing to do */
#define SFLASH_RWN_READ                 0x00000000
#define SFLASH_RWN_WRITE                0x00008000
#define SFLASH_RWN_NOTHING              0x00018000

/* I/O mode of command cycle to SF[18:17]: 00 for x1; 01 for x2; 10 for x4 */
#define SFLASH_CMD_MODE_1X              0x00000000
#define SFLASH_CMD_MODE_2X              0x00020000
#define SFLASH_CMD_MODE_4X              0x00040000

/* I/O mode of address and dummy cycle to SF[20:19] */
#define SFLASH_ADDR_DUMMY_CYCLE_NUM_0   0x00000000
#define SFLASH_ADDR_DUMMY_CYCLE_NUM_1   0x00080000
#define SFLASH_ADDR_DUMMY_CYCLE_NUM_2   0x00100000
#define SFLASH_ADDR_DUMMY_CYCLE_NUM_3   0x00180000

/* I/O mode of data cycle to or from SF [22:21] */
#define SFLASH_DATA_CYCLE_NUM_0         0x00000000
#define SFLASH_DATA_CYCLE_NUM_1         0x00200000
#define SFLASH_DATA_CYCLE_NUM_2         0x00400000
#define SFLASH_DATA_CYCLE_NUM_3         0x00600000

/* transfer data byte number to or from SF[27:23]. For 11111 case, transfer 4bytes per request */
/* for other case, transfer number bytes */
#define SFLASH_TRANSFER_BYTE_NUM_1      0x00800000
#define SFLASH_TRANSFER_BYTE_NUM_2      0x01000000
#define SFLASH_TRANSFER_BYTE_NUM_3      0x01800000
#define SFLASH_TRANSFER_BYTE_NUM_4      0x0f800000
#define SFLASH_TRANSFER_BYTE_LOC        23

#define SFLASH_HOLD_TIME_100ns          0x00000000
#define SFLASH_HOLD_TIME_3us            0x10000000
#define SFLASH_HOLD_TIME_100us          0x20000000

#define GD_SFLASH_1X_READ               0x01
#define GD_SFLASH_2X_READ               0x02
#define GD_SFLASH_4X_READ               0x04
#define GD_SFLASH_1X_WRITE              0x10
#define GD_SFLASH_2X_WRITE              0x20
#define GD_SFLASH_4X_WRITE              0x40

/*
*******************************************************************************
*******************************************************************************
**
** Generic serial flash specific API functions
**
*******************************************************************************
*******************************************************************************
*/
#ifdef __cplusplus
extern "C" {
#endif

GERR GD_SFLASH_Init(void);
GERR GD_SFLASH_Exit(void);
GERR GD_SFLASH_Open(GD_HANDLE* pHandle, GD_SFLASH_SPEED_MODE speed_mode, GD_SFLASH_CHANNEL_E channel);
GERR GD_SFLASH_Close(GD_HANDLE* pHandle);
GERR GD_SFLASH_Read(GD_HANDLE handle, U32 address, U32* buffer, U32 words);
GERR GD_SFLASH_Write(GD_HANDLE handle, U32 address, U32* buffer, U32 words);
GERR GD_SFLASH_Program(GD_HANDLE handle, U32 address, U32* buffer, U32 words);
GERR GD_SFLASH_EraseChip(GD_HANDLE handle);
GERR GD_SFLASH_EraseSector(GD_HANDLE handle, U16 sector);
GERR GD_SFLASH_GetCodes(GD_HANDLE handle, U8* manufactureCode, U16* deviceCode);
GERR GD_SFLASH_GetNames(GD_HANDLE handle, char** manufactureName, char** deviceName);
GERR GD_SFLASH_GetNumberOfSectors(GD_HANDLE handle, U16* numberOfSectors);
GERR GD_SFLASH_GetSectorAddress(GD_HANDLE handle, U16 sector, U32* address);
GERR GD_SFLASH_GetSize(GD_HANDLE handle, U32* deviceWords);
GERR GD_SFLASH_GetSectorSize(GD_HANDLE handle, U16 sector, U32* deviceWords);
GERR GD_SFLASH_GetSector(GD_HANDLE handle, U32 address, U16* sector);
GERR GD_SFLASH_IsChipEmpty(GD_HANDLE handle, GBOOL* isEmpty);
GERR GD_SFLASH_IsSectorEmpty(GD_HANDLE handle, U16 sector, GBOOL* isSectorEmpty);
GERR GD_SFLASH_Unlock(GD_HANDLE handle);
GERR GD_SFLASH_Lock(GD_HANDLE handle);
GERR GD_SFLASH_IsChipLocked(GD_HANDLE handle, GBOOL* isChipLocked);
GERR GD_SFLASH_GetIoMode(GD_HANDLE handle, GD_SFLASH_RW_E op, GD_SFLASH_IO_MODE_E* ioMode);
GERR GD_SFLASH_SetIoMode(GD_HANDLE handle, GD_SFLASH_RW_E op, GD_SFLASH_IO_MODE_E ioMode);
GERR GD_SFLASH_SetResetMode(GD_HANDLE handle, GBOOL mode);
#ifdef __cplusplus
}
#endif

#endif
