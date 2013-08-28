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

#include "dma.h"

/*
 * DMA Channel X Configuration Register bitfields
 */
#define DMA_CFG_ENABLE		(1 <<  0)		/* Channel Enable              */
#define DMA_CFG_SRCP(x)		(((x) & 0x1F) << 1)	/* Source Peripheral ID        */
#define DMA_CFG_DSTP(x)		(((x) & 0x1F) << 6)	/* Destination Peripheral ID   */
#define DMA_CFG_FLW_M2M_DMA	(0 << 11)		/* Flow: M to M, Ctrlr: DMA    */
#define DMA_CFG_FLW_M2P_DMA	(1 << 11)		/* Flow: M to P, Ctrlr: DMA    */
#define DMA_CFG_FLW_P2M_DMA	(2 << 11)		/* Flow: P to M, Ctrlr: DMA    */
#define DMA_CFG_FLW_P2P_DMA	(3 << 11)		/* Flow: P to P, Ctrlr: DMA    */
#define DMA_CFG_FLW_P2P_DP	(4 << 11)		/* Flow: P to P, Ctrlr: DST P  */
#define DMA_CFG_FLW_M2P_DP	(5 << 11)		/* Flow: M to P, Ctrlr: DST P  */
#define DMA_CFG_FLW_P2M_SP	(6 << 11)		/* Flow: P to M, Ctrlr: SRC P  */
#define DMA_CFG_FLW_P2P_SP	(7 << 11)		/* Flow: P to P, Ctrlr: SRC P  */
#define DMA_CFG_IE			(1 << 14)		/* Interrupt Error Mask        */
#define DMA_CFG_ITC			(1 << 15)		/* Terminal Count Int. Mask    */
#define DMA_CFG_LOCK		(1 << 16)		/* Enable Locked Transfers     */
#define DMA_CFG_ACTIVE		(1 << 17)		/* Channel Active State Bit    */
#define DMA_CFG_HALT		(1 << 18)		/* Channel Halt State Bit      */

#define DMA_AHB_MASTER_0			0
#define DMA_AHB_MASTER_1			1

#define DMA_TRANSFER_WIDTH_8BIT		0
#define DMA_TRANSFER_WIDTH_16BIT	1
#define DMA_TRANSFER_WIDTH_32BIT	2

#define DMA_BURST_SIZE_1			0
#define DMA_BURST_SIZE_4			1
#define DMA_BURST_SIZE_8			2
#define DMA_BURST_SIZE_16			3
#define DMA_BURST_SIZE_32			4
#define DMA_BURST_SIZE_64			5
#define DMA_BURST_SIZE_128			6
#define DMA_BURST_SIZE_256			7

typedef struct {
	void *		sadr;	/* Channel X Source Address Register           */
	void *		dadr;	/* Channel X Destination Address Register      */
	uint32_t	lli;	/* Channel X Linked List Address Register      */
	uint32_t	cr;		/* Channel X Control Register                  */
	uint32_t	cfg;	/* Channel X Configuration Register            */
} dma_channel_t;

/*
 * This is the first channel of controller 1.
 */
static volatile dma_channel_t *dma_chan = (dma_channel_t *)0x10150100; 

/*
 * Length is in 16-bit words
 */
void dma_copy16 (void *dest, void *src, int len, uint32_t flags)
{
	uint32_t cr;
	uint32_t cfg;

	cr = flags
	   | DMA_CR_SBSIZE(DMA_BURST_SIZE_4)
	   | DMA_CR_DBSIZE(DMA_BURST_SIZE_8)
	   | DMA_CR_SAHBM(DMA_AHB_MASTER_1)
	   | DMA_CR_DAHBM(DMA_AHB_MASTER_1)
	   | DMA_CR_SWIDTH(DMA_TRANSFER_WIDTH_16BIT)
	   | DMA_CR_DWIDTH(DMA_TRANSFER_WIDTH_16BIT);

	cfg = DMA_CFG_FLW_M2M_DMA;

	dma_chan->sadr = src;
	dma_chan->dadr = dest;
	dma_chan->lli  = 0;
	dma_chan->cr   = cr | DMA_CR_TSIZE(len);
	dma_chan->cfg  = cfg | DMA_CFG_ENABLE;

	while (dma_chan->cfg & (DMA_CFG_ACTIVE | DMA_CFG_ENABLE));
}
