/*
* Copyright (C) 2020-2021 Intel Corporation.
*
* This software and the related documents are Intel copyrighted materials,
* and your use of them is governed by the express license under which they
* were provided to you ("License").
* Unless the License provides otherwise, you may not use, modify, copy,
* publish, distribute, disclose or transmit this software or the related
* documents without Intel's prior written permission.
*
* This software and the related documents are provided as is, with no
* express or implied warranties, other than those that are expressly stated
* in the License.
*
*/

/*
 * st_pkt.h
 *
 *
 */

#ifndef _ST_PKT_H_
#define _ST_PKT_H_
#include <rte_ether.h>
#include <rte_flow.h>
#include <rte_ip.h>

#include "st_api.h"
#include "st_pack.h"

#include <stdint.h>

#ifndef __LITTLE_ENDIAN_BITFIELDS
#define __LITTLE_ENDIAN_BITFIELDS 1
#endif

#define NFIELD_MASK_15_BITS(field) (0xff7f & field)
#define HFIELD_MASK_15_BITS(field) (0x7fff & field)
#define NFIELD_TEST_16_BIT(field) (0x0080 & field)
#define HFIELD_TEST_16_BIT(field) (0x8000 & field)
#define NFIELD_GET_16_BIT(field) ((0x0080 & field) >> 7)
#define HFIELD_GET_16_BIT(field) ((0x8000 & field) >> 15)

struct st_file_422_10be
{
	uint16_t CB;
	uint16_t Y0;
	uint16_t CR;
	uint16_t Y1;
} __attribute__((__packed__));

typedef struct st_file_422_10be st_file_422_10be_t;

struct st_rfc4175_rtp_single_hdr
{
#ifdef __LITTLE_ENDIAN_BITFIELDS
	uint8_t csrcCount : 4;
	uint8_t extension : 1;
	uint8_t padding : 1;
	uint8_t version : 2;
	uint8_t payloadType : 7;
	uint8_t marker : 1;
#else
	uint8_t version : 2;
	uint8_t padding : 1;
	uint8_t extension : 1;
	uint8_t csrcCount : 4;
	uint8_t marker : 1;
	uint8_t payloadType : 7;
#endif
	uint16_t seqNumber;
	uint32_t tmstamp;
	uint32_t ssrc;
	uint16_t seqNumberExt;
	uint16_t line1Length;
	uint16_t line1Number;
	uint16_t line1Offset;
} __attribute__((__packed__));
typedef struct st_rfc4175_rtp_single_hdr st_rfc4175_rtp_single_hdr_t;

struct st_rfc4175_rtp_dual_hdr
{
#ifdef __LITTLE_ENDIAN_BITFIELDS
	uint8_t csrcCount : 4;
	uint8_t extension : 1;
	uint8_t padding : 1;
	uint8_t version : 2;
	uint8_t payloadType : 7;
	uint8_t marker : 1;
#else
	uint8_t version : 2;
	uint8_t padding : 1;
	uint8_t extension : 1;
	uint8_t csrcCount : 4;
	uint8_t marker : 1;
	uint8_t payloadType : 7;
#endif
	uint16_t seqNumber;
	uint32_t tmstamp;
	uint32_t ssrc;
	uint16_t seqNumberExt;
	uint16_t line1Length;
	uint16_t line1Number;
	uint16_t line1Offset;
	uint16_t line2Length;
	uint16_t line2Number;
	uint16_t line2Offset;
} __attribute__((__packed__));
typedef struct st_rfc4175_rtp_dual_hdr st_rfc4175_rtp_dual_hdr_t;

struct st_rfc4175_pkt_dual
{
	struct rte_ether_hdr eth;
	struct rte_ipv4_hdr ip;
	struct rte_udp_hdr udp;
	struct st_rfc4175_rtp_dual_hdr rtp;
} __attribute__((__packed__)) __rte_aligned(2);

typedef struct st_rfc4175_pkt_dual st_rfc4175_pkt_dual_t;

