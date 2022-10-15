#! /bin/bash

RED=$(tput setaf 160)
GREEN=$(tput setaf 77)
YELLOW=$(tput setaf 220)
BLACK=$(tput setaf 235)
EOC=$(tput sgr0)

if [ "$1" == "" ] || [ "$#" -gt 2 ] || [[ ! $1 =~ ^-?[[:digit:]]+$ ]]
then
	printf "\nusage: ./run.sh [number]\n
	E.g. '${YELLOW}./run.sh 20${EOC}' will run the script 20 times on big-superposition maps.
	Selected maps will be saved in maps/trace_maps/ directory.
	Results better than expected will be shown in ${GREEN}green${EOC},
	and results worse/slower than will be highlighted in ${RED}red${EOC}.\n\n"
	exit
fi

FLAG=""

if [ "$#" -eq 2 ]
then
	FLAG="$2"
fi

echo "______________________________________________"
echo "                          ___                 "
echo "      /  _  _ _    ${RED}.${EOC} _     /  _   __/_  _     "
echo "     /_,/_'/ / /__/ / /   /  /_'_\ /  _\      "
echo "______________________________________________"
echo "______________________________________________${BLACK}"
echo -e "\x1b[3m                    by altikka & atenhune${EOC}"

declare -i UNDER=0
declare -i U_RES=0
declare -i OVER=0
declare -i O_RES=0
declare -i EQUAL=0
declare -i SLOW=0
declare -i W=0
declare -i L=0
declare -i I=0

WIN="-"
LOSS="-"
T="0.000"
SLOWEST="0.000"
FASTEST="100.0"

printf "\nTesting $1 big-superposition maps.\n\n"

while [[ I -lt $1 ]]
do
	mkdir -p maps/trace_maps/
	./maps/generator --big-superposition > maps/trace_maps/temp.map
	EXPECTED=( `grep "required: " maps/trace_maps/temp.map | cut -f8 -d " " | head -1` )
	(time ./lem-in $FLAG < maps/trace_maps/temp.map) > maps/trace_maps/temp_res.txt 2> maps/trace_maps/temp_time.txt
	RESULT=( `grep ">>>>" maps/trace_maps/temp_res.txt | cut -f2 -d " "` )
	if [ "$RESULT" == "" ]
	then
		printf "ERROR:\tPlease make sure your lem-in outputs the result formatted\n\tas: '${YELLOW}>>>> [number of turns] <<<<${EOC}' followed by a newline.\n"
		printf "\tThis can be implemented as a flagged output in your program and\n\texecuted as: './run.sh [number] [lem-in flag]' in here.\n"
		printf "\tHappy testing!\n\n"
		rm -fr maps/trace_maps/
		exit
	fi
	S_TIME=( `grep "user" maps/trace_maps/temp_time.txt | cut -f2 -d "m"` )
	F_TIME=( `echo $S_TIME | grep -Eo "[+-]?[0-9]+([.][0-9]+)?"` )
	
	COLOR=${EOC}
	T_COLOR=${EOC}
	DIFF=""
	MSG=""

	if [ $RESULT -lt $EXPECTED ]
	then
		COLOR=${GREEN}
		DIFF=$(($EXPECTED - $RESULT))
		UNDER=$((UNDER + 1))
		U_RES=$((U_RES + DIFF))
		if [ $DIFF -gt 2 ]
		then
			cp maps/trace_maps/temp.map maps/trace_maps/under_${I}_\(${DIFF}\).map
			MSG="  +${DIFF} -> under_${I}_(${DIFF}).map"
		fi
		if [ $DIFF -gt $W ] && [ $DIFF -gt 2 ]
		then
			W=$DIFF
			WIN="${GREEN}+${DIFF}${EOC} under_${I}_(${DIFF}).map"
		fi
	elif [ $EXPECTED -lt $RESULT ]
	then
		COLOR=${RED}
		DIFF=$(($RESULT - $EXPECTED))
		OVER=$((OVER + 1))
		O_RES=$((O_RES + DIFF))
		cp maps/trace_maps/temp.map maps/trace_maps/over_${I}_\(${DIFF}\).map
		MSG="  -${DIFF} -> over_${I}_(${DIFF}).map"
		if [ $DIFF -gt $L ]
		then
			L=$DIFF
			LOSS="${RED}-${DIFF}${EOC} over_${I}_(${DIFF}).map"
		fi
	else
		EQUAL=$((EQUAL + 1))
	fi

	if [ $(echo "$F_TIME > 2.999" | bc -l) -eq 1 ]
	then
		T_COLOR=${RED}
		SLOW=$((SLOW + 1))
		cp maps/trace_maps/temp.map maps/trace_maps/time_${I}_\(${F_TIME}\).map
		MSG="  <t> -> time_${I}_(${F_TIME}).map"
	fi
	if [ $(echo "$F_TIME > $SLOWEST" | bc -l) -eq 1 ]
	then
		SLOWEST=$F_TIME
	fi
	if [ $(echo "$F_TIME < $FASTEST" | bc -l) -eq 1 ]
	then
		FASTEST=$F_TIME
	fi
	T=$(echo "$T+$F_TIME" | bc -l)

	printf "Expected: %3s" $EXPECTED
	printf " | Result: ${COLOR}%3s${EOC}" $RESULT
	printf " | Time: ${T_COLOR}%.2f${EOC}s${MSG}\n" $F_TIME

	rm -fr maps/trace_maps/temp.map
	rm -fr maps/trace_maps/temp_res.txt
	rm -fr maps/trace_maps/temp_time.txt

	I=$((I + 1))
	sleep 0.7
done

printf "DONE\n\n"
echo "______________________________________________"
printf "\nSummary:\n"
printf " ${EQUAL}/$1 of maps were solved as expected.\n"
printf " ${GREEN}${UNDER}${EOC}/$1 of maps were solved better than expected.\n"
if [ $UNDER -gt 0 ]
then
	U_AVR=$(echo "$U_RES/$UNDER" | bc -l)
	printf "  average: +"
	printf %.2f $U_AVR
	printf " | best: ${WIN}\n"
fi

printf " ${RED}${OVER}${EOC}/$1 of maps were solved worse than expected.\n"
if [ $OVER -gt 0 ]
then
	O_AVR=$(echo "$O_RES/$OVER" | bc -l)
	printf "  average: -"
	printf %.2f $O_AVR
	printf " | worst: ${LOSS}\n"
fi

printf "Time:\n  average: "
T_AVR=$(echo "$T/$1" | bc -l)
T_AVR_COLOR=$EOC
if [ $(echo "$SLOWEST > 2.999" | bc -l) -eq 1 ]
then
	T_AVR_COLOR=$RED
fi
printf %.2f $T_AVR
printf "s | saved ($SLOW) slower maps.\n" 
printf "  fastest: %.2f" $FASTEST
printf "s | slowest: ${T_AVR_COLOR}%.2f${EOC}s\n" $SLOWEST
echo "______________________________________________"

printf "\nDo you wish to remove saved files? (yes/no)${YELLOW}\x1b[3m\n"
read remove_trace
printf "${EOC}"
if [ "$remove_trace" == "yes" ]
then
	rm -fr maps/trace_maps/
fi
exit
