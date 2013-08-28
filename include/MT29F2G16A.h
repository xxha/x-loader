/*******************************************************************************
 *                                 Wind River
 *      Work based on x-loader sources from STMicroelectronics which has the
 *      following notice:
 *
 *      Reproduction and Communication of this document is strictly prohibited
 *      unless specifically authorized in writing by STMicroelectronics.
 *
 *      This work, however, has made significant changes to the original
 *      baseline. In fact, there is very little code left from the original.
 *      The above notice has been retained, however, to avoid any issues.
 * 
 *		All Rights reserved by Wind River.
 *
 ******************************************************************************/

#define DEVICE_ID                       0xCA
#define MAKER_ID                        0x2C
#define NAND_TIMING_1                   0x05
#define NAND_TIMING_2                   0x05

#define DATA_BYTES_PER_SECTOR           2048
#define ECC_BLOCKS_PER_PAGE             4               // DATA_BYTES_PER_SECTOR / ECC_WORD_LIMIT
#define ECC_OOB_START                   2

/*
 * 16-bit bus means offset is in words. shift right one bit.
 */
#define SET_BLOCK_ADDRESSING(z,x,y)\
    *(z)        = (uint8_t)((x >> 1) & 0xFF); \
    *(z)        = (uint8_t)((x >> 9) & 0xFF); \
    *(z)        = (uint8_t)(y & 0xFF); \
    *(z)        = (uint8_t)((y >> 8) & 0xFF); \
    *(z)        = (uint8_t)((y >> 16) & 0xFF);

#define SET_BLOCK_OFFSET(z,x)\
    *(z)        = (uint8_t)((x >> 1) & 0xFF); \
    *(z)        = (uint8_t)((x >> 9) & 0xFF);
