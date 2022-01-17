/* 
	Task III: Spawning multi children

	Program name: multiSpawn.c

	Executable name: multiSpawn

	Make file: Makefile3

	Purpose: fork 10 children to assess 10 patients and determine if he/she needs to be hospitalized

	To use, the user will provide the file name in the command line to read
		e,g. 
			make -f Makefile3
			./multiSpawn patient.bin

*/

// INCLUDE FILES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "patient.h"

// FUNCTION PROTOTYPES
int fexists(char *fileName);
int morph(char *id, char *priorityLevel, char *medicalProblem);
int waitpid(int, int *, int);;
int parentFun(PatientInfo patient);


/**********************************************************************/
// main function

int main(int argc, char *argv[]) {
	PatientInfo patient;
	FILE *fid;
	int rc;
	char id[20];
	char priority[5];
	char medical[50];
	int cpid;
	int status = 0;
	PatientInfo patients[10];
	int NumBytes;
	int NumRecords;
	int *childProcessIds = NULL;

	// check if file name provided
	if (argc < 2) {
	  printf("Usage: %s filename \n",argv[0]);
	  return(-2);
	}


	// check if it exists
	rc = fexists(argv[1]);

	// if does not exist
	if(rc == -3){
		printf("File %s does not exist\n", argv[1]);
		return(-3);
	}

	//file opened and exsits, read the 1st patient record**
	else{

		fid = fopen(argv[1], "rb+");
		rc = fread(patients, sizeof(patient), 10, fid);
		printf("number or records read: %d\n", rc);

		// * determine how many record in the file
		fseek(fid, 0, SEEK_END);
		NumBytes = ftell(fid);
		NumRecords = NumBytes/sizeof(patient);
		childProcessIds = (int *) malloc(NumRecords * sizeof(int));
    	if (childProcessIds == NULL) return(1);

		printf("number of records in the file %d\n", NumRecords);
		fclose(fid);

		for (int i = 0; i < 10; i++){

			childProcessIds[i] = fork();
			// child
			if(childProcessIds[i] == 0){
				// convert patient data

				sprintf(id,"%d", patients[i].id);
				sprintf(priority,"%d", patients[i].priorityLevel);
				sprintf(medical,"%s", patients[i].medicalProblem);

				rc = morph(id, priority, medical);

				printf("should not get here\n");
				exit(0);
			}
	
			// parent
			else if (childProcessIds[i] > 0) {
				// call parent handle function
				rc = parentFun(patients[i]);
			} 

			// error
			else {

				exit(-4);
			}
			
		}


	}


	return(0);


}


/************************************************************************/
// parentFun: parent wait until child function terminated, if terminated properly, print assessment; if not, print error msg

//input: patient

// return:childrc or -4
//	
int parentFun(PatientInfo patient)
{ 
   int cpid; 
   int status = 0;
   int childrc; 
   
   cpid=waitpid(-1, &status, 0); 
 
   // no more child or error
   if (cpid == -1){
   	 exit(0);
   }

   childrc = WEXITSTATUS(status);

   if (WIFEXITED(status) != 0){
   	  if (childrc > 0){
   	  	printf("Patient %s %s id(%d) requires %d days in hospital\n",patient.firstName, patient.familyName, patient.id, childrc);
   	  }
   	  return(childrc);
   }
   else{
   		printf("Error! Child did not terminate properly\n");
   		return (-4);
   }


}

/************************************************************************/
// morph: execute moprhed function drAssessment

// Input: id, priorityLevel, medicalProblem

// drAssessment Return:
// 0 - the patient does not need hospitalization
// >0 - the number of hospitalization days
// -1 - if the prioity is not in the range of 0-9
// -2 - if the command line parameter is not correct 


int morph(char *id, char *priorityLevel, char *medicalProblem){
	char *args[5];
    int rc;

    args[0] = "./drAssessment";
    args[1] = id;
    args[2] = priorityLevel;
    args[3] = medicalProblem;
    args[4] = NULL;

    rc=execvp("./drAssessment",args);

    // only print below if fails
    printf("The program should not print this rc = %d\n",rc);
    return(rc);
}



/************************************************************************/
// Return whether the given file exists in the current directory.

// Return:
// 0 if the file does not exist
// 1 if exists
int fexists(char *fileName)
{
    // add code

    FILE *fp = NULL;

  // open the file

    fp = fopen(fileName, "r");

    if (fp == NULL) {
      return(-3);
    }
 
    fclose(fp);
    return(1);
}


