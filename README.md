# i5n_converter
 AIS 6 bit character decoder and encoder in C

## Test index
```
DECODING
01000101 45
01000100 44
10110100 b4
 Q(17) T(20) R(18) 4(52)
11000101 c5
01011000 58
00100000 20
 1(49) U(21)  (32)  (32)
decoded: QTR41U  
 17 20 18 52 49 21 32 32
idx=18: R
QTR41U  

ENCODING
 17 Q 00010001
 20 T 00010100
 18 R 00010010
 52 4 00110100
 0x45 0x44 0xb4

 49 1 00110001
 21 U 00010101
 32   00100000
 32   00100000
 0xc5 0x58 0x20

encoded: [0x45 0x44 0xb4 0xc5 0x58 0x20]
```

## Test i5n
```
callsign: QTR41U  
encoded: [0x45 0x44 0xb4 0xc5 0x58 0x20]
17
20
18
52
49
21
32
32
decoded: [QTR41U  ]
```
