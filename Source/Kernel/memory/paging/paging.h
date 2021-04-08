#ifndef _PAGING_H_
#define _PAGING_H_





void initPaging();



unsigned int page_directory[1024] __attribute__((aligned(4096)));

unsigned int first_page_table[1024] __attribute__((aligned(4096)));


 void idpaging(unsigned int *first_pte, unsigned int from, int size);

extern void enablePaging(unsigned int*);

#endif