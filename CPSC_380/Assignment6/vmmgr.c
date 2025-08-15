# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define PAGEE_TABLE_SIZE 256
# define PAGE_SIZE 256
# define TLB_SIZE 16
# define FRAME_SIZE 256
# define PHYSICAL_MEMORY_SIZE 65536
# define BACKING_STORE_FILE "BACKING_STORE.bin"

typedef struct TLBItem {
    int page_number;
    int frame_number;
    int valid;
    int counter; 
} TLBItem;

typedef struct PageTableItem {
    // we don't need a frame number because the item will be    
        // indexed at the page number aka page 0 will be at index 0
        // of the page table
    int frame_number;
    int valid;
} PageTableItem;

// the TLB is an array of size 16 of TLBItems
TLBItem TLB[TLB_SIZE];

// the Page Table is an array of size 256 of PageTableItems
struct PageTableItem PageTable[PAGEE_TABLE_SIZE];

// keep track of stats at the end of the program

// should add up to total translations
int page_faults = 0;
int non_page_faults = 0; 

// should add up to total translations
int tlb_hits = 0;
int tlb_miss = 0;

int total_translations = 0;
int num_of_current_translation = 1;

// represents out backing store binary file
FILE *Backing_Store;

// other variables
int binary_of_address[32];
int binary_of_page_number[8];
int binary_of_page_offset[8];


void Initialize_Arrays() {
    // initialize the TLB (no address if equal to -1 so we can tell it is not an address)
    for (int i = 0; i < TLB_SIZE; i++) {
        TLB[i].page_number = -1;
        TLB[i].frame_number = -1;
        TLB[i].valid = 0;
        TLB[i].counter = 0;
    }

    // initialize the page table (no address if equal to -1 so we can tell it is not an address)
    for (int i = 0; i < PAGEE_TABLE_SIZE; i++) {
        PageTable[i].frame_number = -1;
        PageTable[i].valid = 0;
    }
}

int Open_BackingStore() {
    // "rb" will open a binary file for reading
    Backing_Store = fopen(BACKING_STORE_FILE, "rb"); 

    // if the file could not be opened 
    if (Backing_Store == NULL) {
        printf("The backing store file could not be opened");
        return -1;
    }

    return 0;
}

void Close_BackingStore() {
    fclose(Backing_Store);
}

void extract_address_portions(int virtual_address, int *page_number, int *page_offset) {
    int temp_virtual_address = virtual_address;

    // shifts the virtual address by 8 bits, then extracts the rightmost 8 bits from that shift
    *page_number = (virtual_address >> 8) & 0xFF;
    // extracts the rightmost 8 bits without any shifting
    *page_offset = virtual_address & 0xFF;


    // the binary representations of both values for verification
    // a. decimal -> 32-bit binary for virtual address 
    for (int k = 31; k >= 0; k--) {
        binary_of_address[k] = temp_virtual_address % 2;
        temp_virtual_address /= 2;
    }
    // b. extract page number bits (indices 16-23)
    int index = 0;
    for (int k = 16; k <= 23; k++) {
        binary_of_page_number[index] = binary_of_address[k];
        index++;
    }
    // c. extract page offset bits (indices 24-31)
    index = 0;
    for (int k = 24; k <= 31; k++) {
        binary_of_page_offset[index] = binary_of_address[k];
        index++;
    }
}

void print_translation_specs(int virtual_address, int *page_number, int *page_offset, int *frame_number, int *physical_address, unsigned char *byte_read) {
    // divider between translations for readability purposes
    printf("------ %d ------ \n", num_of_current_translation);

    // virtual address 
    printf("virtual address: %d    [ ", virtual_address);

    // binary translation
    int space_counter = 0;
    for (int j=0; j < 32; j++) {
        printf("%d", binary_of_address[j]);
        space_counter++;
        if (space_counter == 4) {
            printf(" ");
            space_counter = 0;
        }
    }
    printf("]\n");

    // page number
    printf("page number: %d    [ " , *page_number);
    space_counter = 0;
    for (int j=0; j < 8; j++) {
        printf("%d", binary_of_page_number[j]);
        space_counter++;
        if (space_counter == 4) {
            printf(" ");
            space_counter = 0;
        }
    }
    printf("]\n");
    


    // page offset
    printf("page offset: %d    [ ", *page_offset);
    space_counter = 0;
    for (int j=0; j < 8; j++) {
        printf("%d", binary_of_page_offset[j]);
        space_counter++;
        if (space_counter == 4) {
            printf(" ");
            space_counter = 0;
        }
    }
    printf("]\n");

    // frame number
    printf("frame number: %d\n", *frame_number);
    

    // physical address translation
    printf("translated physical address: %d\n", *physical_address);

    // signed byte at physical address
    printf("signed byte stored: %d\n", *byte_read);
    printf("\n");
}

