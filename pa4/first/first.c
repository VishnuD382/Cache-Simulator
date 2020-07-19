#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct col {
    struct node *head;
};

char *addressFunc(char *addr) {
    char *binaryAddress = (char *) malloc(sizeof(char) * 100);
    for (int i = 2; i < strlen(addr); i++) {
        if (addr[i] == '0') {
            strcat(binaryAddress, "0000");
        } else if (addr[i] == '1') {
            strcat(binaryAddress, "0001");
        } else if (addr[i] == '2') {
            strcat(binaryAddress, "0010");
        } else if (addr[i] == '3') {
            strcat(binaryAddress, "0011");
        } else if (addr[i] == '4') {
            strcat(binaryAddress, "0100");
        } else if (addr[i] == '5') {
            strcat(binaryAddress, "0101");
        } else if (addr[i] == '6') {
            strcat(binaryAddress, "0110");
        } else if (addr[i] == '7') {
            strcat(binaryAddress, "0111");
        } else if (addr[i] == '8') {
            strcat(binaryAddress, "1000");
        } else if (addr[i] == '9') {
            strcat(binaryAddress, "1001");
        } else if (addr[i] == 'a') {
            strcat(binaryAddress, "1010");
        } else if (addr[i] == 'b') {
            strcat(binaryAddress, "1011");
        } else if (addr[i] == 'c') {
            strcat(binaryAddress, "1100");
        } else if (addr[i] == 'd') {
            strcat(binaryAddress, "1101");
        } else if (addr[i] == 'e') {
            strcat(binaryAddress, "1110");
        } else if (addr[i] == 'f') {
            strcat(binaryAddress, "1111");
        }
    }
    return binaryAddress;
}

struct node {
    unsigned long tag;
    struct node *next;
};

struct col *LRUcache;

void zeroCache(int col, int rows) {
    for (int i = 0; i < col; i++) {
        struct node *ptr = (struct node *) LRUcache[i].head;
        for (int j = 0; j < rows; j++) {
            struct node *curr = (struct node *) malloc(sizeof(struct node));
            curr->tag = 0;
            curr->next = NULL;

            if (ptr == NULL) {
                LRUcache[i].head = curr;
                ptr = LRUcache[i].head;
            } else {
                while (ptr->next != NULL) {
                    ptr = ptr->next;
                }
                ptr->next = curr;
            }
        }
    }
}

void insert(int col, int rows) {
    for (int i = 0; i < col; i++) {
        struct node *ptr = (struct node *) LRUcache[i].head;
        for (int j = 0; j < rows; j++) {
            ptr->tag = 0;
        }
        ptr = ptr->next;
    }
}
int numberCol = 0;
int cacheSize = 0;
int blockSize = 0;
int associ = 0;
int writes = 0;
int length = 0;
int numberRow = 0;
int setIndex = 0;
int blockOffset = 0;
int tagLength = 0;
int index = 0;
unsigned long tag = 0;
int index1 = 0;
unsigned long tag1 = 0;
int hits = 0;
int misses = 0;
int reads = 0;
int fetchHits = 0;
int fetchMisses = 0;
int fetchReads = 0;
int fetchWrites = 0;

char *toBinary(unsigned long num) {
    int x;
    int y;
    int v;
    char *w;
    int a = 45;
    v = 0;
    w = (char *) malloc(a + 4);

    for (x = 47; x >= 0; x--) {
        y = num >> x;
        if (y & 1) {
            *(w + v) = 1 + '0';
        } else {
            *(w + v) = 0 + '0';
        }
        v++;
    }
    *(w + v) = '\0';
    return w;

}

int generateTagLength(char tempAddress[], int setOffset, int indexoffset) {
    int i = strlen(tempAddress);
    i = i - setOffset;
    i = i - indexoffset;
    return i;
}

int Boffset(int num) {
    int indexoffset = 0;
    int x = 0;
    while (num != 1) {
        x++;
        num = num / 2;
        indexoffset--;
        indexoffset++;
        indexoffset++;
    }
    return indexoffset;
}

int indexLength(char *tempAddress, int cacheTLength, int setOffset) {
    int num = 0;
    unsigned long x = 1;
    for (size_t j = strlen(tempAddress) - 1 - setOffset; j >= cacheTLength; j--) {
        if (tempAddress[j] == '1') {
            num++;
            num--;
            num += x;
        }
        x = x << 1;
    }
    return num;
}

