/*
 * File: anagramm.c
 * Author: Tauno Erik
 * Created: 23.02.2019
 * Last edit: 01.03.2019
 * 
 * Description: Finds all anagrams for provided word from a provided
 * 				dictionary.
 * 				Returns executation time in microseconds and anagramms.
 * 
 * 				Compile: gcc anagramm.c -o ./bin/anagramm
 * 				
 * 				Run: ./bin/anagramm lemmad.txt word
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <memory.h>

#define BUFFER_SIZE 50

void lower_string(char []);

int main(int argc, char *argv[])
{
	double duration;
	
	clock_t begin = clock();
	
	FILE *fp;
	
	char buffer[BUFFER_SIZE];
	char anagramm[BUFFER_SIZE];
	char foundAnagramms[50][BUFFER_SIZE];
	
	int secondWordLen = 0;
	int fac = 0; // found anagramm counter
	
	char *firstWord = argv[2];
	
	// if two words
	if (argv[3])
	{
		char space[2];
		firstWord = (char *) malloc(2 + strlen(argv[2])+ strlen(argv[3]) );
		strcpy(space, " ");
		strcpy(firstWord, argv[2]);
		strcat(firstWord, space);
		strcat(firstWord, argv[3]);
	}

 
	int firstWordLen = strlen(firstWord);
	
	// If no dict and/or word
	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s <dict.txt> <word>\n", argv[0]);
		return 1;
	}
	
	// If we can not open dict file
	if ( (fp = fopen((argv[1]), "rt" )) == NULL)
	{
		perror("Can not open dict-file");
		return 1;
	}
	
	while ( fgets(buffer, sizeof(buffer), fp))
	{
		buffer[strlen(buffer) - 1] = '\0';
		lower_string(buffer);
		buffer[strcspn(buffer, "\r\n")] = 0;
		
		char *secondWord = buffer;
		int counter = 0;
		
		size_t destination_size = sizeof(buffer);
		
		// copy buffer to anagramm 
		strncpy(anagramm, buffer,destination_size);
		anagramm[destination_size - 1] = '\0'; 
		
		secondWordLen = (strlen(buffer)); 
		
		// if words are same length
		if (firstWordLen == secondWordLen )
		{
			char temp;
			// Sort both words
			for (int i = 0; i < firstWordLen; i++) 
			{
				for (int j = i+1; j < firstWordLen; j++)
				{
					if (firstWord[i] > firstWord[j])
					{
						temp = firstWord[i];
						firstWord[i] = firstWord[j];
						firstWord[j] = temp;
					}
					if (secondWord[i] > secondWord[j])
					{
						temp = secondWord[i];
						secondWord[i] = secondWord[j];
						secondWord[j] = temp;
					}
				}
			}
			
			// compare both wors charcter by character
			for (int i = 0; i < firstWordLen; i++)
			{
				if (firstWord[i] == secondWord[i])
				{
					counter ++;
				}
			}
			
			//if is anagramm
			if (counter == firstWordLen) 
			{
				size_t size = sizeof(anagramm);
				strncpy(foundAnagramms[fac], anagramm, size);
				fac ++; 
			}
		}
	}
	fclose(fp);
	
	clock_t end = clock();
	
	//duration = (double)(end - begin); 
	duration = (double)(end - begin) / CLOCKS_PER_SEC;
	duration = duration*1000000;
	
	printf("%.2f", duration);
	
	for (int i = 0; i < fac; i++)
	{
		printf(",%s", foundAnagramms[i]);
	}

	printf("\n");

	return 0;
} 

/*
 * Function to lowercase char
 */ 
void lower_string(char s[]) {
	int c = 0;
   
	while (s[c] != '\0') {
		if (s[c] >= 'A' && s[c] <= 'Z') {
			s[c] = s[c] + 32;
		}
		c++;
	}
}
