## To compile:
    gcc -Wall -Wextra -o program src/main.c src/refuges.c -Iinclude

## For usage with provided files:
    Text file:
        ./program -f ./testcases/filename.txt
    Binary file:
        ./program -b ./testcases/filename.bin

Output files will be generated on testcases/

## For usage with stdin:
    ./program

## Example:
### Input
    5 8

    XXX-XXXX
    XX--XXXX
    -XXXXX--
    -XXX----
    XXXXXX--
### Output
    1
    XXX-XXXX
    XX--XXXX
    -XXXXXRR
    -XXXRRRR
    XXXXXXRR


## Folders
* **exp_outputs:** expected outputs for each input on testcases/
* **include:** header files
* **src:** source files
* **testcases:** provided test cases