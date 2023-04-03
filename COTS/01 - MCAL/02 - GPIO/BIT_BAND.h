/*************************************************************************************************************************/
/* author : yousef ahmed                                                                                                 */
/* date   : 12/1/2023                                                                                                    */
/* version: V01                                                                                                          */
/*************************************************************************************************************************/ 

#ifndef BIT_BAND_H
#define BIT_BAND_H

// Convert bit-band address and bit number into
// bit-band alias address
#define BIT_BAND(addr,bitnum)      ((addr & 0xF0000000)+0x2000000+((addr & 0xFFFFF)<<5)+(bitnum <<2))
// Convert the address as a pointer
#define MEM_ADDR(addr)            *((volatile unsigned long *) (addr))

#endif