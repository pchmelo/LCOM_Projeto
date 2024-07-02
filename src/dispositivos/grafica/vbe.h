#ifndef __VBE_
#define __VBE_

#define REG86_INTNO 0x10
#define REG86_AH 0x4F
#define REG86_AL 0x02
#define REG86_BX BIT(14)

#define BYTES_NUM_PIXEL(n)  (n +7) / 8;

#define SIZ_COR_PADRAO 32
#define MASK_COR_PADRAO(n) (BIT(n)  -1)

#define VBE_768 0x105   //indexado
#define VBE_480 0x110
#define VBE_600 0x115
#define VBE_1024 0x11A
#define VBE_864 0x14C

#define MODO_VBE_SET 0x4F02
#define LINEAR_VBE_FB BIT(14)

#define DIRETA_COR 0x06
#define INDEXADA_COR 0x105

#define BIOS_SET_MODOVIDEO 0x00
#define BIOS_CARTAIVIDEO_SERV 0x10

#endif
