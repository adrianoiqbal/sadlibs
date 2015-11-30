//
//  main.c
//  sadlibs
//
//  Created by Adriano Iqbal on 11/29/15.
//  Copyright © 2015 Adriano Iqbal. All rights reserved.
///

#include "sadlibs.h"

//initializes an empty sentence structure, returns pointer to that sentence
sentence* sentence_init (){
    sentence* s = malloc(sizeof(sentence));
    s->contents = malloc(MAXLENGTH);
    s->length = 0;
    s->structure_type = arc4random() % 5; //number of sentence types
    return s;
}

char* get_part (int part_type){
    long pos;
    long length;
    char charholder = 'a';
    size_t capval = (size_t)MAXLENGTH;
    
    FILE* stream;
    char* part = malloc(MAXLENGTH);
    
    //figure out which part you need (i.e. which file to open)
    switch (part_type) {
        case INDEPENDENT:
            stream = fopen("/Users/adrianoiqbal/Documents/Xcode Stuff/sadlibs/sadlibs/independent.txt", "r");
            break;
        
        case SUBORDINATE:
            stream = fopen("/Users/adrianoiqbal/Documents/Xcode Stuff/sadlibs/subordinate.txt", "r");
            break;
            
        case NAME:
            stream = fopen("/Users/adrianoiqbal/Documents/Xcode Stuff/sadlibs/sadlibs/names.txt", "r");
            break;
            
        default:
            perror("no such part exists");
            exit(1);
            break;
    }
    
    //get length of file first
    fseek(stream, 0, SEEK_END);
    length = ftell(stream);

    //then, jump to random spot in file
    pos = arc4random() % length;
    fseek(stream, pos, SEEK_SET);
    
    //find the start of that line (by going to end of previous line)
    //error handling here
    while(charholder != '\n'){
        fread(&charholder, 1, 1, stream);
        pos = ftell(stream);
        fseek(stream, -2, SEEK_CUR);
    }
    
    //grab that line
    fseek(stream, 2, SEEK_CUR);
    getline(&part, &capval, stream);
    part[strlen(part) - 1] = '\0';
    
    return part;
}

void assemble_parts (sentence* target){
    
    int content_pos = 0;
    char* part;
    
    switch (target->structure_type) {
        case SIMPLE:
            part = get_part(INDEPENDENT);
            appendpart(target, part, &content_pos);
            break;
            
        case COMPOUND:
            //get first clause
            part = get_part(INDEPENDENT);
            appendpart(target, part, &content_pos);
            
            //connect the parts with a semicolon and space
            target->contents[content_pos] = ';';
            content_pos++;
            target->contents[content_pos] = ' ';
            content_pos++;
            
            //get second clause
            part = get_part(INDEPENDENT);
            appendpart(target, part, &content_pos);
            break;
            
        case COMPLEX_A:
            //get subordinate clause
            part = get_part(SUBORDINATE);
            appendpart(target, part, &content_pos);
            
            //connect the parts with a comma and space
            target->contents[content_pos] = ',';
            content_pos++;
            target->contents[content_pos] = ' ';
            content_pos++;
            
            //get independent clause
            part = get_part(INDEPENDENT);
            appendpart(target, part, &content_pos);
            break;
            
        case COMPLEX_B:
            //get subordinate clause
            part = get_part(INDEPENDENT);
            appendpart(target, part, &content_pos);
            
            //connect the parts with a comma and space
            target->contents[content_pos] = ',';
            content_pos++;
            target->contents[content_pos] = ' ';
            content_pos++;
            
            //get independent clause
            part = get_part(SUBORDINATE);
            appendpart(target, part, &content_pos);
            
            break;
            
        case COMPOUNDCOMPLEX:
            //get subordinate clause
            part = get_part(SUBORDINATE);
            appendpart(target, part, &content_pos);
            
            //connect the parts with a comma and space
            target->contents[content_pos] = ',';
            content_pos++;
            target->contents[content_pos] = ' ';
            content_pos++;
            
            //get independent clause
            part = get_part(INDEPENDENT);
            appendpart(target, part, &content_pos);
            
            //connect the parts with a comma and space
            target->contents[content_pos] = ';';
            content_pos++;
            target->contents[content_pos] = ' ';
            content_pos++;
            
            //get independent clause
            part = get_part(INDEPENDENT);
            appendpart(target, part, &content_pos);
            
            break;
            
        default:
            perror("assembly failed");
            exit(1);
            break;
            
    }
    
    //cap off sentence with period and newline
    target->contents[content_pos] = '.';
    content_pos++;
    target->contents[content_pos] = '\n';
    content_pos++;
    
    //update length
    target->length = content_pos;
    
    //search through and replace placeholder signs ($) with names
    for (int letter = 0; letter < target->length; letter++) {
        if (target->contents[letter] == '$') {
            target->contents = stringinsert(target, get_part(NAME), letter);
        }
    }
    
    //printf("%s", target->contents);
    
}

int main(int argc, const char * argv[]) {

    for (int i = 0; i < NUMSENTS; i++) {
        sentence *my_sentence = sentence_init();
        assemble_parts(my_sentence);
        char* toprint = my_sentence->contents;
        fprintf(stdout, "%s", toprint);
        //fprintf(stdout, "butts");
        fflush(stdout);
    }

    return 0;
}
