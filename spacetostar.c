#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

#define BUF 500

int main(int arg, char* argv){
	char * string = malloc(sizeof(char)*BUF);
	while (fgets(string, BUF, stdin)){
		if (strcmp(string, "\n") == 0){
				free(string);
				return 0;
		}
		char * nstring = malloc(strlen(string)+1);
		strcpy(nstring, spacetostar(string));
		char * nnstring = malloc(strlen(string)+1);
		strcpy(nnstring, lowertoupper(nstring));
		printf("%s", nstring);
		printf("%s", nnstring);
	}
	free(string);
	free(nstring);
	free(nnstring);
	return 0;
}

char* spacetostar(char *string){
	char buf[strlen(string)+1];
	strcpy(buf ,string);;
	for (int i = 0; buf[i] != '\0'; i++){
		if (buf[i] == ' '){
			buf[i] = '*';
		}
	}
	string = &buf[0];
	return string;
}

char* lowertoupper(char *string){
	char buf[strlen(string)+1];
	strcpy(buf ,string);;
	for (int i = 0; buf[i] != '\0'; i++){
		if (islower(buf[i])){
			buf[i] = toupper(buf[i]);
		}
	}
	string = &buf[0];
	return string;

}
