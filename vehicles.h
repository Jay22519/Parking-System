/*** This file containd the detail about the vehicle struct and realted utility function ***/

typedef struct vehicle
{
    int vehicle_number ;
    char vehicle_type  ;  //2 for 2 wheeler and 4 for 4 wheeler
    char wing_id ;
    int owner_flat_id ;  //Flat id of the owner of the vehicle . If this is 0 so it is a guest vehicle
    int alloc ;
    // If alloc is 1 means the given vehicle is permanently mapped
    // If alloc is 0 ,so either it is guest vehicle or extra vehicle of the car owner

    int parkingNumber ;
    char ParkingType ;

    struct vehicle *next ;

}Vehicle;


void initialize_vehicle(Vehicle *v,int vehicle_number , char vehicle_type,char wing_id , int owner_flat_id)
{
    v->vehicle_number = vehicle_number ;
    v->vehicle_type = vehicle_type ;
    v->wing_id = wing_id ; //This will be D if it is a guest vehicle
    v->owner_flat_id = owner_flat_id ;
    v->alloc = 0 ;
    v->parkingNumber = 0 ; //This is dummy assignment
    v->ParkingType = 'A' ; // This is dummy assignment

    v->next = NULL ;
}

void show_vehicle(Vehicle *v)
{

    printf("Vehicle details are  : \n") ;
    printf("Vehicle number  %d\n" ,v->vehicle_number) ;
    printf("Vehicle Type  %c \n",v->vehicle_type) ;
    printf("Wing of vehicle  %c\n",v->wing_id) ;
    printf("Flat number of the owner of vehicle %d\n",v->owner_flat_id) ;

}



Vehicle *insertVehicle(Vehicle *root , Vehicle *newVehicle)
{
    if(root == NULL)
    {
        return newVehicle ;
    }
    else
    {
        Vehicle *tmp = root  ;

        while(tmp->next != NULL)
        {
            tmp = tmp->next ;
        }
        tmp->next = newVehicle ;
    }

    return root ;
}

Vehicle *searchVehicle(Vehicle *root , int number)
{
    Vehicle *tmp = root  ;
    while(tmp!=NULL && tmp->vehicle_number != number)
    {
        tmp = tmp->next ;
    }

    return tmp ;
}


void printVehicleList(Vehicle *root)
{
    Vehicle *tmp = root ;
    while(tmp!=NULL)
    {
        show_vehicle(tmp) ;
        printf("\n\n") ;
        tmp = tmp->next ;
    }
}


//This is the head to my Vehicle Linked List
 Vehicle *vehicle_root = NULL ;

