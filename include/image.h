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

#ifndef _IMAGE_H_
#define _IMAGE_H_

#define IH_OS_LINUX			5			/* Linux OS */
#define IH_OS_U_BOOT		17			/* U-boot Firmware */
#define IH_ARCH_ARM			2			/* ARM arch */
#define IH_TYPE_KERNEL		2			/* Kernel Image */
#define IH_COMP_NONE		0			/* No Compression */

#define IH_MAGIC			0x27051956	/* Magic Number */
#define IH_NMLEN			32			/* Max Name Length */

typedef struct image_header
{
	uint32_t ih_magic;					/* Magic Number */
	uint32_t ih_hcrc;					/* Header CRC */
	uint32_t ih_time;					/* Creation Timestamp */
	uint32_t ih_size;					/* Image Size */
	uint32_t ih_load;					/* Address to put image */
	uint32_t ih_ep;						/* Address to jump to */
	uint32_t ih_dcrc;					/* Image CRC */
	uint8_t ih_os;						/* OS */
	uint8_t ih_arch;					/* CPU arch */
	uint8_t ih_type;					/* Type */
	uint8_t ih_comp;					/* Compression */
	uint8_t ih_name[IH_NMLEN];			/* Name */
} image_header_t;

#define ATAG_NONE		0x00000000		/* The end of the list. */
#define ATAG_CORE		0x54410001		/* The start of the list. */
#define ATAG_MEM		0x54410002		/* device memory layout */
#define ATAG_CMDLINE	0x54410009		/* Command line arg */

struct tag_header
{
	uint32_t size;
	uint32_t tag;
};

struct tag_core
{
	uint32_t flags;
	uint32_t pagesize;
	uint32_t rootdev;
};

struct tag_mem32
{
	uint32_t size;
	uint32_t start;
};

struct tag_cmdline
{
	char cmdline[1];
};

struct tag
{
	struct tag_header hdr;
	union
	{
		struct tag_core core;
		struct tag_mem32 mem;
		struct tag_cmdline cmdline;
	} u;
};

#define tag_next(t)	((struct tag *)((uint32_t *)(t) + (t)->hdr.size))
#define tag_size(type)	((sizeof(struct tag_header) + sizeof(struct type)) >> 2)

#endif	/* __IMAGE_H__ */