struct st_rfc4175_pkt_single
{
	struct rte_ether_hdr eth;
	struct rte_ipv4_hdr ip;
	struct rte_udp_hdr udp;
	struct st_rfc4175_rtp_single_hdr rtp;
} __attribute__((__packed__)) __rte_aligned(2);

typedef struct st_rfc4175_pkt_single st_rfc4175_pkt_single_t;

struct st_rfc3550_audio_hdr
{
#ifdef __LITTLE_ENDIAN_BITFIELDS
	uint8_t csrcCount : 4;
	uint8_t extension : 1;
	uint8_t padding : 1;
	uint8_t version : 2;
	uint8_t payloadType : 7;
	uint8_t marker : 1;
#else
	uint8_t version : 2;
	uint8_t padding : 1;
	uint8_t extension : 1;
	uint8_t csrcCount : 4;
	uint8_t marker : 1;
	uint8_t payloadType : 7;
#endif
	uint16_t seqNumber;
	uint32_t tmstamp;
	uint32_t ssrc;
} __attribute__((__packed__));
typedef struct st_rfc3550_audio_hdr st_rfc3550_audio_hdr_t;

struct st_rfc3550_pkt_audio
{
	struct rte_ether_hdr eth;
	struct rte_ipv4_hdr ip;
	struct rte_udp_hdr udp;
	st_rfc3550_audio_hdr_t rtp;
} __attribute__((__packed__)) __rte_aligned(2);

typedef struct st_rfc3550_pkt_audio st_rfc3550_pkt_audio_t;

/*
*	Ancillary data packet header (RFC 8331)
*/
struct st_rfc8331_anc_rtp_hdr
{
#ifdef __LITTLE_ENDIAN_BITFIELDS
	uint8_t csrcCount : 4;
	uint8_t extension : 1;
	uint8_t padding : 1;
	uint8_t version : 2;
	uint8_t payloadType : 7;
	uint8_t marker : 1;
#else
	uint8_t version : 2;
	uint8_t padding : 1;
	uint8_t extension : 1;
	uint8_t csrcCount : 4;
	uint8_t marker : 1;
	uint8_t payloadType : 7;
#endif
	uint16_t seqNumber;
	uint32_t tmstamp;
	uint32_t ssrc;
	uint16_t seqNumberExt;
	uint16_t length;

	struct
	{
		uint32_t ancCount : 8;
		uint32_t f : 2;
		uint32_t reserved : 22;
	};
} __attribute__((__packed__));

typedef struct st_rfc8331_anc_rtp_hdr st_rfc8331_anc_rtp_hdr_t;

struct st_rfc8331_pkt_anc
{
	struct rte_ether_hdr eth;
	struct rte_ipv4_hdr ip;
	struct rte_udp_hdr udp;
	st_rfc8331_anc_rtp_hdr_t rtp;
} __attribute__((__packed__)) __rte_aligned(2);
;

typedef struct st_rfc8331_pkt_anc st_rfc8331_pkt_anc_t;

/**
 * Union to keep pktHdr template on each session
 */
union st_pkt_hdr
{
	st_rfc4175_pkt_dual_t dualHdr;
	st_rfc4175_pkt_single_t singleHdr;
	st_rfc3550_pkt_audio_t audioHdr;
	st_rfc8331_pkt_anc_t ancillaryHdr;
};

