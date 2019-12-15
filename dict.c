#define MAX_LENGTH 25
#define NUM_OF_ALPHABET 26
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "dict.h"
struct _Element_Word
{
	char* word;
	char* translate;
	char* key;//arn't key and word the same?
};

//---------------------------------------------hash passed functions------------------------------------------//
int HashWord(char* word, int size)//are there invalid args?
{
	return ((int)(((word[0] - 'a') * 26 + strlen(word)) % size));
}

Result PrintEntry(pWord pw)
{
	if (pw == NULL || pw->word == NULL || pw->translate == NULL) return FAIL;
	printf("%s : %s\n", pw->word, pw->translate);
	return SUCCESS;
}

Result CompareWords(char* word1, char* word2)
{
	if (word1 == NULL || word2 == NULL)return FAIL;
	if (strcmp(word1, word2) == 0) return SUCCESS;
	return FAIL;
}

char* GetEntryKey(pWord pw)
{
	if (pw == NULL) return NULL;
	return pw->key;
}

void DestroyEntry(pWord pw)
{
	if (pw == NULL) return;
	free(pw);
}
//---------------------------------------------struct word function------------------------------------------//

pWord createElementWord(char* word, char* translate)
{
	if (word == NULL || translate == NULL) return NULL;
	pWord pw;
	if ((pw = (pWord)malloc(sizeof(struct _Element_Word))) == NULL)
	{
		printf("Error Allocation Memory\n");
		return NULL;
	}
	pw->word = word;
	pw->translate = translate;
	pw->key = word;
	return pw;
}

Result setElementWordAndKey(pWord pw, char* word)
{
	if (pw == NULL || word == NULL) return FAIL;
	pw->word = word;
	pw->key = word;
	return SUCCESS;
}

Result setElementTranslate(pWord pw, char* translate)
{
	if (pw == NULL || translate == NULL) return FAIL;
	pw->translate = translate;
	return SUCCESS;
}

char* getElementInWord(pWord pw)
{
	if (pw == NULL) return NULL;
	return pw->word;
}
char* getElementInKey(pWord pw)
{
	if (pw == NULL) return NULL;
	return pw->key;
}
char* getElementInTranslate(pWord pw)
{
	if (pw == NULL) return NULL;
	return pw->translate;
}

//----------------------------------------------------

pHash CreateDictionary()
{
	pHash ph;
	ph = HashCreate(MAX_LENGTH * NUM_OF_ALPHABET, HashWord, PrintEntry, CompareWords, GetEntryKey, DestroyEntry);
	if (ph == NULL)return NULL;
	return ph;
}

Result AddTranslation(pHash ph, char* word, char* translation)//can it return a value?
{
	pWord pw = createElementWord(word, translation);
	if (pw == NULL)return FAIL;
	if (HashAdd(ph, pw) == FAIL)return FAIL;
	return SUCCESS;
}

Result Translate(pHash ph, char* word)
{
	if (ph == NULL || word == NULL)return FAIL;
	pWord p_elem = (pWord)HashFind(ph, word);
	if (p_elem == NULL)return FAIL;
	printf("Translation: %s : %s\n", p_elem->key, p_elem->translate);
	return SUCCESS;
}

Result DeleteTranslation(pHash ph, char* word)
{
	if (HashRemove(ph, word) == FAIL)return FAIL;
	return SUCCESS;
}

Result PrintDictionary(pHash ph)
{
	if (ph == NULL)return FAIL;
	printf("Dictionary Contents\n");
	HashPrint(ph);
	return SUCCESS;
}

