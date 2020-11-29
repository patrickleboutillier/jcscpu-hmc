REM "R2=min, R3=max" ;

DATA R2, 0 ;
DATA R3, 255 ;
LABEL 'RETRY' ;
JMP '@TRY' ;

LABEL 'TRY_RETURN' ;
REM "Save R1 to RAM at address 255" ;
DATA R0, 255 ;
ST R0, R1 ;
LABEL 'GET_CHAR' ;
DATA R0, 0 ; # TTY
OUTA R0 ;
IND R0 ;
REM '\0' ;
DATA R1, 0 ;
CMP R0, R1 ;
JE '@GET_CHAR' ;
REM 'h' ;
DATA R1, 104 ;
CMP R0, R1 ;
JE '@H' ;
REM 'l' ;
DATA R1, 108 ;
CMP R0, R1 ;
JE '@L' ;
REM '=' ;
DATA R1, 61 ;
CMP R0, R1 ;
JE '@EQ' ;
JMP '@RETRY' ;

LABEL 'H' ;
DATA R0, 255 ;
LD R0, R2 ;
JMP '@RETRY' ;

LABEL 'L' ;
DATA R0, 255 ;
LD R0, R3 ;
JMP '@RETRY' ;

LABEL 'EQ' ;
DATA R0, 33 ; # !
OUTD R0 ;
DATA R0, 10 ; # \n
OUTD R0 ;
HALT ;

LABEL 'TRY' ;
NOT R2, R1 ;
DATA R0, 1 ;
CLF ;
ADD R0, R1 ;
CLF ;
ADD R3, R1 ;
CLF ;
SHR R1, R1 ;
CLF ;
ADD R2, R1 ;
DATA R0, 1 ; # TTY_NUM
OUTA R0 ;
OUTD R1 ;
DATA R0, 0 ; # TTY
OUTA R0 ;
DATA R0, 63 ; # ?
OUTD R0 ;
DATA R0, 32 ; # ' '
OUTD R0 ;
JMP '@TRY_RETURN' ;