/*
0               1               2               3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| R00 (8 bits)  | Y00 (8 bits) | CR00 (8 bits)|
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
struct st_rfc4175_rgb_8_pg1
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} __attribute__((__packed__));

#define ST_KNI_THEARD (2)

#define RVRTP_VERSION_2 2
#define RVRTP_PAYLOAD_TYPE_RAW_VIDEO 112
#define RARTP_PAYLOAD_TYPE_PCM_AUDIO 111
#define RANCRTP_PAYLOAD_TYPE_ANCILLARY 113	// Need to check that in documenation

#define ST_PKT_AUDIO_HDR_LEN (sizeof(st_rfc3550_pkt_audio_t))
#define ST_AUDIO_PKT_SURROUND71_PCM24 (ST_PKT_AUDIO_HDR_LEN + 8 * 3 * 48)
#define ST_AUDIO_PKT_SURROUND71_PCM16 (ST_PKT_AUDIO_HDR_LEN + 8 * 2 * 48)
#define ST_AUDIO_PKT_SURROUND71_PCM8 (ST_PKT_AUDIO_HDR_LEN + 8 * 1 * 48)
#define ST_AUDIO_PKT_SURROUND51_PCM24 (ST_PKT_AUDIO_HDR_LEN + 6 * 3 * 48)
#define ST_AUDIO_PKT_SURROUND51_PCM16 (ST_PKT_AUDIO_HDR_LEN + 6 * 2 * 48)
#define ST_AUDIO_PKT_SURROUND51_PCM8 (ST_PKT_AUDIO_HDR_LEN + 6 * 1 * 48)
#define ST_AUDIO_PKT_STEREO_PCM16 (ST_PKT_AUDIO_HDR_LEN + 2 * 2 * 48)
#define ST_MIN_AUDIO_PKT_SIZE (ST_PKT_AUDIO_HDR_LEN + 48)
#define ST_MAX_AUDIO_PKT_SIZE (1500 - ST_PKT_AUDIO_HDR_LEN)

#define ST_NIC_RATE_SPEED_10GBPS (10)
#define ST_NIC_RATE_SPEED_25GBPS (25)
#define ST_NIC_RATE_SPEED_40GBPS (40)
#define ST_NIC_RATE_SPEED_100GBPS (100)

#define ST_DEFAULT_PKTS_IN_LN 4
#define ST_FMT_HD720_PKTS_IN_DLN 5
#define ST_FMT_HD720_PKTS_IN_SLN 3
#define ST_FMT_HD1080_PKTS_IN_SLN 4
#define ST_FMT_HD1080_PKTS_IN_DLN 8
#define ST_FMT_UHD2160_PKTS_IN_SLN 16

#define ST_FMT_HD1080_PKT_DLN_SZ 600
#define ST_FMT_HD720_PKT_DLN_SZ 1280
#define ST_FMT_HD720_PKT_SLN_SZ 1200
#define ST_FMT_HD720_PKT_HLN_SZ 800
#define ST_FMT_UHD2160_PKT_SLN_SZ 1200
#define ST_FMT_HD1080_PKT_SLN_SZ 1200

#define ST_PKT_SLN_HDR_LEN (14 + 20 + 8 + sizeof(st_rfc4175_rtp_single_hdr_t))
#define ST_HD_SLN_RGB_480_PIXELS (ST_PKT_SLN_HDR_LEN + sizeof(struct st_rfc4175_rgb_8_pg1) * 480)
#define ST_HD_SLN_422_10_480_PIXELS (ST_PKT_SLN_HDR_LEN + sizeof(st_rfc4175_422_10_pg2_t) * 240)

#define ST_ANC_ALL_HDR_LEN (14 + 20 + 8 + sizeof(st_rfc8331_anc_rtp_hdr_t))
#define ST_ANC_UDW_MAX_SIZE 255 * 10 / 8
#define ST_ANC_RTP_PKT_MAX_LEN (1500 - ST_ANC_ALL_HDR_LEN)

#define ST_MIN_VALID_PKT_SIZE ST_HD_SLN_422_10_480_PIXELS
#define ST_DEFAULT_LEFT_BYTES_720P (2 * (ST_FMT_HD720_PKT_SLN_SZ - ST_FMT_HD720_PKT_HLN_SZ))

#define ST_PKT_DLN_HDR_LEN (14 + 20 + 8 + sizeof(st_rfc4175_rtp_dual_hdr_t))
#define ST_HD_DLN_422_10_276_PIXELS (ST_PKT_DLN_HDR_LEN + sizeof(st_rfc4175_422_10_pg2_t) * 276)
#define ST_HD_DLN_422_10_256_PIXELS (ST_PKT_DLN_HDR_LEN + sizeof(st_rfc4175_422_10_pg2_t) * 256)
#define ST_HD_DLN_422_10_240_PIXELS (ST_PKT_DLN_HDR_LEN + sizeof(st_rfc4175_422_10_pg2_t) * 240)
#define ST_UD_DLN_422_10_960_PIXELS (ST_PKT_DLN_HDR_LEN + sizeof(st_rfc4175_422_10_pg2_t) * 960)
#define ST_HD_DLN_DEFAULT_PKT_SZ ST_HD_DLN_422_10_240_PIXELS

#define ST_MIN_PKT_SIZE 60
#define ST_PHYS_PKT_ADD 24
#define ST_MIN_PKT_L1_SZ (ST_MIN_PKT_SIZE + ST_PHYS_PKT_ADD)

#define ST_DEFAULT_PKT_L1_SZ (1514 + ST_PHYS_PKT_ADD)
#define ST_HD_422_10_SLN_L1_SZ (ST_HD_SLN_422_10_480_PIXELS + ST_PHYS_PKT_ADD)

#define ST_FRAME_TIME_DEFAULTx100 (3336666667)
#define ST_FRAME_TIME_DEFAULTx40 (1334666667)
#define ST_FRAME_TIME_DEFAULTx25 (834166667)
#define ST_FRAME_TIME_DEFAULTx10 (333666667)
#define ST_DENOM_DEFAULT (10000)

#define ST_ADJUST_10GBPS (10000)
#define ST_ADJUST_25GBPS (10000)
#define ST_ADJUST_40GBPS (10000)
#define ST_ADJUST_100GBPS (9846)  // 98.46Gbps

#define ST_DEFAULT_PKTS_IN_FRAME_LINEAR (4320)
#define ST_DEFAULT_PKTS_IN_FRAME_GAPPED (4500)

///////////////////////////////////////////////////////////////////////
#define NIC_RATE_SPEED_COUNT 4

typedef uint32_t (*st_nic_enq_threads_fn)(st_pacing_type_t pacing, uint32_t snCount);

typedef struct st_nic_rate_params
{
	uint8_t nicSpeed;
	uint8_t maxSt21Sn25Fps;
	uint8_t maxSt21Sn29Fps;
	uint8_t maxSt21Sn50Fps;
	uint8_t maxSt21Sn59Fps;
	uint8_t maxTxRings;
	uint8_t maxRxRings;
	uint8_t maxSchThrds;
	uint8_t maxEnqThrds;
	uint8_t maxRcvThrds;
	uint8_t maxAudioRcvThrds;
	uint8_t maxAncRcvThrds;
	uint8_t maxTxBulkNum; /* The number of objects for each dequeue, 1, 2 or 4 */
	/* function to get the number of enqueue threads for required sn count and pacing type */
	st_nic_enq_threads_fn fnGetEnqThrds;
} st_nic_rate_params_t;

