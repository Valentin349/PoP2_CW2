/*
 ============================================================================
 Name        : CWK2Q5.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement an algorithm in C which given a file containing a block of text as
 input, redacts all words from a given set of “redactable” words (also from a
 file), and outputs the result to a file called “result.txt”. For example,
 given the block of text:
    The quick brown fox jumps over the lazy dog

 and the redactable set of words:
    the, jumps, lazy

 the output text in “result.txt” should be
    *** quick brown fox ***** over *** **** dog

 Note that the number of stars in the redacted text is the same as the number
 of letters in the word that has been redacted, and that capitalization is
 ignored. You should not use any of the string libraries to answer this
 question. You should also test your program using the example files
 provided.
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

char* readFile(const char *text_filename, const char *mode){
	FILE *fp;
	long length;
	char *buff;

	fp = fopen(text_filename, mode);
	if (fp){
		// get num of bytes
		fseek(fp, 0L, SEEK_END);
		length = ftell(fp);
		// reset file pos to beginning of the file
		fseek(fp, 0L, SEEK_SET);
		buff = malloc(length+1);
		// write to buffer
		if (buff){
			fread(buff, sizeof(char), length, fp);
		}
		fclose(fp);
		// fread doesnt add \0 at the end of the file so we have to add it manually
		buff[length] = '\0';
	}
	return buff;
}

int countWords(char* buff){
	int wordCount = 0;
	while(*buff != '\0'){
		if (*buff == ' ' || *buff == '\t' || *buff == '\n'){
			wordCount++;
		}
		buff++;
	}
	return wordCount;
}

void letterCounter(char* buff){
	int counter = 0;
	while(*buff != '\0' || *buff == ' ' || *buff == '\t' || *buff == '\n'){
		counter++;
		buff++;
	}
	return wordCount;
}


void redact_words(const char *text_filename, const char *redact_words_filename){
	char *textBuff = readFile(text_filename, "r");
	char **words = malloc(countWords(textBuff) * sizeof(char*));

	printf("%d\n", countWords(textBuff));
}

int main(int argc, char *argv[]) {
	const char *input_file = "./debate.txt";
	const char *redact_file = "./redact.txt";
	redact_words(input_file, redact_file);
	return EXIT_SUCCESS;
}