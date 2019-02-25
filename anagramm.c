/*
 * File: anagramm.c
 * Author: Tauno Erik
 * Created: 23.02.2019
 * Last edit: 24.02.2019
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
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024

void lower_string(char []);

int main(int argc, char *argv[])
{
	double duration;
	char temp;
	//int i = 0;
	//int j = 0;
	
	
	clock_t begin = clock();
	
	FILE *fp;
	char buffer[BUFFER_SIZE];
	char anagramm[BUFFER_SIZE];
	char foundAnagramms[50][BUFFER_SIZE];

	
	
	char *firstWord = argv[2]; // first word
	int firstWordLen = strlen(firstWord);
	int secondWordLen = 0;
	
	int fac = 0; // found anagramm counter
	
	//printf("%s\n", argv[1]); // dict.txt
	//printf("%s\n", argv[2]); // word
	
	// If no dict and/or word
	if (argc != 3)
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
	
	duration = (double)(end - begin) / (CLOCKS_PER_SEC/1000);
	
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
