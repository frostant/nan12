
using namespace std;

void puts_error(int error){
    cout<<"errorID"<<error<<endl; 
    switch (error) {
        case -1: printf("this function is under develop!\n"); break;
        case 1: break; // the error has been displayed.
        default: 
            printf("Woooo! you find a new error. \n"); 
    }
    return ; 
} 