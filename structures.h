/*** In this file all the structures used have been defined ***/


typedef struct Flat
{
    int flat_number ;
    int Wheeler_2 ;
    int Wheeler_4 ;
    int floor ;
    char wing_id;

}flat ;

void newFlat(char w,int fi,int notwo,int nofour,int fl,flat *a){
    a->wing_id=w;
    a->flat_number =fi;
    a->Wheeler_2 =notwo;
    a->Wheeler_4 =nofour;
    a->floor=fl;
}

void print_flat(flat a){
    printf("\n Below is the Flat information :\n");
    printf("Floor number            : %d\n",a.floor);
    printf("Wing of the flat        : %c\n",a.wing_id);
    printf("Flat number is          : %d\n",a.flat_number);
    printf("Number of 2 wheelers    : %d\n",a.Wheeler_2);
    printf("Number of 4 wheelers  : %d\n",a.Wheeler_4);
    printf("\n\n") ;
}

// Done with the definition , declaration and printing function of struct Flat

#define MAX_SPOTS 1000

typedef struct parking_Struct{
    int no_of_compact_spots, no_of_large_spots ;
    int status_compact_spots[MAX_SPOTS], status_large_spots[MAX_SPOTS] ;
    int mapping_compact_spots[MAX_SPOTS], mapping_large_spots[MAX_SPOTS];
    char dedicated_wing;

    int vehicle_number_stored_C[MAX_SPOTS] ,vehicle_number_stored_l[MAX_SPOTS]  ;

}parking;


void newParking(int nc,int nl,char pl ,parking *a){
    a->dedicated_wing=pl;
    a->no_of_large_spots=nl;
    a->no_of_compact_spots=nc;

    int i;
    for (i=0;i<nc;i++){
        a->status_compact_spots[i]=0;
        a->mapping_compact_spots[i] = 0 ;
        a->vehicle_number_stored_C[i] = 0  ;
        //0 means available , 1 means guest car standing or extra car standing which will be overidden
    }
    for (i=0;i<nl;i++){
        a->status_large_spots[i]=0;
        a->mapping_large_spots[i] = 0  ;
        a->vehicle_number_stored_l[i] = 0 ;
        //0 means available , 1 means guest car standing or extra car standing which will be overidden
    }
}
void print_parking_detail(parking a){
    printf("\n Parking detail are :\n");
    printf("Wing             : %c\n",a.dedicated_wing);
    printf("Number of large spots        : %d\n",a.no_of_large_spots);
    printf("Number of compact spots      : %d\n",a.no_of_compact_spots);
    printf("Mapping_compact_spots:\n");
    int i;
    for(i=0;i<a.no_of_compact_spots;i++){
        printf("%d  ",a.mapping_compact_spots[i]);
    }
    printf("\n");
    printf("Mapping_large_spots:\n");
    for(i=0;i<a.no_of_large_spots;i++){
        printf("%d  ",a.mapping_large_spots[i]);
    }


    printf("Vehicle_Number in Compact_spots:\n");

    for(i=0;i<a.no_of_compact_spots;i++){
        printf("%d  ",a.vehicle_number_stored_C[i]);
    }
    printf("\n");
    printf("Vehicle Number in large_spots:\n");
    for(i=0;i<a.no_of_large_spots;i++){
        printf("%d  ",a.vehicle_number_stored_l[i]);
    }
    printf("\n\n");

    printf("Status_compact_spots:\n");

    for(i=0;i<a.no_of_compact_spots;i++){
        printf("%d  ",a.status_compact_spots[i]);
    }
    printf("\n");
    printf("Status_large_spots:\n");
    for(i=0;i<a.no_of_large_spots;i++){
        printf("%d  ",a.status_large_spots[i]);
    }

    printf("\n\n") ;
}



//Done with the declaration , definition and printing function of parking floor struct


typedef struct building{
    flat fl[9][3];
    char wing_id;
    parking pl;
    // floor ,flat number
} wing;


void newWing(wing *a,char wi,int nc,int nl){
    a->wing_id=wi;
    int i,j;
    for (i=0;i<9;i++){
        for (j=0;j<4;j++){
            newFlat(wi,10*i + j+1,0,0,i+1,&a->fl[i][j]);
        }
    }
    newParking(nc,nl,wi, &a->pl);
}


void show_wing(wing a){
    printf("Wing is :%c\n",a.wing_id);
    int i,j;
    for (i=0;i<9;i++){
        for (j=0;j<4;j++){
            print_flat(a.fl[i][j]);
        }
    }
    print_parking_detail(a.pl);
}



//Done with declaration , definition and printing of wing struct