typedef struct
{
	uint64_t pktRx;
	uint64_t pktDrop;
	uint64_t pktInvalid;
	uint64_t pkTx;
	uint32_t threadId;
	st_essence_type_t sn_type;
	uint16_t portP;
	uint16_t portR;
	uint16_t qPcount;
	uint16_t qRcount;
	uint16_t queueP[8];
	uint16_t queueR[8];
} userargs_t;

#define ST_MAX_SESSIONS_25FPS_10GBPS 8
#define ST_MAX_SESSIONS_29FPS_10GBPS 6
#define ST_MAX_SESSIONS_50FPS_10GBPS 4
#define ST_MAX_SESSIONS_59FPS_10GBPS 3
#define ST_MAX_ENQ_THREADS_10GBPS 1
#define ST_MAX_RCV_THREADS_10GBPS 1
#define ST_MAX_AUDIO_RCV_THREADS_10GBPS 1
#define ST_MAX_ANC_RCV_THREADS_10GBPS 1
#define ST_MAX_TX_RINGS_10GBPS 1
#define ST_MAX_RX_RINGS_10GBPS (1 + ST_MAX_RCV_THREADS_10GBPS)
#define ST_MAX_SCH_THREADS_10GBPS ST_MAX_TX_RINGS_10GBPS
#define ST_MAX_TX_BULK_NUM_10GBPS 2

