#include "Declaration.h"


Node *map_vehicle_Node(Node *root, Vehicle *v,  wing *a, wing *b, wing *c)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vehicle_number = v->vehicle_number;

    int i = v->owner_flat_id;
    int possible = 1; /**If this is 1 means it is possible for the owner to store in the same wing because has only
        1 wheeler
     **/

    Node *Vehicle_Node;
    char wing_id = v->wing_id;
    parking *P;
    flat *f;

    int done_on_the_same_wing = 0;
    if (wing_id == 'A')
    {
        P = &(a->pl);
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                f = &(a->fl[j][k]);
                if (f->flat_number == i)
                {
                    if (v->vehicle_type == '2')
                    {
                        f->Wheeler_2  += 1;
                    }
                    else
                    {
                        f->Wheeler_4 += 1;
                        if (f->Wheeler_2 > 1)
                        {
                            possible = 0;
                        }
                    }
                }
            }
        }
    }
    else if (wing_id == 'B')
    {
        P = &(b->pl);
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                f = &(b->fl[j][k]);
                if (f->flat_number == i)
                {
                    if (v->vehicle_type == '2')
                    {
                        f->Wheeler_2 += 1;
                    }
                    else
                    {
                        f->Wheeler_4 += 1;
                        if (f->Wheeler_4 > 1)
                        {
                            possible = 0;
                        }
                    }
                }
            }
        }
    }
    else
    {
        P = &(c->pl);
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                f = &(c->fl[j][k]);
                if (f->flat_number == i)
                {
                    if (v->vehicle_type == '2')
                    {
                        f->Wheeler_2 += 1;
                    }
                    else
                    {
                        f->Wheeler_4 += 1;
                        if (f->Wheeler_4 > 1)
                        {
                            possible = 0;
                        }
                    }
                }
            }
        }
    }

    int done = 0;
    char parking_type;
    int parking_position;
    if (v->vehicle_type == '2')
    {
        parking_type = 'C';
        for (int j = 0; j < 10 && done == 0; j++) //That 10 is the number of compact spots
        {
            if ((P->mapping_compact_spots[j] == 0) || P->mapping_compact_spots[j] == 1)
            {

                //Arre for this to do , I have to make a list to store all Guest Vehicle
                if (P->mapping_compact_spots[j] == 1)
                {
                    int vehicle_numbera = P->vehicle_number_stored_C[i];
                    Vehicle *vehicleTmp = searchVehicle(vehicle_root, vehicle_numbera);
                    Alloc_Guest_Car(v, a, b, c);
                }
                P->vehicle_number_stored_C[j] = v->vehicle_number;
                P->mapping_compact_spots[j] = 2;
                done = 1;
                parking_position = j;
                //printf("Parking spot is %d\n",parking_position) ;
                v->alloc = 1;
                done_on_the_same_wing = 1;
            }
        }
    }
    else if (v->vehicle_type == '4' && possible == 1)
    {
        parking_type = 'L';
        for (int j = 0; j < 10 && done == 0; j++) //THat 10 is the number of compact spots
        {
            if (P->mapping_large_spots[j] == 0 || P->mapping_large_spots[j] == 1)
            {

                if (P->mapping_large_spots[j] == 1)
                {
                    int vehicle_numbera = P->vehicle_number_stored_l[i];
                    Vehicle *vehicleTmp = searchVehicle(vehicle_root, vehicle_numbera);
                    Alloc_Guest_Car(v, a, b, c);
                }

                P->vehicle_number_stored_l[j] = v->vehicle_number;
                P->mapping_large_spots[j] = 2;
                done = 1;
                parking_position = j;
                v->alloc = 1;
                done_on_the_same_wing = 1;
            }
        }

        if (done == 0)
        {
            parking_type = 'C';
            for (int j = 0; j < 9 && done == 0; j++) //THat 10 is the number of compact spots
            {
                if (P->mapping_compact_spots[j] == 0 && P->mapping_compact_spots[j + 1] == 0 || (P->mapping_compact_spots[j] == 1 && P->mapping_compact_spots[j + 1] == 1))
                {

                    if (P->mapping_compact_spots[j] == 1)
                    {
                        int vehicle_numbera = P->vehicle_number_stored_C[i];
                        Vehicle *vehicleTmp = searchVehicle(vehicle_root, vehicle_numbera);
                        Alloc_Guest_Car(v, a, b, c);
                    }

                    P->vehicle_number_stored_C[j] = v->vehicle_number;
                    P->vehicle_number_stored_C[j + 1] = v->vehicle_number;
                    P->mapping_compact_spots[j] = 2;
                    P->mapping_compact_spots[j + 1] = 2;
                    done = 1;
                    parking_position = j;
                    v->alloc = 1;
                    done_on_the_same_wing = 1;
                }
            }
        }
    }

    /**If done is still 0 means the owner has more than 1 four wheeler or the vehicle is guest vehicle which can be
        determined by whether the flat_id of the owner is zero or not ;
        So in this case we'll allocate the vehicle to another wing but won't map it .
     **/

    if (wing_id == 'A' && done == 0)
    {
        P = &(b->pl);

        // Searching position in Wing B for the Car owner of Wing A ;
        parking_type = 'L';
        for (int j = 0; j < 10 && done == 0; j++) //THat 10 is the number of compact spots
        {
            if (P->mapping_large_spots[j] == 0)
            {
                P->vehicle_number_stored_l[j] = v->vehicle_number;
                P->mapping_large_spots[j] = 1;
                done = 1;
                parking_position = j;
            }
        }

        if (done == 0)
        {
            parking_type = 'C';
            for (int j = 0; j < 9 && done == 0; j++) //THat 10 is the number of compact spots
            {
                if (P->mapping_compact_spots[j] == 0 && P->mapping_compact_spots[j + 1] == 0)
                {
                    P->vehicle_number_stored_C[j] = v->vehicle_number;
                    P->vehicle_number_stored_C[j + 1] = v->vehicle_number;
                    P->mapping_compact_spots[j] = 1;
                    P->mapping_compact_spots[j + 1] = 1;
                    done = 1;
                    parking_position = j;
                }
            }
        }

        if (done == 0)
        {
            P = &(c->pl);
            parking_type = 'L';
            for (int j = 0; j < 10 && done == 0; j++) //THat 10 is the number of compact spots
            {
                if (P->mapping_large_spots[j] == 0)
                {
                    P->vehicle_number_stored_l[j] = v->vehicle_number;
                    P->mapping_large_spots[j] = 1;
                    done = 1;
                    parking_position = j;
                }
            }

            if (done == 0)
            {
                parking_type = 'C';
                for (int j = 0; j < 9 && done == 0; j++) //THat 10 is the number of compact spots
                {
                    if (P->mapping_compact_spots[j] == 0 && P->mapping_compact_spots[j + 1] == 0)
                    {
                        P->vehicle_number_stored_C[j] = v->vehicle_number;
                        P->vehicle_number_stored_C[j + 1] = v->vehicle_number;
                        P->mapping_compact_spots[j] = 1;
                        P->mapping_compact_spots[j + 1] = 1;
                        done = 1;
                        parking_position = j;
                    }
                }
            }
        }
    }

    else if (wing_id == 'B' && done == 0)
    {
        P = &(c->pl);

        // Searching position in Wing B for the Car owner of Wing A ;
        parking_type = 'L';
        for (int j = 0; j < 10 && done == 0; j++) //THat 10 is the number of compact spots
        {
            if (P->mapping_large_spots[j] == 0)
            {
                P->vehicle_number_stored_l[j] = v->vehicle_number;
                P->mapping_large_spots[j] = 1;
                done = 1;
                parking_position = j;
            }
        }

        if (done == 0)
        {
            parking_type = 'C';
            for (int j = 0; j < 9 && done == 0; j++) //THat 10 is the number of compact spots
            {
                if (P->mapping_compact_spots[j] == 0 && P->mapping_compact_spots[j + 1] == 0)
                {
                    P->vehicle_number_stored_C[j] = v->vehicle_number;
                    P->vehicle_number_stored_C[j + 1] = v->vehicle_number;
                    P->mapping_compact_spots[j] = 1;
                    P->mapping_compact_spots[j + 1] = 1;
                    done = 1;
                    parking_position = j;
                }
            }
        }

        if (done == 0)
        {
            P = &(a->pl);
            parking_type = 'L';
            for (int j = 0; j < 10 && done == 0; j++) //THat 10 is the number of compact spots
            {
                if (P->mapping_large_spots[j] == 0)
                {
                    P->vehicle_number_stored_l[j] = v->vehicle_number;
                    P->mapping_large_spots[j] = 1;
                    done = 1;
                    parking_position = j;
                }
            }

            if (done == 0)
            {
                parking_type = 'C';
                for (int j = 0; j < 9 && done == 0; j++) //THat 10 is the number of compact spots
                {
                    if (P->mapping_compact_spots[j] == 0 && P->mapping_compact_spots[j + 1] == 0)
                    {
                        P->vehicle_number_stored_C[j] = v->vehicle_number;
                        P->vehicle_number_stored_C[j + 1] = v->vehicle_number;
                        P->mapping_compact_spots[j] = 1;
                        P->mapping_compact_spots[j + 1] = 1;
                        done = 1;
                        parking_position = j;
                    }
                }
            }
        }
    }

    else if (wing_id == 'C' && done == 0)
    {
        P = &(a->pl);

        // Searching position in Wing B for the Car owner of Wing A ;
        parking_type = 'L';
        for (int j = 0; j < 10 && done == 0; j++) //THat 10 is the number of compact spots
        {
            if (P->mapping_large_spots[j] == 0)
            {
                P->vehicle_number_stored_l[j] = v->vehicle_number;
                P->mapping_large_spots[j] = 1;
                done = 1;
                parking_position = j;
            }
        }

        if (done == 0)
        {
            parking_type = 'C';
            for (int j = 0; j < 9 && done == 0; j++) //THat 10 is the number of compact spots
            {
                if (P->mapping_compact_spots[j] == 0 && P->mapping_compact_spots[j + 1] == 0)
                {
                    P->vehicle_number_stored_C[j] = v->vehicle_number;
                    P->vehicle_number_stored_C[j + 1] = v->vehicle_number;
                    P->mapping_compact_spots[j] = 1;
                    P->mapping_compact_spots[j + 1] = 1;
                    done = 1;
                    parking_position = j;
                }
            }
        }

        if (done == 0)
        {
            P = &(b->pl);
            parking_type = 'L';
            for (int j = 0; j < 10 && done == 0; j++) //THat 10 is the number of compact spots
            {
                if (P->mapping_large_spots[j] == 0)
                {
                    P->vehicle_number_stored_l[j] = v->vehicle_number;
                    P->mapping_large_spots[j] = 1;
                    done = 1;
                    parking_position = j;
                }
            }

            if (done == 0)
            {
                parking_type = 'C';
                for (int j = 0; j < 9 && done == 0; j++) //THat 10 is the number of compact spots
                {
                    if (P->mapping_compact_spots[j] == 0 && P->mapping_compact_spots[j + 1] == 0)
                    {
                        P->vehicle_number_stored_C[j] = v->vehicle_number;
                        P->vehicle_number_stored_C[j + 1] = v->vehicle_number;
                        P->mapping_compact_spots[j] = 1;
                        P->mapping_compact_spots[j + 1] = 1;
                        done = 1;
                        parking_position = j;
                    }
                }
            }
        }
    }

    //P[parking_position]->vehicle_number_stored_C = v->vehicle_number ;

    //Parking spot and type is perfectly allocated
    //printf("\n\nParking spot is %d and Parking type is %c\n\n",parking_position,parking_type) ;

    v->ParkingType = parking_type;
    v->parkingNumber = parking_position;

    //Even the allocation is done perfectly
    //printf("\n\nParking spot is %d and Parking type is %c\n\n",v->parkingNumber,v->ParkingType) ;

    if (done_on_the_same_wing == 1)
    {
        newNode->height = 1;

        newNode->left = NULL;
        newNode->right = NULL;

        //printf("Going to insert\n ")  ; Working
        //printf("%c\t\t %d\n\n",newNode->parking_type , newNode->parking_position) ; Working
        return insertNode(root, newNode);
    }
}


