read	$3
addi	$1	$2	1
addi	$2	$2	2
blt	$3	$2	8
addi	$2	$2	-1
mul	$1	$3	$1
addi	$3	$3	-1
bne	$2	$3	5
print	$1