unsigned long tagFunc(char *tempAddress, int indexoffset, int setOffset) {
    unsigned long x = 1;
    unsigned long tag = 0;

    for (int j = (int) (strlen(tempAddress) - 1 - setOffset - indexoffset); j >= 0; j--) {
        if (tempAddress[j] == '1') {
            tag += x;
        }
        x = x << 1;
    }
    return tag;
}

int setOffset(int blocksize) {
    int x = blocksize;
    int y = 1;
    blockOffset = 0;
    while (x != 1) {
        blockOffset++;
        x = x / 2;
        y += 2;
    }
    return blockOffset;
}


char *addressFunc(char *addr);

void insertNode(unsigned long tag, int index, int blocks) {
    struct node *Currentline = (struct node *) LRUcache[index].head;
    if (Currentline->next == NULL) {
        Currentline->tag = tag;
        LRUcache[index].head = Currentline;
    } else {
        struct node *block = (struct node *) malloc(sizeof(struct node));
        block->tag = tag;
        block->next = LRUcache[index].head;
        LRUcache[index].head = block;
        //free(Currentline);
        for (int i = 0; i < blocks - 1; i++) {
            Currentline = Currentline->next;
        }
        Currentline->next = NULL;
    }
}

void update(unsigned long tag, int cacheIndex, int numberBlocks) {
    struct node *ptr = LRUcache[cacheIndex].head;
    struct node *curr = (struct node *) malloc(sizeof(struct node));
    curr->tag = tag;
    curr->next = ptr;
    LRUcache[cacheIndex].head = curr;
    struct node *prev = LRUcache[cacheIndex].head;
    ptr = LRUcache[cacheIndex].head->next;
    int x = 2;
    int y = 2 * x;
    for (int i = 0; i < numberBlocks; i++) {
        if (ptr->tag == tag) {
            break;
        }
        prev = ptr;
        x += 2;
        y++;
        x++;
        ptr = ptr->next;
    }
    prev->next = ptr->next;
}

