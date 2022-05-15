## Usage

```c
#include <stdio.h>
#include "dbgalloc.h"


void callback(struct alloc_register_t *reg){
    printf("%s\n", reg->file_name);
}


int main(){
    INIT_ALLOC_REGS();
        


    int *a = (int*)DBGALLOC(sizeof(int)); //oh forgot to deallocate!
        

    //DBGFREE(a);


    INVOKE_CALLBACK(callback); //invokes a callback function on unfreed pointers
    NOT_FREED(); //outputs unfreed pointers
    return 0;
}

```

## Output
```text
main.c
NOT FREED 0x55cc0df942a0 at main.c:15
```