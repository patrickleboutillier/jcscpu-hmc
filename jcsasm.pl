#!/usr/bin/perl 
use strict ;
use Carp ;


my $DATAADDR = 255 ;
my $PRINT = 1 ;
my @LINES = () ;
my %LABELS = () ;
my $NB_REM = 0 ;


END {
	if ($PRINT){
		my $name = $ARGV[0] || 'prog' ;
		print "PROGMEM const byte ${name}[] = {\n" ;
    	print join("\n", grep { $_ !~ /SKIP_PRINT/ } @{done()})  ;
		print "\n} ;\n"  ;
	}
}


$SIG{__DIE__} = sub {
    $PRINT = 0 ;
} ;


sub nb_lines {
    return scalar(@LINES) - $NB_REM ;
}


sub done {
    return [] unless scalar(@LINES) ;

    my $last = $LINES[-1] ;
    # Process GOTOs
    for (my $i = 0 ; $i < scalar(@LINES) ; $i++){
        my $l = $LINES[$i] ;
        if ($l =~ /\@(\w+)/){
            my $label = $1 ;
            my $byte = $LABELS{$label} ;

            if (! defined($byte)){
                print STDERR "Undefined label '$label'!\n" ;
                exit(1) ;
            }
            my $bin = sprintf("%08b", $byte) ;
            $LINES[$i] =~ s/\@\@$label/$byte/ ;
        }
    }

    my @ret = @LINES ;
    @LINES = () ;
    %LABELS = () ;
    $NB_REM = 0 ;
    
    return \@ret ;
}


sub add_inst {
    my $inst = shift ;
    my $comment = shift ;

	$inst .= ($inst ? ', ' : '') ;
	$comment = ($comment ? "// " : '') . $comment ;

    my $no = scalar(@LINES) ;
    my $pos = $no - $NB_REM ;
    push @LINES, 
		sprintf("  /* addr %3d */ ", $pos) .
		($inst ? sprintf("%-15s ", $inst) : '') .
		$comment ;
}


sub R0() {
    my $this = {v => "R0", n => "R0"} ;
    return bless $this, "R" ;
} 


sub R1() {
    my $this = {v => "R1", n => "R1"} ;
    return bless $this, "R" ;
} 


sub R2() {
    my $this = {v => "R2", n => "R2"} ;
    return bless $this, "R" ;
} 


sub R3() {
    my $this = {v => "R3", n => "R3"} ;
    return bless $this, "R" ;
} 


sub REM {
    add_inst("", join('', @_)) ;
    $NB_REM++ ;
}


sub ADD($$) {
    _reg_reg("1000", "ADD", @_) ;
}


sub SHR($$) {
    _reg_reg("1001", "SHR", @_) ;
}


sub SHL($$) {
    _reg_reg("1010", "SHL", @_) ;
}


sub NOT($$) {
    _reg_reg("1011", "NOT", @_) ;
}


sub AND($$) {
    _reg_reg("1100", "AND", @_) ;
}


sub OR($$) {
    _reg_reg("1101", "OR", @_) ;
}


sub XOR($$) {
    _reg_reg("1110", "XOR", @_) ;
}


sub CMP($$) {
    _reg_reg("1111", "CMP", @_) ;
}


sub LD($$) {
    _reg_reg("0000", "LD", @_) ;
}


sub ST($$) {
    _reg_reg("0001", "ST", @_) ;
}


sub DATA($$) {
    _reg_byte("0010", "DATA", @_) ;
}


sub JMPR($) {
    my ($rb) = _check_proto("R", @_) ;

    add_inst("JMPR($rb->{v})") ;
}


sub CLF() {
    _check_proto("", @_) ;

    add_inst("CLF") ;
}


sub HALT(;$) {
    _check_proto("", @_) ;

    add_inst("HALT", $_[0]) ;
}


sub JMP($) {
    my ($byte) = _check_proto("A", @_) ;

    my $bin = undef ;
    if ($byte =~ /^\@/){
        $bin = $byte ;
        $byte = "\@$bin" ;
    }
    else {
        $bin = sprintf("%08b", $byte) ;
    }

    add_inst("JMP($byte)", "($bin)") ;
	add_inst("", "SKIP_PRINT") ;
}


sub GOTO($) {
    my $label = shift ;

    croak("JCSASM: Invalid label '$label'") unless $label =~ /^\w+$/ ;
    REM("GOTO \@$label") ;
    JMP("\@$label") ;
}


sub LABEL($) {
    my $label = shift ;

    croak("JCSASM: Invalid label '$label'") unless $label =~ /^\w+$/ ;
    croak("JCSASM: Label '$label' already defined") if $LABELS{$label} ;
    my $pos = scalar(@LINES) - $NB_REM ;
    $LABELS{$label} = $pos ;
    REM("Label '$label'") ;
    return $pos ;
}


