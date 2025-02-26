#PROG=$1
rm cttube
gcc cttube.c parser.c transformer.c -o cttube 
./cttube truth.tb
#./cttube "$PROG"