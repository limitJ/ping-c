//
// Created by 58252 on 2020/4/13.
//

#ifndef _RESULT_H_
#define _RESULT_H_ 1
#define IP 0
#define ERROR 1
typedef struct Result_{
    int status;
    char message[32];
    void* obj;
}Result;

#endif //PING_RESULT_H
