if [ "$1" == "-l" ]
then
	avrdude -c c232hm -p m644p -U lfuse:w:"$2":m
fi

if [ "$1" == "-h" ]
then
	avrdude -c c232hm -p m644p -U hfuse:w:"$2":m
fi

if [ "$1" == "-e" ]
then
	avrdude -c c232hm -p m644p -U efuse:w:"$2":m
fi
