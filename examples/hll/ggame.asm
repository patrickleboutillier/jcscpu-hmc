PROGMEM const byte prog[] = {
  /* addr   0 */ DATA(R0, 10),   // (00001010)
  /* addr   2 */ DATA(R1, 255),  // (11111111)
  /* addr   4 */ ST(R1, R0),     
  /* addr   5 */ DATA(R0, 255),  // (11111111)
  /* addr   7 */ DATA(R1, 254),  // (11111110)
  /* addr   9 */ ST(R1, R0),     
  /* addr  10 */ DATA(R0, 0),    // (00000000)
  /* addr  12 */ DATA(R1, 252),  // (11111100)
  /* addr  14 */ ST(R1, R0),     
  /* addr  15 */ DATA(R0, 1),    // (00000001)
  /* addr  17 */ DATA(R1, 251),  // (11111011)
  /* addr  19 */ ST(R1, R0),     
  /* addr  20 */ // Label 'WHILE20'
  /* addr  20 */ DATA(R0, 251),  // (11111011)
  /* addr  22 */ LD(R0, R0),     
  /* addr  23 */ OR(R0, R0),     
  /* addr  24 */ JZ(234),   // (@ELSE24)
  /* addr  26 */ // guess
  /* addr  26 */ DATA(R0, 254),  // (11111110)
  /* addr  28 */ LD(R0, R0),     
  /* addr  29 */ DATA(R1, 252),  // (11111100)
  /* addr  31 */ LD(R1, R1),     
  /* addr  32 */ NOT(R1, R1),    
  /* addr  33 */ DATA(R2, 1),    // (00000001)
  /* addr  35 */ CLF,            
  /* addr  36 */ ADD(R2, R1),    
  /* addr  37 */ CLF,            
  /* addr  38 */ ADD(R0, R1),    
  /* addr  39 */ DATA(R0, 250),  // (11111010)
  /* addr  41 */ ST(R0, R1),     
  /* addr  42 */ DATA(R1, 250),  // (11111010)
  /* addr  44 */ LD(R1, R0),     
  /* addr  45 */ SHR(R0, R0),    
  /* addr  46 */ ST(R1, R0),     
  /* addr  47 */ DATA(R0, 252),  // (11111100)
  /* addr  49 */ LD(R0, R0),     
  /* addr  50 */ DATA(R1, 250),  // (11111010)
  /* addr  52 */ LD(R1, R1),     
  /* addr  53 */ CLF,            
  /* addr  54 */ ADD(R0, R1),    
  /* addr  55 */ DATA(R0, 253),  // (11111101)
  /* addr  57 */ ST(R0, R1),     
  /* addr  58 */ DATA(R0, 253),  // (11111101)
  /* addr  60 */ LD(R0, R0),     
  /* addr  61 */ XOR(R1, R1),    
  /* addr  62 */ OUTA(R1),       
  /* addr  63 */ OUTD(R0),       
  /* addr  64 */ DATA(R0, 63),   // (00111111)
  /* addr  66 */ DATA(R1, 249),  // (11111001)
  /* addr  68 */ ST(R1, R0),     
  /* addr  69 */ DATA(R0, 249),  // (11111001)
  /* addr  71 */ LD(R0, R0),     
  /* addr  72 */ XOR(R1, R1),    
  /* addr  73 */ OUTA(R1),       
  /* addr  74 */ OUTD(R0),       
  /* addr  75 */ DATA(R0, 255),  // (11111111)
  /* addr  77 */ LD(R0, R0),     
  /* addr  78 */ XOR(R1, R1),    
  /* addr  79 */ OUTA(R1),       
  /* addr  80 */ OUTD(R0),       
  /* addr  81 */ // Get char
  /* addr  81 */ DATA(R0, 0),    // (00000000)
  /* addr  83 */ DATA(R1, 248),  // (11111000)
  /* addr  85 */ ST(R1, R0),     
  /* addr  86 */ DATA(R0, 0),    // (00000000)
  /* addr  88 */ DATA(R1, 247),  // (11110111)
  /* addr  90 */ ST(R1, R0),     
  /* addr  91 */ DATA(R0, 247),  // (11110111)
  /* addr  93 */ LD(R0, R0),     
  /* addr  94 */ DATA(R1, 248),  // (11111000)
  /* addr  96 */ LD(R1, R1),     
  /* addr  97 */ DATA(R2, 1),    // (00000001)
  /* addr  99 */ CMP(R0, R1),    
  /* addr 100 */ JE(103),    // (@EQ100)
  /* addr 102 */ XOR(R2, R2),    
  /* addr 103 */ // Label 'EQ100'
  /* addr 103 */ DATA(R0, 246),  // (11110110)
  /* addr 105 */ ST(R0, R2),     
  /* addr 106 */ // Label 'WHILE106'
  /* addr 106 */ DATA(R0, 246),  // (11110110)
  /* addr 108 */ LD(R0, R0),     
  /* addr 109 */ OR(R0, R0),     
  /* addr 110 */ JZ(120),  // (@ELSE110)
  /* addr 112 */ XOR(R0, R0),    
  /* addr 113 */ OUTA(R0),       
  /* addr 114 */ IND(R0),        
  /* addr 115 */ DATA(R1, 247),  // (11110111)
  /* addr 117 */ ST(R1, R0),     
  /* addr 118 */ // GOTO @FI110
  /* addr 118 */ JMP(122),   // (@FI110)
  /* addr 120 */ // Label 'ELSE110'
  /* addr 120 */ // GOTO @ELIHW106
  /* addr 120 */ JMP(124),  // (@ELIHW106)
  /* addr 122 */ // Label 'FI110'
  /* addr 122 */ // GOTO @WHILE106
  /* addr 122 */ JMP(106),  // (@WHILE106)
  /* addr 124 */ // Label 'ELIHW106'
  /* addr 124 */ // Check char
  /* addr 124 */ DATA(R0, 104),  // (01101000)
  /* addr 126 */ DATA(R1, 245),  // (11110101)
  /* addr 128 */ ST(R1, R0),     
  /* addr 129 */ DATA(R0, 247),  // (11110111)
  /* addr 131 */ LD(R0, R0),     
  /* addr 132 */ DATA(R1, 245),  // (11110101)
  /* addr 134 */ LD(R1, R1),     
  /* addr 135 */ DATA(R2, 1),    // (00000001)
  /* addr 137 */ CMP(R0, R1),    
  /* addr 138 */ JE(141),    // (@EQ138)
  /* addr 140 */ XOR(R2, R2),    
  /* addr 141 */ // Label 'EQ138'
  /* addr 141 */ DATA(R0, 244),  // (11110100)
  /* addr 143 */ ST(R0, R2),     
  /* addr 144 */ DATA(R0, 244),  // (11110100)
  /* addr 146 */ LD(R0, R0),     
  /* addr 147 */ OR(R0, R0),     
  /* addr 148 */ JZ(156),    // (@FI148)
  /* addr 150 */ DATA(R0, 253),  // (11111101)
  /* addr 152 */ LD(R0, R0),     
  /* addr 153 */ DATA(R1, 252),  // (11111100)
  /* addr 155 */ ST(R1, R0),     
  /* addr 156 */ // Label 'FI148'
  /* addr 156 */ DATA(R0, 108),  // (01101100)
  /* addr 158 */ DATA(R1, 243),  // (11110011)
  /* addr 160 */ ST(R1, R0),     
  /* addr 161 */ DATA(R0, 247),  // (11110111)
  /* addr 163 */ LD(R0, R0),     
  /* addr 164 */ DATA(R1, 243),  // (11110011)
  /* addr 166 */ LD(R1, R1),     
  /* addr 167 */ DATA(R2, 1),    // (00000001)
  /* addr 169 */ CMP(R0, R1),    
  /* addr 170 */ JE(173),    // (@EQ170)
  /* addr 172 */ XOR(R2, R2),    
  /* addr 173 */ // Label 'EQ170'
  /* addr 173 */ DATA(R0, 242),  // (11110010)
  /* addr 175 */ ST(R0, R2),     
  /* addr 176 */ DATA(R0, 242),  // (11110010)
  /* addr 178 */ LD(R0, R0),     
  /* addr 179 */ OR(R0, R0),     
  /* addr 180 */ JZ(188),    // (@FI180)
  /* addr 182 */ DATA(R0, 253),  // (11111101)
  /* addr 184 */ LD(R0, R0),     
  /* addr 185 */ DATA(R1, 254),  // (11111110)
  /* addr 187 */ ST(R1, R0),     
  /* addr 188 */ // Label 'FI180'
  /* addr 188 */ DATA(R0, 61),   // (00111101)
  /* addr 190 */ DATA(R1, 241),  // (11110001)
  /* addr 192 */ ST(R1, R0),     
  /* addr 193 */ DATA(R0, 247),  // (11110111)
  /* addr 195 */ LD(R0, R0),     
  /* addr 196 */ DATA(R1, 241),  // (11110001)
  /* addr 198 */ LD(R1, R1),     
  /* addr 199 */ DATA(R2, 1),    // (00000001)
  /* addr 201 */ CMP(R0, R1),    
  /* addr 202 */ JE(205),    // (@EQ202)
  /* addr 204 */ XOR(R2, R2),    
  /* addr 205 */ // Label 'EQ202'
  /* addr 205 */ DATA(R0, 240),  // (11110000)
  /* addr 207 */ ST(R0, R2),     
  /* addr 208 */ DATA(R0, 240),  // (11110000)
  /* addr 210 */ LD(R0, R0),     
  /* addr 211 */ OR(R0, R0),     
  /* addr 212 */ JZ(232),    // (@FI212)
  /* addr 214 */ DATA(R0, 33),   // (00100001)
  /* addr 216 */ DATA(R1, 239),  // (11101111)
  /* addr 218 */ ST(R1, R0),     
  /* addr 219 */ DATA(R0, 239),  // (11101111)
  /* addr 221 */ LD(R0, R0),     
  /* addr 222 */ XOR(R1, R1),    
  /* addr 223 */ OUTA(R1),       
  /* addr 224 */ OUTD(R0),       
  /* addr 225 */ DATA(R0, 255),  // (11111111)
  /* addr 227 */ LD(R0, R0),     
  /* addr 228 */ XOR(R1, R1),    
  /* addr 229 */ OUTA(R1),       
  /* addr 230 */ OUTD(R0),       
  /* addr 231 */ HALT,           
  /* addr 232 */ // Label 'FI212'
  /* addr 232 */ // GOTO @FI24
  /* addr 232 */ JMP(236),    // (@FI24)
  /* addr 234 */ // Label 'ELSE24'
  /* addr 234 */ // GOTO @ELIHW20
  /* addr 234 */ JMP(238),  // (@ELIHW20)
  /* addr 236 */ // Label 'FI24'
  /* addr 236 */ // GOTO @WHILE20
  /* addr 236 */ JMP(20),  // (@WHILE20)
  /* addr 238 */ // Label 'ELIHW20'
} ;
