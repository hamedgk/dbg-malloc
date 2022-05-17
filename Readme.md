## Usage

```c
#include <stdio.h>
#include "dbgalloc.h"


void callback(struct alloc_reggetster_t *reg){
    printf("callback gets called and prints filename: %s\n", reg->file_name);
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
callback gets called and prints filename: main.c
NOT FREED 0x55cc0df942a0 at main.c:15
```

## Install
to build the library:
```bash
make
```

to install:
```bash
sudo make install
```
