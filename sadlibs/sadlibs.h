//
//  sadlibs.h
//  sadlibs
//
//  Created by Adriano Iqbal on 11/29/15.
//  Copyright © 2015 Adriano Iqbal. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef sadlibs_h
#define sadlibs_h

//max length of complete sentence
#define MAXLENGTH 500

//number of sentences to generate
#define NUMSENTS 2

//macros to distinguish between different part types
#define INDEPENDENT 0
#define SUBORDINATE 1
#define NAME 2

//macros to distinguish between different sentence structure types
#define SIMPLE 0
#define COMPOUND 1
#define COMPLEX_A 2
#define COMPLEX_B 3
#define COMPOUNDCOMPLEX 4

//the sentence struct
typedef struct sentence{
    char* contents;
    int structure_type;
    int length;
} sentence;

//function declarations
sentence* sentence_init ();
char* get_part (int part_type);
void assemble_parts (sentence* target);

//helper function: appendpart. Takes sentence pointer, the address of a position counter,
//and a part, and appends the part onto the sentence.
void appendpart (sentence* target, char* part, int* pos){
    strcpy(&target->contents[*pos], part);
    *pos += strlen(part);
}

char* stringinsert (sentence* target, char* littlestring, int pos){
    char buffer [500] = {'\0'};
    char* bufp = &buffer[0];
    strncpy(bufp, target->contents, pos);
    strcpy(&bufp[pos], littlestring);
    strcpy(&bufp[pos + strlen(littlestring)], &target->contents[pos + 1]);
    char* returnstr = bufp;
    return returnstr;
}

#endif /* sadlibs_h */
