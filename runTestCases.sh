#!/bin/bash

if which dos2unix ; then
	DOSUNIX="dos2unix"
elif which fromdos ; then
	DOSUNIX="fromdos"
else
	DOSUNIX="cat"
fi

echo "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"

PASSED=0
CHECKED=0

make clean
make bin/c_compiler
dos2unix bin/c_compiler
mkdir -p testout
OUTPUT_DIRECTORY=testout

for i in compiler_tests/*; do
	SUB_FOLDER=${OUTPUT_DIRECTORY}/$(basename ${i})
	mkdir -p ${SUB_FOLDER}
	for j in $i/*.c; do
		b=$(basename ${j});
		n=${b%.c}
		m=${j%.c}

		if [[ $b != *_driver.c ]]; then
			TESTCASE=${SUB_FOLDER}/${n}
			mkdir -p ${TESTCASE}
			echo "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"
			echo ""
			echo "C File: ${j}"
			echo "Test Case: $n"

			bin/c_compiler -S ${j} -o ${TESTCASE}/$n.s
			mips-linux-gnu-gcc -mfp32 -o ${TESTCASE}/$n.o -c ${TESTCASE}/$n.s
			mips-linux-gnu-gcc -mfp32 -static -o ${TESTCASE}/$n ${TESTCASE}/$n.o ${m}_driver.c
			qemu-mips ${TESTCASE}/$n
			
			# print the exit code
			RESULT=$?
			echo "Exit code: ${RESULT}";
			echo ""
			
			# check if return code is 0
			if [ ${RESULT} -eq 0 ]; then
				echo "P A S S";
				PASSED=$(( ${PASSED}+1 ));
			else
				echo "F A I L";
			fi
			CHECKED=$(( ${CHECKED}+1 ));
		fi	
	done
done

echo "#################################"
echo ""
echo "Passed ${PASSED} out of ${CHECKED}"
echo ""
echo "#################################"
make clean