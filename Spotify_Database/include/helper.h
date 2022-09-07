#ifndef F1B8C669_4619_4D7D_BF00_FB7841E45500
#define F1B8C669_4619_4D7D_BF00_FB7841E45500

#include <string.h>
#include <string>
#include <chrono>


void toLowerAll(char* name){
    for (int i = 0; i < strlen(name); i++)
    {
        // if(name[i]=='\''){
        //     name[i] = ' ';
        // }
        // else{
            name[i] = tolower(name[i]);
        //}
    }
}



#endif /* F1B8C669_4619_4D7D_BF00_FB7841E45500 */
