## COMP 2401 A5 Emergency Room Processes Signals
#	Author @ Addison Xiong
	Date @ Dec 9 2021
	
## Purpose: 
	 Assesses a set of patients and determines for each patient whether the patient needs to be hospitalized and if so for how many days
	
## Structure for the edited files(except from already provided):

	drAssessment.c (executable drAssessment)
	singleAssessment.c (executable singleMorph, use Makefile1)
	singleSpawn.c (executable singleSpawn, use Makefile2)
	multiSpawn.c (executable multiSpawn, use Makefile3)


## Instruction to compile the program(examples provided)
	To test TASK I, the user will provide the file name in the command line to read
		e,g. 
			make -f Makefile1
			./singleMorph patient.bin

	To test TASK II, the user will provide the file name in the command line to read
		e,g. 
			make -f Makefile2
			./singleSpawn patient.bin

	To test TASK III, the user will provide the file name in the command line to read
		e,g. 
			make -f Makefile3
			./multiSpawn patient.bin
			
	To test drAssessment.c
		gcc -o drAssessment drAssessment.c
		./drAssessment

## Limitations/Issues

	N/A

## How to use the software
	make files will include all the dependencies for each program
	use make file to create executables for each program
	
	singleMorph: assess a single patient, to print any assessment, uncomment the print statments in drAssessment.c
	singleSpawn: fork a child, morph the child to assess a single patient, parent print the assessment
	multiSpawn: fork 10 children and assess 10 patients (only print the patients who needs hospitalization)

	For details of each program, please read the header comments for each .c file 
	
## Bonus
	did the first bonus question(find the number of records in the file, allocate the memory)	