Node *Remove_vehicle_node(Node *root, int vhnumber, wing *a, wing *b, wing *c)
{

    Node *tmp = root ;


    tmp = searchNode(tmp,vhnumber) ;

    if(tmp != NULL)
    {
        root = deleteNode(root, vhnumber);
    }

    int done = 0 ;

    parking  *P  ;

    int nl , nc ;

    P = &(a->pl) ; nl = P->no_of_large_spots  ;nc = P->no_of_compact_spots  ;
    for(int i = 0 ; i<nl && done == 0 ; i++)
    {
        if(P->vehicle_number_stored_l[i] == vhnumber)
        {
            done = 1 ;
            P->status_large_spots[i]=0;
            P->mapping_large_spots[i] = 0 ;
            P->vehicle_number_stored_C[i] = 0  ;
        }
    }

    if(done == 0)
    {
        for(int i = 0 ; i<nc && done == 0 ; i++)
        {
            if(P->vehicle_number_stored_C[i] == vhnumber)
            {
                done = 1 ;
                P->status_compact_spots[i]=0;
                P->mapping_compact_spots[i] = 0 ;
                P->vehicle_number_stored_C[i] = 0  ;
            }
        }
    }

    if(done == 0)
    {
        P = &(b->pl) ; nl = P->no_of_large_spots  ;nc = P->no_of_compact_spots  ;
        for(int i = 0 ; i<nl && done == 0 ; i++)
        {
            if(P->vehicle_number_stored_l[i] == vhnumber)
            {
                done = 1 ;
                P->status_large_spots[i]=0;
                P->mapping_large_spots[i] = 0 ;
                P->vehicle_number_stored_C[i] = 0  ;
            }
        }

        if(done == 0)
        {
            for(int i = 0 ; i<nc && done == 0 ; i++)
            {
                if(P->vehicle_number_stored_C[i] == vhnumber)
                {
                    done = 1 ;
                    P->status_compact_spots[i]=0;
                    P->mapping_compact_spots[i] = 0 ;
                    P->vehicle_number_stored_C[i] = 0  ;
                }
            }
        }

    }

    if(done == 0)
    {
        P = &(c->pl) ; nl = P->no_of_large_spots  ;nc = P->no_of_compact_spots  ;
        for(int i = 0 ; i<nl && done == 0 ; i++)
        {
            if(P->vehicle_number_stored_l[i] == vhnumber)
            {
                done = 1 ;

                P->status_large_spots[i]=0;
                P->mapping_large_spots[i] = 0 ;
                P->vehicle_number_stored_C[i] = 0  ;
            }
        }

        if(done == 0)
        {
            for(int i = 0 ; i<nc && done == 0 ; i++)
            {
                if(P->vehicle_number_stored_C[i] == vhnumber)
                {
                    done = 1 ;
                    P->status_compact_spots[i]=0;
                    P->mapping_compact_spots[i] = 0 ;
                    P->vehicle_number_stored_C[i] = 0  ;
                }
            }
        }

    }

    return root  ;

}



