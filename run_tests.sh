gcc cttube.c parser.c transformer.c -o cttube
for file in tests/*.tb; do
     ./cttube "$file"
done