void update_tlb(int *page_number,int *frame_number) {
    // update the tlb and the lru for the tlb
    int lru_index = 0;
    // finds the LRU item
    for (int i = 1; i < TLB_SIZE; i++) {
        if (TLB[i].counter < TLB[lru_index].counter) {
            lru_index = i;
        }
    }
    // updates the LRU item with our current item
    TLB[lru_index].page_number = *page_number;
    TLB[lru_index].frame_number = *frame_number;
    TLB[lru_index].valid = 1;
    TLB[lru_index].counter = num_of_current_translation;
}

int translate_address(int *page_number, int *frame_number, int *physical_address, int *page_offset, unsigned char *byte_read) {

    // TLB HIT
    bool tlbHit = false;
    for (int i = 0; i < TLB_SIZE; i++) {
        // if we find our page number in the tlb
        if (TLB[i].page_number == *page_number) {
            // save the frame number associated with it
            *frame_number = TLB[i].frame_number;
            tlbHit = true;
            tlb_hits++;

            // update the lru for the tlb (the item just used will be given the current translation number) -> so, the item with the lowest number is the LRU item
            TLB[i].counter = num_of_current_translation;

            break;
        }
    }

    // TLB MISS
    if (tlbHit == false) {
        // check if the page number is valid in the page table aka it has been loaded in
        if (PageTable[*page_number].valid) {
                // save the frame number associated with it 
                *frame_number = PageTable[*page_number].frame_number;
                
                // update the tlb and the lru for the tlb
                update_tlb(page_number, frame_number);
        }
        else { // if invalid, load in the page from the backing store aka page fault
            
            // for this program we know that the page number and the frame number are the same, but for the
            // purpose of the assignment, we will treat this as the page fault
            
            // load in the info to the page table for future use
            *frame_number = *page_number;
            PageTable[*page_number].frame_number = *frame_number;
            PageTable[*page_number].valid = 1;

            // update the tlb and the lru for the tlb
            update_tlb(page_number, frame_number);

            page_faults++;
        }
    }

    // translate to the physical address
    // the frame number * the frames per page + offset will be our final address
    *physical_address = (*frame_number * PAGE_SIZE) + *page_offset;

    // read the unsigned byte from physical memory
    if (*physical_address < PHYSICAL_MEMORY_SIZE) {
        fseek(Backing_Store, *physical_address, SEEK_SET);
        fread(byte_read, sizeof(char), 1, Backing_Store);
    }
    else {
        printf("Error: Physical address exceeds memory size\n");
        return -1;
    }


    return 0;
}

int process_virtual_address(int virtual_address) {
    
    int page_number_value;
    int page_offset_value;
    int frame_number_value;
    int physical_address_value;
    unsigned char byte_value;

    int *page_number = &page_number_value;
    int *page_offset = &page_offset_value;
    int *frame_number = &frame_number_value;
    int *physical_address = &physical_address_value;
    unsigned char *byte_read = &byte_value;

    // 1. Extract the page number and the page offset
    extract_address_portions(virtual_address, page_number, page_offset);

    // 2. Translate the address
    if (translate_address(page_number, frame_number, physical_address, page_offset, byte_read) == -1) {
        return -1;
    }    

    // 3. Print the information we want from this translation
    print_translation_specs(virtual_address, page_number, page_offset, frame_number, physical_address, byte_read);    

    num_of_current_translation++;

    return 0;
}


int main(int argc, char *argv[]) {
    FILE *addresses;

    // read in the user arguments from the command line
        // <program name> <input file name>

    // if incorrect arguments, prompt directions 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file name> \n", argv[0]);
        return -1;
    }

    
    Initialize_Arrays();
    if (Open_BackingStore() == -1) {
            return -1;
    }
    

    // read in the logical addresses from the text file
    addresses = fopen(argv[1], "r"); // "r" opens for reading

    // if the file could not be opened
    if (addresses == NULL) {
        printf("The input file could not be opened \n");
        // dont leave the backing store file open
        Close_BackingStore();
        return -1;
    }

    // for each address we read from the input file, translate it and produce the output we need
    int current_virtual_address;
    // fscanf will never return NULL so we must use EOF to represent End of File
    while (fscanf(addresses, "%d", &current_virtual_address) != EOF) {
        // this function will handle the translation process of the address
        if (process_virtual_address(current_virtual_address) == -1) {
            return -1;
        }

        // increment the amount of addresses we have processed
        total_translations++;
    }

    // output stats
    printf("------ Overall Stats ------\n");
    printf("Page-fault rate: %f\n", (float)page_faults/(float)total_translations);
    printf("TLB-hit rate: %f\n", (float)tlb_hits/(float)total_translations);



    // dont leave the input & backing store files open
    fclose(addresses);
    Close_BackingStore();

    return 0;

}