sub _JMPXXX {
    my $flags = shift ;
    my $label = shift ;
    my ($byte) = _check_proto("A", @_) ;

    my $bin = undef ;
    if ($byte =~ /^\@/){
        $bin = $byte ;
        $byte = "\@$bin" ;
    }
    else {
        $bin = sprintf("%08b", $byte) ;
    }

    add_inst("J$label($byte)", "($bin)") ;
	add_inst("", "SKIP_PRINT") ;
}


sub JC    { return _JMPXXX("1000", "C", @_) ;}
sub JA    { return _JMPXXX("0100", "A", @_) ;}
sub JE    { return _JMPXXX("0010", "E", @_) ;}
sub JZ    { return _JMPXXX("0001", "Z", @_) ;}
sub JCA   { return _JMPXXX("1100", "CA", @_) ;}
sub JCE   { return _JMPXXX("1010", "CE", @_) ;}
sub JCZ   { return _JMPXXX("1001", "CZ", @_) ;}
sub JAE   { return _JMPXXX("0110", "AE", @_) ;}
sub JAZ   { return _JMPXXX("0101", "AZ", @_) ;}
sub JEZ   { return _JMPXXX("0011", "EZ", @_) ;}
sub JCAE  { return _JMPXXX("1110", "CAE", @_) ;}
sub JCAZ  { return _JMPXXX("1101", "CAZ", @_) ;}
sub JCEZ  { return _JMPXXX("1011", "CEZ", @_) ;}
sub JAEZ  { return _JMPXXX("0111", "AEZ", @_) ;}
sub JCAEZ { return _JMPXXX("1111", "CAEZ", @_) ;}


sub IND($){
    my ($rb) = _check_proto("R", @_) ;

    add_inst("IND($rb->{v})") ;
}


sub INA($) {
    my ($rb) = _check_proto("R", @_) ;

    add_inst("OUTD($rb->{v})") ;
}


sub OUTD($) {
    my ($rb) = _check_proto("R", @_) ;

    add_inst("OUTD($rb->{v})") ;
}


sub OUTA($) {
    my ($rb) = _check_proto("R", @_) ;

    add_inst("OUTA($rb->{v})") ;
}


sub TTY(){
	return 0 ;
}


sub TTY_NUM(){
	return 1 ;
}


sub RNG(){
	return 1 ;
}


sub VAR(;$) {
    my $value = undef ;
    ($value) = _check_proto("A", @_) if scalar(@_) ;

    my $addr = $DATAADDR-- ;
    croak("Data segment overlapped code segment!!!") if ($DATAADDR <= nb_lines()) ;
    my $this = \$addr ;

    if (defined($value)){
        SET($this, $value) ;
    }

    return bless($this, "V") ;
}


sub SET($$){
    my ($var, $value) = _check_proto("VA", @_) ;

    DATA R0, $value ;
    DATA R1, $$var ; 
    ST R1, R0 ;
}


sub COPY($$){
    my ($vara, $varb) = _check_proto("VV", @_) ;

    DATA R0, $$vara ;
    LD R0, R0 ;
    DATA R1, $$varb ;
    ST R1, R0 ;
}


sub EQ($$) {
    my ($vara, $varb) = _check_proto("VV", @_) ;

    DATA R0, $$vara ;
    LD R0, R0 ;
    DATA R1, $$varb ;
    LD R1, R1 ;
    DATA R2, 1 ;
    CMP R0, R1 ;
    my $eq = "EQ" . nb_lines() ;
    JE "\@$eq" ;
    XOR R2, R2 ;
    LABEL $eq ;

    my $ret = VAR() ;
    DATA R0, $$ret ;
    ST R0, R2 ;

    return $ret ;
}


sub GT($$) {
    my ($vara, $varb) = _check_proto("VV", @_) ;

    DATA R0, $$vara ;
    LD R0, R0 ;
    DATA R1, $$varb ;
    LD R1, R1 ;
    DATA R2, 1 ;
    CMP R0, R1 ;
    my $gt = "GT" . nb_lines() ;
    JA "\@$gt" ;
    XOR R2, R2 ;
    LABEL $gt ;

    my $ret = VAR() ;
    DATA R0, $$ret ;
    ST R0, R2 ;

    return $ret ;
}


sub PLUS($$;$) {
    my ($vara, $varb) = _check_proto("VV", @_) ;
    shift ; shift ;
    my $varc = undef ;
    ($varc) = _check_proto("V", @_) if (scalar(@_)) ;

    DATA R0, $$vara ;
    LD R0, R0 ;
    DATA R1, $$varb ;
    LD R1, R1 ;
    CLF ;
    ADD R0, R1 ;

    my $dest = $varc ;
    $dest = VAR() unless defined($dest) ;
    DATA R0, $$dest ;
    ST R0, R1 ;

    return $dest ;
}


