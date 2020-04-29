#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#include<string.h>

#include "structures.h"
#include "vehicles.h"
#include "AVL_Data.h"
#include "mapVehicle.h"
#include "AllocGuest.h"
#include "Declaration.h"
#include "CommandList.h"
#include "Operations.h"
#include "ParkVehicle.h"
#include <time.h>


void preOrder(Node *root) ;
int main()
{
    Node *root = NULL;

    History *h = NULL ;


    int nL,nC ;

    printf("Welcome !!!!! \n") ;
    printf("Enter the number of comapct spots \t") ;
    scanf("%d",&nC) ;
    printf("Enter the number of large spots \t")  ;
    scanf("%d",&nL) ;


    wing a,b,c;
    newWing(&a,'A',10,10);
    newWing(&b,'B',10,10);
    newWing(&c,'C',10,10);

    printf("\n\n The input is done and all the wings are initialised") ;

    Vehicle *my_list ; char vehicle_name[100] ; int index = 0 ;


    int command = -1 ;
    Command() ;

        printf("Enter command\n") ;
        scanf("%d",&command) ;

    while(command != 0)
    {

        if(command == 1)
        {
            printf("Enter 1 to wing number if you want to see it\n") ;
            int A,B,C ;
            scanf("%d%d%d",&A,&B,&C) ;
            if(A==1)
            {
                show_wing(a) ;
            }

            if(B==1)
            {
                show_wing(b) ;
            }

            if(C == 1)
            {
                show_wing(c) ;
            }
        }

        else if(command == 2)
        {
            Vehicle *v = (Vehicle*)malloc(sizeof(Vehicle)) ;
            int vehicle_number ;
            char vehicle_type ; int tmp ;
            char wing_id ;
            int flat_number ;
            printf("Enter Vehicle Type\t") ;
            scanf("%d",&tmp) ;
            if(tmp == 2)
            {
                vehicle_type = '2' ;
            }
            else
            {
                vehicle_type = '4' ;
            }
            printf("Enter Vehicle number\t") ;
            scanf("%d",&vehicle_number) ;
            printf("Enter Flat_number\t") ;
            scanf("%d",&flat_number) ;
            printf("Enter Wing_id\t") ;
            scanf("%d",&tmp) ;
            if(tmp == '1')
            {
                wing_id = 'A' ;
            }
            else if(tmp == 2)
            {
                wing_id = 'B' ;
            }
            else
            {
                wing_id = 'C' ;
            }

            initialize_vehicle(v,vehicle_number,vehicle_type,wing_id,flat_number) ;
            printf("Done with initilization\n") ;
            vehicle_root = insertVehicle(vehicle_root,v) ;




        }
        else if(command == 3)
        {
            printVehicleList(vehicle_root) ;
        }

        else if(command == 4)
        {
            int vehicle_number ;
            printf("Enter the vehicle number which you want to map\t") ;
            scanf("%d",&vehicle_number) ;
            printf("\n") ;
            Vehicle *v = searchVehicle(vehicle_root,vehicle_number) ;

            root = map_vehicle_Node(root,v,&a,&b,&c) ;
        }
        else if(command == 5)
        {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            int date ; int time ;
            date = tm.tm_year + 1900 +  tm.tm_mon + 1 +  tm.tm_mday ;
            time = tm.tm_hour + tm.tm_min + tm.tm_sec ;

            int vehicle_number ;
            printf("Enter the vehicle number which you want to map\t") ;
            scanf("%d",&vehicle_number) ;
            printf("\n") ;

            Vehicle *v = searchVehicle(vehicle_root,vehicle_number) ;
            char vehicle_type = v->vehicle_type ;

            h = Park_Vehicle(vehicle_root,vehicle_number,vehicle_type,&a,&b,&c,date,time,h) ;
        }
        else if(command == 6)
        {
            preOrder(root) ;
        }

        else if(command == 7)
        {
            int vehicle_number ;
            printf("Enter the vehicle number which you want to map\t") ;
            scanf("%d",&vehicle_number) ;
            printf("\n") ;

            root = Remove_vehicle_node(root,vehicle_number,&,&b,&c) ;
        }
        else if(command == 8)
        {
            Parking_status(a,b,c) ;
        }

        else if(command == 9)
        {
            int date ; printf("Enter the date\t") ; scanf("%d",&date) ;
            Display_Visitors(h,date) ;
        }

        else if(command == 10)
        {
            PrintHistory(h) ;
        }

        printf("\nEnter command\n") ;
        scanf("%d",&command) ;

    }



    return 0 ;
}



void preOrder(Node *root)
{
    //printf("\n\nEntering the pre-order function\n\n") ;
    if (root != NULL)
    {
        int vehicle_number = root->vehicle_number;

        Vehicle *z = searchVehicle(vehicle_root, vehicle_number);
        show_vehicle(z);
        preOrder(root->left);

        preOrder(root->right);
    }
}