#define ST_MAX_SESSIONS_25FPS_25GBPS 20
#define ST_MAX_SESSIONS_29FPS_25GBPS 16
#define ST_MAX_SESSIONS_50FPS_25GBPS 10
#define ST_MAX_SESSIONS_59FPS_25GBPS 8
#define ST_MAX_TX_RINGS_25GBPS 1
#define ST_MAX_ENQ_THREADS_25GBPS 2
#define ST_MAX_RCV_THREADS_25GBPS 2
#define ST_MAX_AUDIO_RCV_THREADS_25GBPS 1
#define ST_MAX_ANC_RCV_THREADS_25GBPS 1
#define ST_MAX_RX_RINGS_25GBPS (1 + ST_MAX_RCV_THREADS_25GBPS)
#define ST_MAX_SCH_THREADS_25GBPS ST_MAX_TX_RINGS_25GBPS
#define ST_MAX_TX_BULK_NUM_25GBPS 2

#define ST_MAX_SESSIONS_25FPS_40GBPS 32
#define ST_MAX_SESSIONS_29FPS_40GBPS 28
#define ST_MAX_SESSIONS_50FPS_40GBPS 16
#define ST_MAX_SESSIONS_59FPS_40GBPS 14
#define ST_MAX_TX_RINGS_40GBPS 1
#define ST_MAX_ENQ_THREADS_40GBPS 2
#define ST_MAX_RCV_THREADS_40GBPS 4
#define ST_MAX_AUDIO_RCV_THREADS_40GBPS 1
#define ST_MAX_ANC_RCV_THREADS_40GBPS 1
#define ST_MAX_SCH_THREADS_40GBPS ST_MAX_TX_RINGS_40GBPS
#define ST_MAX_RX_RINGS_40GBPS (1 + ST_MAX_RCV_THREADS_40GBPS)
#define ST_MAX_TX_BULK_NUM_40GBPS 2

#define ST_MAX_SESSIONS_25FPS_100GBPS 80
#define ST_MAX_SESSIONS_29FPS_100GBPS 64
#define ST_MAX_SESSIONS_50FPS_100GBPS 40
#define ST_MAX_SESSIONS_59FPS_100GBPS 32
#define ST_MAX_TX_RINGS_100GBPS 2
#define ST_MAX_ENQ_THREADS_100GBPS 4
#define ST_MAX_RCV_THREADS_100GBPS 8
#define ST_MAX_AUDIO_RCV_THREADS_100GBPS 2
#define ST_MAX_ANC_RCV_THREADS_100GBPS 2
#define ST_MAX_SCH_THREADS_100GBPS ST_MAX_TX_RINGS_100GBPS
#define ST_MAX_RX_RINGS_100GBPS (1 + ST_MAX_RCV_THREADS_100GBPS)
#define ST_MAX_TX_BULK_NUM_100GBPS 4

///////////////////////////////////////////////////////////////////////

#define ST_DEQUEUE_BULK

#define ST_MAX_ENQ_THREADS_MAX 8
#define ST_MAX_RCV_THREADS_MAX 8
#define ST_ANC_MAX_RCV_THREADS_MAX 2
#define ST_AUDIO_MAX_RCV_THREADS_MAX 2
#define ST_MAX_SESSIONS_MAX 160

#define RX_BURTS_SIZE 128  //64

#define ST_MAX_PTP_FLOWS 1
#define ST_MAX_FLOWS (2 * ST_MAX_SESSIONS_MAX + 2 * ST_MAX_PTP_FLOWS)

#define ST_PKTS_LOSS_ALLOWED (ST_DEFAULT_PKTS_IN_FRAME_LINEAR / 4)

#define ST_FLOW_CLASS_IN_HW

#define ST_CLOCK_PRECISION_TIME 40000ul

#define ST_VRX_FULL_NARROW	(9) /* Pass criteria for narrow */
#define ST_VRX_FULL_WIDE	(863) /* Pass criteria for wide */

#endif /* ST_PKT_H_ */
