#ifndef _ACM_LAB_GENERAL_H
#define _ACM_LAB_GENERAL_H

// Interplay ACM signature
#define IP_ACM_SIG 0x01032897

#pragma pack (push, 1)
struct ACM_Header {
	int32_t signature;
	int32_t samples;
	unsigned short channels;
	unsigned short rate;
	unsigned short levels : 4;
	unsigned short subblocks : 12;
};
#pragma pack (pop)

#endif
