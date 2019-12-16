
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"

pHash ReadDictionary () {	
	/* This function reads a dictionary line by line from the standard input. */
	/*FILE* = p_file;
	p_file = fopen("in1-1.txt", "r");*/
	pHash dictionary;
	char entryLine [100] = "";
	char *word, *translation;

	dictionary = CreateDictionary();

	while (scanf ("%s", entryLine) == 1) { // Not EOF
		word = strtok(entryLine, "=");
		translation = strtok(NULL, "=");
		AddTranslation(dictionary, word, translation);
	}

	return dictionary;
}

int main () {
	pHash ph = ReadDictionary();
	PrintDictionary(ph);
	DeleteTranslation(ph, "dog");
	DeleteTranslation(ph, "cat");
	DeleteTranslation(ph, "astronaut");
	PrintDictionary(ph);
	AddTranslation(ph, "goat", "ez");
	AddTranslation(ph, "cow", "para");
	AddTranslation(ph, "school", "beitsefer");
	AddTranslation(ph, "boy", "yeled");
	PrintDictionary(ph);
	Translate(ph, "flag");
	Translate(ph, "goat");
	Translate(ph, "school");
	Translate(ph, "apple");
	HashDestroy(ph);
	return 0;
}
