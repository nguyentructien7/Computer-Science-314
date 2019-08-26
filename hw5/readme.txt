Problem 1: 
4096 = 2^12 bytes block size
2^4 block address size
I node contains 12 direct blocks, 1 single, double, and triple indirect blocks

2^12 / 2^4 = 2^8 entries in an indirect block

So maximum file size would be:
= (Direct num * Direct Size) + (Entries in indirect * Direct Size) + (Entries in double * Entries in indirect * Direct Size) + (Entries in triple * Entries in double * Entries in indirect * Direct Size)
= (12 * 2^12) + (2^8 * 2^12) + (2^8 * 2^8 * 2^12) + (2^8 * 2^8 * 2^8 * 2^12)
= 3*2^14 + 2^20 + 2^28 + 2^36 = 68989009920 bytes for a maximum file size on an inode