sub MINUS($$;$) {
    my ($vara, $varb, $varc) = _check_proto("VV", @_) ;
    shift ; shift ;
    my $varc = undef ;
    ($varc) = _check_proto("V", @_) if (scalar(@_)) ;

    DATA R0, $$vara ;
    LD R0, R0 ;
    DATA R1, $$varb ;
    LD R1, R1 ;
    NOT R1, R1 ;
    DATA R2, 1 ; 
    CLF ;
    ADD R2, R1 ;
    CLF ;
    ADD R0, R1 ;

    my $dest = $varc ;
    $dest = VAR() unless defined($dest) ;
    DATA R0, $$dest ;
    ST R0, R1 ;

    return $dest ;
}


sub IF($&;&){
    my ($var, $blkif, $blkelse) = _check_proto("VBB", @_) ;

    # Put $var in R0
    DATA R0, $$var ;
    LD R0, R0 ; 
    # z flag will be set if R0 == 0
    OR R0, R0 ;  

    my $fi = "FI" . nb_lines() ; 
    my $else = "ELSE" . nb_lines() ; 
    JZ ($blkelse ? "\@$else" : "\@$fi") ;
    $blkif->() ;
	if ($blkelse){
    	GOTO $fi ;
    	LABEL $else ;
    	$blkelse->() ;
	}
    LABEL $fi ;
}


sub WHILE(&&) {
    my $cond = shift ;
    my $block = shift ;

    my $while = "WHILE" . nb_lines() ;
    my $elihw = "ELIHW" . nb_lines() ;
    LABEL $while ;
    IF $cond->(), sub {
        $block->() ;
    }, sub {
        GOTO $elihw ;
    } ;
    GOTO $while ;
    LABEL $elihw ;
}



sub PRINT_CHAR($){
    my ($var) = _check_proto("V", @_) ;

    DATA R0, $$var ;
    LD R0, R0 ; 
    XOR R1, R1 ;
    OUTA R1 ;
    OUTD R0 ;
}


sub PRINT_NUM($){
    my ($var) = _check_proto("V", @_) ;

    DATA R0, $$var ;
    LD R0, R0 ; 
    DATA R1, 1 ;
    OUTA R1 ;
    OUTD R0 ;
}


sub GET_CHAR($){
    my ($var) = _check_proto("V", @_) ;
    XOR R0, R0 ;
	OUTA R0 ;
	IND R0 ;
    DATA R1, $$var ;
    ST R1, R0 ;
}


sub _check_proto {
    my $proto = shift ;
    my @args = @_ ;

    my @ps = split(//, $proto) ;
    my @newargs = () ;
    for (my $j = 0 ; $j < scalar(@ps) ; $j++){
        my $ok = 1 ;
        my $arg = shift @args ;
        if (($ps[$j] eq "R")&&(ref($arg) != "R")){
            $ok = 0 ;
        }
        if ($ps[$j] eq "A"){
            if ($arg !~ /^\@\w+$/){
                my $argn = _valid_num($arg) ;
                if ((! defined($arg))||($argn == -1)){
                    $ok = 0 ;
                }          
                $arg = $argn ;
            }
        }     
        if (($ps[$j] eq "V")&&(ref($arg) != "V")){
            $ok = 0 ;
        }
        if (($ps[$j] eq "B")&&(ref($arg) != "CODE")){
            $ok = 0 ;
        }     

        croak("JCSASM: Invalid syntax ($ps[$j] => $arg)") unless $ok ;
        push @newargs, $arg ; 
    }

    return @newargs ;
}


sub _valid_dec {
    my $d = shift ;

    if ($d =~ /^(0d)?(\d+)$/){
        $d = $2 ;
        croak("JCSASM: Decimal value '$d' to large") unless $d < 256 ;   
        return $d ;
    }

    return -1 ;
}


sub _valid_bin {
    my $b = shift ;

    if ($b =~ /^(0b)([01]{8})$/){ 
        return oct($b) ;
    }

    return -1 ;
}


sub _valid_num {
    my $n = shift ;

    foreach my $s (\&_valid_dec, \&_valid_bin){
        my $r = $s->($n) ;
        return $r if $r != -1 ;
    } 

    return -1 ;
}


sub _reg_reg {
    my $inst = shift ;
    my $label = shift ;
    my ($ra, $rb) = _check_proto("RR", @_) ;

    add_inst("$label($ra->{v}, $rb->{v})") ;
}


sub _reg_byte {
    my $inst = shift ;
    my $label = shift ;
    my ($rb, $byte) = _check_proto("RA", @_) ;

    my $bin = sprintf("%08b", $byte) ;
    add_inst("$label($rb->{v}, $byte)", "($bin)") ;
	add_inst("", "SKIP_PRINT") ;
}


eval join("", <STDIN>) ;
die "$@\n" if $@ ;


__DATA__









sub NEQ($$) {
    my ($vara, $varb) = _check_proto("VV", @_) ;

    DATA R0, $$vara ;
    LD R0, R0 ;
    DATA R1, $$varb ;
    LD R1, R1 ;
    XOR R0, R1 ;
    my $ret = VAR() ;
    DATA R0, $$ret ;
    ST R0, R1 ;

    return $ret ;
}





1 ;
