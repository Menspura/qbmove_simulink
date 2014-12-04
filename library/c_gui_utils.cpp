#include <unistd.h>

#include "mex.h"
#include "../../qbAPI/src/qbmove_communications.h"
#include "matrix.h"



#define BROADCAST_ID 0


void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    int i = 0;
    int num_ports;
    char ports[10][255];
    comm_settings my_cs;
    int option = (int)mxGetScalar(prhs[0]);
    int id = (int)mxGetScalar(prhs[1]);
    char* port = mxArrayToString(prhs[2]);
    
    char id_str[5];
   
//     printf("option: %d\n", option);
//     printf("id: %d\n", id);
//     printf("port: %s\n", port);
    
    switch(option) {
        // retrieve ports
        case 0:
            printf("Retrieve ports\n");
            num_ports = RS485listPorts(ports);
            for (i=0; i<5; i++) {
                plhs[i] = mxCreateString(ports[i]);
            }
            break;
        // retrieve id
        case 1:
            printf("Retrieve current id\n");
            openRS485(&my_cs, port);
            id = 0;
            commGetParam(&my_cs, BROADCAST_ID, PARAM_ID, &id, 1);
            printf("current id is: %d\n", id);
            sprintf(id_str, "%d", id);
            plhs[0] = mxCreateString(id_str);
            closeRS485(&my_cs);
            break;
        // set id
        case 2:
            printf("Set new id: %d\n", id);
            openRS485(&my_cs, port);
            commSetParam(&my_cs, BROADCAST_ID, PARAM_ID, &id, 1);
            commStoreParams(&my_cs, BROADCAST_ID);
            closeRS485(&my_cs);
            break;
            
    }
    //printf("nlhs: %d\n", nlhs);
    //printf("nrhs: %d\n", nrhs);
        
    
    
//     int i = 0;
//     int j = 5;
//     
//     for (i=0; i<10; i++) {
//         j++;
//     }
//     
//     printf("i: %d\n", i);
//     printf("j: %d\n", j);
//     
//     printf("nlhs: %d\n", nlhs);
//     printf("nrhs: %d\n", nrhs);
//     
//     printf("input1: %d\n", (int)mxGetScalar(prhs[0]));
}