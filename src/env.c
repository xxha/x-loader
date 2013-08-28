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

#include "nand.h"

typedef	struct {
	uint32_t	crc;		/* CRC32 over data bytes */
	uint8_t		data[1];	/* Environment data */
} env_t;

int readenv(uint8_t *buf, uint32_t start, uint32_t end)
{
	env_t *hdr = (env_t *)buf;
	uint32_t page = PAGE(start);
	uint32_t endPage = PAGE(end);
	uint32_t crc;
	int size = 0, i = sizeof(hdr->crc);

	page = ReadNandPages(page, buf, 1, endPage);
	if (!page)
	{
		puts("ERROR: Cannot read env page\r\n");
		return -1;
	}

	// env area is a bunch of \0 terminated strings where the end is an
	// empty string.
	do
	{
		while (buf[i++]) {
			if (i >= PAGE_SIZE)
			{
				i -= PAGE_SIZE;
				size += PAGE_SIZE;
				buf += PAGE_SIZE;
				page = ReadNandPages(page, buf, 1, endPage);
				if (!page)
				{
					puts("ERROR: Cannot read env page\r\n");
					return -1;
				}
			}
		}

		// Read in the next page if the \0 was at the end of the page.
		if (i >= PAGE_SIZE)
		{
			i -= PAGE_SIZE;
			size += PAGE_SIZE;
			buf += PAGE_SIZE;
			page = ReadNandPages(page, buf, 1, endPage);
			if (!page)
			{
				puts("ERROR: Cannot read env page\r\n");
				return -1;
			}
		}
	} while (buf[i]);

	size += i + 1 - sizeof(crc);
	crc = crc32(0, hdr->data, size);

	if (hdr->crc != crc) {
		puts("ERROR: env CRC mismatch: expected ");
		writeHex(hdr->crc);
		puts(", calculated ");
		writeHex(crc);
		puts(".\r\n");
		return -1;
	}

	return 0;
}

char *envVar (uint8_t *env, char *name)
{
	// skip CRC
	env += 4;

	while (*env) {
		if (!strncmp(env, name, strlen(name))) {
			env += strlen(name);
			if (*env == '=')
				return env + 1;
		}
		env += strlen(env) + 1;
	}
	return 0;
}
