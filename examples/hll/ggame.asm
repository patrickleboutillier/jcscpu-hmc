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
  /* addr  24 */ JZ(235),   // (@ELSE24)
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
  /* addr  61 */ DATA(R1, 1),    // (00000001)
  /* addr  63 */ OUTA(R1),       
  /* addr  64 */ OUTD(R0),       
  /* addr  65 */ DATA(R0, 63),   // (00111111)
  /* addr  67 */ DATA(R1, 249),  // (11111001)
  /* addr  69 */ ST(R1, R0),     
  /* addr  70 */ DATA(R0, 249),  // (11111001)
  /* addr  72 */ LD(R0, R0),     
  /* addr  73 */ XOR(R1, R1),    
  /* addr  74 */ OUTA(R1),       
  /* addr  75 */ OUTD(R0),       
  /* addr  76 */ DATA(R0, 255),  // (11111111)
  /* addr  78 */ LD(R0, R0),     
  /* addr  79 */ XOR(R1, R1),    
  /* addr  80 */ OUTA(R1),       
  /* addr  81 */ OUTD(R0),       
  /* addr  82 */ // Get char
  /* addr  82 */ DATA(R0, 0),    // (00000000)
  /* addr  84 */ DATA(R1, 248),  // (11111000)
  /* addr  86 */ ST(R1, R0),     
  /* addr  87 */ DATA(R0, 0),    // (00000000)
  /* addr  89 */ DATA(R1, 247),  // (11110111)
  /* addr  91 */ ST(R1, R0),     
  /* addr  92 */ DATA(R0, 247),  // (11110111)
  /* addr  94 */ LD(R0, R0),     
  /* addr  95 */ DATA(R1, 248),  // (11111000)
  /* addr  97 */ LD(R1, R1),     
  /* addr  98 */ DATA(R2, 1),    // (00000001)
  /* addr 100 */ CMP(R0, R1),    
  /* addr 101 */ JE(104),    // (@EQ101)
  /* addr 103 */ XOR(R2, R2),    
  /* addr 104 */ // Label 'EQ101'
  /* addr 104 */ DATA(R0, 246),  // (11110110)
  /* addr 106 */ ST(R0, R2),     
  /* addr 107 */ // Label 'WHILE107'
  /* addr 107 */ DATA(R0, 246),  // (11110110)
  /* addr 109 */ LD(R0, R0),     
  /* addr 110 */ OR(R0, R0),     
  /* addr 111 */ JZ(121),  // (@ELSE111)
  /* addr 113 */ XOR(R0, R0),    
  /* addr 114 */ OUTA(R0),       
  /* addr 115 */ IND(R0),        
  /* addr 116 */ DATA(R1, 247),  // (11110111)
  /* addr 118 */ ST(R1, R0),     
  /* addr 119 */ // GOTO @FI111
  /* addr 119 */ JMP(123),   // (@FI111)
  /* addr 121 */ // Label 'ELSE111'
  /* addr 121 */ // GOTO @ELIHW107
  /* addr 121 */ JMP(125),  // (@ELIHW107)
  /* addr 123 */ // Label 'FI111'
  /* addr 123 */ // GOTO @WHILE107
  /* addr 123 */ JMP(107),  // (@WHILE107)
  /* addr 125 */ // Label 'ELIHW107'
  /* addr 125 */ // Check char
  /* addr 125 */ DATA(R0, 104),  // (01101000)
  /* addr 127 */ DATA(R1, 245),  // (11110101)
  /* addr 129 */ ST(R1, R0),     
  /* addr 130 */ DATA(R0, 247),  // (11110111)
  /* addr 132 */ LD(R0, R0),     
  /* addr 133 */ DATA(R1, 245),  // (11110101)
  /* addr 135 */ LD(R1, R1),     
  /* addr 136 */ DATA(R2, 1),    // (00000001)
  /* addr 138 */ CMP(R0, R1),    
  /* addr 139 */ JE(142),    // (@EQ139)
  /* addr 141 */ XOR(R2, R2),    
  /* addr 142 */ // Label 'EQ139'
  /* addr 142 */ DATA(R0, 244),  // (11110100)
  /* addr 144 */ ST(R0, R2),     
  /* addr 145 */ DATA(R0, 244),  // (11110100)
  /* addr 147 */ LD(R0, R0),     
  /* addr 148 */ OR(R0, R0),     
  /* addr 149 */ JZ(157),    // (@FI149)
  /* addr 151 */ DATA(R0, 253),  // (11111101)
  /* addr 153 */ LD(R0, R0),     
  /* addr 154 */ DATA(R1, 252),  // (11111100)
  /* addr 156 */ ST(R1, R0),     
  /* addr 157 */ // Label 'FI149'
  /* addr 157 */ DATA(R0, 108),  // (01101100)
  /* addr 159 */ DATA(R1, 243),  // (11110011)
  /* addr 161 */ ST(R1, R0),     
  /* addr 162 */ DATA(R0, 247),  // (11110111)
  /* addr 164 */ LD(R0, R0),     
  /* addr 165 */ DATA(R1, 243),  // (11110011)
  /* addr 167 */ LD(R1, R1),     
  /* addr 168 */ DATA(R2, 1),    // (00000001)
  /* addr 170 */ CMP(R0, R1),    
  /* addr 171 */ JE(174),    // (@EQ171)
  /* addr 173 */ XOR(R2, R2),    
  /* addr 174 */ // Label 'EQ171'
  /* addr 174 */ DATA(R0, 242),  // (11110010)
  /* addr 176 */ ST(R0, R2),     
  /* addr 177 */ DATA(R0, 242),  // (11110010)
  /* addr 179 */ LD(R0, R0),     
  /* addr 180 */ OR(R0, R0),     
  /* addr 181 */ JZ(189),    // (@FI181)
  /* addr 183 */ DATA(R0, 253),  // (11111101)
  /* addr 185 */ LD(R0, R0),     
  /* addr 186 */ DATA(R1, 254),  // (11111110)
  /* addr 188 */ ST(R1, R0),     
  /* addr 189 */ // Label 'FI181'
  /* addr 189 */ DATA(R0, 61),   // (00111101)
  /* addr 191 */ DATA(R1, 241),  // (11110001)
  /* addr 193 */ ST(R1, R0),     
  /* addr 194 */ DATA(R0, 247),  // (11110111)
  /* addr 196 */ LD(R0, R0),     
  /* addr 197 */ DATA(R1, 241),  // (11110001)
  /* addr 199 */ LD(R1, R1),     
  /* addr 200 */ DATA(R2, 1),    // (00000001)
  /* addr 202 */ CMP(R0, R1),    
  /* addr 203 */ JE(206),    // (@EQ203)
  /* addr 205 */ XOR(R2, R2),    
  /* addr 206 */ // Label 'EQ203'
  /* addr 206 */ DATA(R0, 240),  // (11110000)
  /* addr 208 */ ST(R0, R2),     
  /* addr 209 */ DATA(R0, 240),  // (11110000)
  /* addr 211 */ LD(R0, R0),     
  /* addr 212 */ OR(R0, R0),     
  /* addr 213 */ JZ(233),    // (@FI213)
  /* addr 215 */ DATA(R0, 33),   // (00100001)
  /* addr 217 */ DATA(R1, 239),  // (11101111)
  /* addr 219 */ ST(R1, R0),     
  /* addr 220 */ DATA(R0, 239),  // (11101111)
  /* addr 222 */ LD(R0, R0),     
  /* addr 223 */ XOR(R1, R1),    
  /* addr 224 */ OUTA(R1),       
  /* addr 225 */ OUTD(R0),       
  /* addr 226 */ DATA(R0, 255),  // (11111111)
  /* addr 228 */ LD(R0, R0),     
  /* addr 229 */ XOR(R1, R1),    
  /* addr 230 */ OUTA(R1),       
  /* addr 231 */ OUTD(R0),       
  /* addr 232 */ HALT,           
  /* addr 233 */ // Label 'FI213'
  /* addr 233 */ // GOTO @FI24
  /* addr 233 */ JMP(237),    // (@FI24)
  /* addr 235 */ // Label 'ELSE24'
  /* addr 235 */ // GOTO @ELIHW20
  /* addr 235 */ JMP(239),  // (@ELIHW20)
  /* addr 237 */ // Label 'FI24'
  /* addr 237 */ // GOTO @WHILE20
  /* addr 237 */ JMP(20),  // (@WHILE20)
  /* addr 239 */ // Label 'ELIHW20'
} ;
