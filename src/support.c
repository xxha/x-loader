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

#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#include "config.h"
#include "gpio_p.h"
#include "image.h"
#include "env.h"
#include "nand.h"
#include "support.h"

static uint8_t *env;
static uint32_t nandPage[PAGE_SIZE / sizeof(uint32_t)];

static const uint8_t *defaultEnv = DEFAULT_ENV;
static int isUboot;

static void setupTags(struct tag *tags)
{
	char *cmdline = envVar(env, "bootargs");

	tags->hdr.tag = ATAG_CORE;
	tags->hdr.size = tag_size (tag_core);

	tags->u.core.flags = 0;
	tags->u.core.pagesize = 0;
	tags->u.core.rootdev = 0;

	tags = tag_next (tags);

	tags->hdr.tag = ATAG_MEM;
	tags->hdr.size = tag_size (tag_mem32);

	tags->u.mem.start = BANK0_START;
	tags->u.mem.size  = BANK0_SIZE;

	tags = tag_next (tags);

	tags->hdr.tag = ATAG_CMDLINE;
	tags->hdr.size = (sizeof (struct tag_header) + strlen (cmdline) + 1 + 4) >> 2;

	strcpy (tags->u.cmdline.cmdline, cmdline);

	tags = tag_next (tags);

	tags->hdr.tag = ATAG_NONE;
	tags->hdr.size = 0;
}

uint32_t strHex(char *str, char **end)
{
	uint32_t hex = 0;

	// Accept leading 0x
	if (str[0] == '0' && str[1] == 'x')
		str += 2;

	while (*str) {
		if (*str >= '0' && *str <= '9') {
			hex <<= 4;
			hex += (*str - '0');
		}
		else if (*str >= 'a' && *str <= 'f') {
			hex <<= 4;
			hex += 0xa + (*str - 'a');
		}
		else if (*str >= 'A' && *str <= 'F') {
			hex <<= 4;
			hex += 0xa + (*str - 'A');
		}
		else {
			*end = str;
			return hex;
		}
		str++;
	}
	*end = str;
	return hex;
}

void writeHex(uint32_t data)
{
	const char hex[16] = "0123456789ABCDEF";
	char str[2] =
	{ '0', 0 };
	uint8_t i;

	for (i = 0; i <= 7; i++)
	{
		str[0] = hex[(data & 0xf0000000) >> 28];
		puts(str);
		data &= 0x0fffffff;
		data = data << 4;
	}
}

void jumpTo(uint32_t entry)
{
	struct tag *tags = (struct tag *)BOOT_PARAMS_OFFSET;

	puts("Booting OS...\r\n");
	UART_flush();

	setupTags(tags);

	*(volatile uint32_t *) (GPIO2_REG_START_ADDR + GPIO_MIC_OFFSET)   |=  GPIO_PIN82_HIGH;
	*(volatile uint32_t *) (GPIO2_REG_START_ADDR + GPIO_FIMSC_OFFSET) &= ~GPIO_PIN82_HIGH;
	*(volatile uint32_t *) (GPIO2_REG_START_ADDR + GPIO_RIMSC_OFFSET) &= ~GPIO_PIN82_HIGH;

	// -----------------------------------
	// Let's jump to the image entry point
	// -----------------------------------
	((void (*)(int, int, struct tag *)) entry)(0, MACH_TYPE, tags);

	// ------------------------------------------------------------------------- //
	// !!!! we should never be here... may be we should generate a sw reset !!!! //
	// ------------------------------------------------------------------------- //
}

int bootPart(range_t *range)
{
	char *part = envVar(env, "bootpart");
	int count = 0;

	if (!part)
		return 0;

	while (*part) {
		range->start = strHex(part, &part);
		if (*part == ':')
			range->end = strHex(part + 1, &part);
		range++;
		count++;
		if (*part++ != ',')
			break;
	}

	return count;
}

uint32_t loadImage(uint32_t start, uint32_t end)
{
	image_header_t *header = (image_header_t *) nandPage;
	uint8_t *src = (uint8_t *) nandPage;
	uint8_t *dst;
	uint32_t page = PAGE(start);
	uint32_t endPage = PAGE(end);
	uint32_t crc;

	page = ReadNandPages(page, src, 1, endPage);
	if (!page)
	{
		puts("ERROR: Cannot read header page\r\n");
		return ~0;
	}

	if (ntohl(header->ih_magic) != IH_MAGIC)
	{
		puts("ERROR: Header magic mismatch\r\n");
		return ~0;
	}

	switch (header->ih_os)
	{
	case IH_OS_LINUX:
		isUboot = 0;
		break;
	case IH_OS_U_BOOT:
		isUboot = 1;
		break;
	default:
		puts("ERROR: Unsupported OS type\r\n");
		return ~0;
	}

	if (header->ih_arch != IH_ARCH_ARM) {
		puts("ERROR: Unsupported ARCH type\r\n");
		return ~0;
	}

	if (header->ih_type != IH_TYPE_KERNEL) {
		puts("ERROR: Unsupported Image type\r\n");
		return ~0;
	}

	puts("Image: ");
	puts(header->ih_name);
	puts("\r\n");

	src += sizeof(image_header_t);
	dst = (uint8_t *) ntohl(header->ih_load);

	switch (header->ih_comp) {
	case IH_COMP_NONE:
	{
		const int inSRAM = PAGE_SIZE - sizeof(image_header_t);
		memcpy(dst, src, inSRAM);
		dst += PAGE_SIZE - sizeof(image_header_t);

		page = ReadNandPages(page, dst, PAGE(ntohl(header->ih_size) - inSRAM), endPage);
		if (!page)
		{
			puts("ERROR: problem reading NAND\r\n");
			return ~0;
		}

		// Calculate CRC
		dst = (uint8_t *) ntohl(header->ih_load);
		crc = crc32(0, dst, ntohl(header->ih_size));
		break;
	}
	default:
		puts("ERROR: Unsupported compression\r\n");
		return ~0;
	}

	// Verify CRC
	if (ntohl(header->ih_dcrc) != crc) {
		puts("ERROR: CRC mismatch\r\n");
		return ~0;
	}

	return ntohl(header->ih_ep);
}

void loadEnv(uint32_t start, uint32_t end)
{
	int err = 0;
	puts("loadEnv: ----------\r\n");
	env = (uint8_t *)ENV_RAM_ADDR;

	err = readenv(env, start, end);
	if (err){
		puts("read env error, use default instead\r\n");
		env = (uint8_t *)defaultEnv;
	}
}

int wdEnabled(void)
{
	char *enabled = envVar(env, "watchdog");

	// Never enable watchdog for u-boot images.
	if (isUboot)
		return 0;

	// Anything other than "disable" means it is enabled.
	return (enabled && !strcmp(enabled, "disable")) ? 0 : 1;
}
