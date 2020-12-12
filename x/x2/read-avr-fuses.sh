avrdude -c c232hm -p m644p -U lfuse:r:a.lf:h -U hfuse:r:a.hf:h -U efuse:r:a.e:h

printf "low  :"
cat a.lf
rm a.lf

printf "high :"
cat a.hf
rm a.hf

printf "ext  :"
cat a.e
rm a.e