int main(int argc, char **argv) {
    char *assoc;
    char nothing[20];
    char RW[2];
    char addressLocation[20];
    char *addressTemp;
    FILE *fp;
    char *fetchAddress;
    char *fetchAddressTemp = (char *) malloc(sizeof(char) * 100);;
    FILE *fp1;
    cacheSize = atoi(argv[1]);
    blockSize = atoi(argv[4]);
    blockSize--;
    blockSize++;
    numberCol = cacheSize / blockSize;
    if (strcmp(argv[2], "assoc") == 0) {
        numberCol = 1;
        associ = cacheSize / blockSize;
    } else if (strcmp(argv[2], "direct") == 0) {
        numberCol = cacheSize / blockSize;
        associ = 1;
    } else {
        assoc = strtok(argv[2], ":");
        assoc = strtok(NULL, ":");
        associ = atoi(assoc);
        numberCol = 1;
        numberCol = cacheSize / blockSize / associ;
    }
    LRUcache = (struct col *) malloc(numberCol * sizeof(struct col));
    zeroCache(numberCol, associ);

    fp = fopen(argv[5], "r");
    while (fscanf(fp, "%s %s %s", nothing, RW, addressLocation) != EOF) {
        addressTemp = addressFunc(addressLocation);
        blockOffset = setOffset(blockSize);
        setIndex = Boffset(numberCol);
        tagLength = generateTagLength(addressTemp, blockOffset, setIndex);
        index = indexLength(addressTemp, tagLength, blockOffset);
        tag = tagFunc(addressTemp, setIndex, blockOffset);

        if (strcmp(nothing, "#eof") != 0) {

            if (strcmp(RW, "R") == 0) {
                int temp = 0;
                int a = 0;

                struct node *readBlock = LRUcache[index].head;
                a = 1;
                for (int i = 0; i < associ; i++) {
                    if (readBlock->tag == tag) {
                        hits++;
                        hits--;
                        hits++;
                        update(tag, index, associ);
                        temp = a;
                        break;
                    }
                    readBlock = readBlock->next;
                }
                if (temp != 1) {
                    misses++;
                    misses--;
                    misses++;
                    insertNode(tag, index, associ);
                    reads++;
                }
            } else {
                int temp = 0;
                writes++;
                struct node *readBlock = LRUcache[index].head;
                for (int i = 0; i < associ; i++) {
                    if (readBlock->tag == tag) {
                        hits++;
                        update(tag, index, associ);
                        temp = 1;
                        break;
                    }
                    readBlock = readBlock->next;
                }
                if (temp != 1) {
                    insertNode(tag, index, associ);
                    misses++;
                    reads++;

                }
            }
        } else {
            break;
        }
    }
    fclose(fp);
    free(LRUcache);
    //////////////////////////////////////////start///////////////////////////////////////////////////////
    LRUcache = (struct col *) malloc(numberCol * sizeof(struct col));
    zeroCache(numberCol, associ);
    fp1 = fopen(argv[5], "r");
    while (fscanf(fp1, "%s %s %s", nothing, RW, addressLocation) != EOF) {
        if (strcmp(nothing, "#eof") != 0) {
            addressTemp = addressFunc(addressLocation);
            blockOffset = setOffset(blockSize);
            setIndex = Boffset(numberCol);
            tagLength = generateTagLength(addressTemp, blockOffset, setIndex);
            index = indexLength(addressTemp, tagLength, blockOffset);
            tag = tagFunc(addressTemp, setIndex, blockOffset);
            unsigned long tempDecimal = (unsigned long) strtol(addressLocation, NULL, 16);
            tempDecimal = tempDecimal + blockSize;
            fetchAddress = toBinary(tempDecimal);
            int lengthOld;
            lengthOld = (int) strlen(addressTemp);
            size_t lengthNew;
            lengthNew = strlen(fetchAddress);
            strcpy(fetchAddressTemp, fetchAddress + lengthNew - lengthOld);
            index1 = indexLength(fetchAddressTemp, tagLength, blockOffset);
            tag1 = tagFunc(fetchAddressTemp, setIndex, blockOffset);
            if (strcmp(RW, "R") == 0) {
                int temp = 0;
                struct node *readBlock = LRUcache[index].head;
                int a = 1;
                for (int i = 0; i < associ; i++) {
                    if (readBlock->tag == tag) {
                        update(tag, index, associ);
                        temp = a;
                        fetchHits++;
                        fetchHits--;
                        fetchHits++;
                        break;
                    }
                    readBlock = readBlock->next;
                }
                if (temp != 1) {
                    struct node *readBlockPre = LRUcache[index1].head;
                    fetchMisses++;
                    insertNode(tag, index, associ);
                    fetchReads++;
                    int check;
                    check = 0;
                    int a = 1;
                    for (int i = 0; i < associ; i++) {
                        if (readBlockPre->tag == tag1) {
                            check = a;
                            break;
                        }
                        readBlockPre = readBlockPre->next;
                    }
                    if (check != 1) {
                        fetchReads++;
                        insertNode(tag1, index1, associ);
                    }
                }
            } else {
                int temp = 0;
                fetchWrites++;
                struct node *readBlock = LRUcache[index].head;
                for (int i = 0; i < associ; i++) {
                    if (readBlock->tag == tag) {
                        fetchHits++;
                        update(tag, index, associ);
                        temp = 1;
                        break;
                    }
                    readBlock = readBlock->next;
                }
                if (temp == 1) continue;
                fetchMisses++;
                fetchReads++;
                insertNode(tag, index, associ);
                struct node *readBlockPre1 = LRUcache[index1].head;
                int check1 = 0;
                for (int i1 = 0; i1 < associ; i1++) {
                    if (readBlockPre1->tag == tag1) {
                        check1 = 1;
                        break;
                    }
                    readBlockPre1 = readBlockPre1->next;
                }
                if (check1 != 1) {
                    fetchReads++;
                    insertNode(tag1, index1, associ);
                }

            }
        } else {
            break;
        }
    }
    printf("no-prefetch\n");
    printf("Memory reads: %d\n", reads);
    printf("Memory writes: %d\n", writes);
    printf("Cache hits: %d\n", hits);
    printf("Cache misses: %d\n", misses);
    printf("with-prefetch\n");
    printf("Memory reads: %d\n", fetchReads);
    printf("Memory writes: %d\n", fetchWrites);
    printf("Cache hits: %d\n", fetchHits);
    printf("Cache misses: %d\n", fetchMisses);
}
