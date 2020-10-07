read	$0
read	$1
j	7
blt	$0	$1	6
sub	$0	$0	$1
j	7
sub	$1	$1	$0
bne	$0	$1	3
print	$0
