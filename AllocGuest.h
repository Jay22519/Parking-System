
void Alloc_Guest_Car(Vehicle *v, wing *a, wing *b, wing *c)
{
    parking *P = &(a->pl);

    char vehicle_type = v->vehicle_type;
    int done = 0;
    if (vehicle_type == '2')
    {
        for (int i = 0; i < 10 && done == 0; i++)
        {
            if (P->mapping_compact_spots[i] == 0)
            {
                P->mapping_compact_spots[i] = 1;
                P->vehicle_number_stored_C[i] = v->vehicle_number;
                v->ParkingType = 'C';
                v->parkingNumber = i;
                v->wing_id = 'A';
                done = 1;
            }
        }

        if (done == 0)
        {
            P = &(b->pl);
            for (int i = 0; i < 10 && done == 0; i++)
            {
                if (P->mapping_compact_spots[i] == 0)
                {
                    P->mapping_compact_spots[i] = 1;
                    P->vehicle_number_stored_C[i] = v->vehicle_number;
                    v->ParkingType = 'C';
                    v->parkingNumber = i;
                    v->wing_id = 'B';
                    done = 1;
                }
            }
        }

        if (done == 0)
        {
            P = &(c->pl);
            for (int i = 0; i < 10 && done == 0; i++)
            {
                if (P->mapping_compact_spots[i] == 0)
                {
                    P->mapping_compact_spots[i] = 1;
                    P->vehicle_number_stored_C[i] = v->vehicle_number;
                    v->ParkingType = 'C';
                    v->parkingNumber = i;
                    v->wing_id = 'C';
                    done = 1;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < 10 && done == 0; i++)
        {
            if (P->mapping_large_spots[i] == 0)
            {
                P->mapping_large_spots[i] = 1;
                P->vehicle_number_stored_l[i] = v->vehicle_number;
                v->ParkingType = 'L';
                v->parkingNumber = i;
                v->wing_id = 'A';
                done = 1;
            }
        }

        if (done == 0)
        {
            P = &(b->pl);
            for (int i = 0; i < 10 && done == 0; i++)
            {
                if (P->mapping_large_spots[i] == 0)
                {
                    P->mapping_large_spots[i] = 1;
                    P->vehicle_number_stored_l[i] = v->vehicle_number;
                    v->ParkingType = 'L';
                    v->parkingNumber = i;
                    v->wing_id = 'B';
                    done = 1;
                }
            }
        }

        if (done == 0)
        {
            P = &(c->pl);
            for (int i = 0; i < 10 && done == 0; i++)
            {
                if (P->mapping_large_spots[i] == 0)
                {
                    P->mapping_large_spots[i] = 1;
                    P->vehicle_number_stored_l[i] = v->vehicle_number;
                    v->ParkingType = 'L';
                    v->parkingNumber = i;
                    v->wing_id = 'C';
                    done = 1;
                }
            }
        }

        if (done == 0)
        {
            for (int i = 0; i < 10 && done == 0; i++)
            {
                if (P->mapping_compact_spots[i] == 0 && P->mapping_compact_spots[i + 1] == 0)
                {
                    P->mapping_compact_spots[i] = 1;
                    P->mapping_compact_spots[i + 1] = 1;
                    P->vehicle_number_stored_C[i] = v->vehicle_number;
                    P->vehicle_number_stored_C[i + 1] = v->vehicle_number;
                    v->ParkingType = 'C';
                    v->parkingNumber = i;
                    v->wing_id = 'A';
                    done = 1;
                }
            }

            if (done == 0)
            {
                P = &(b->pl);
                for (int i = 0; i < 10 && done == 0; i++)
                {
                    if (P->mapping_compact_spots[i] == 0 && P->mapping_compact_spots[i + 1] == 0)
                    {
                        P->mapping_compact_spots[i] = 1;
                        P->mapping_compact_spots[i + 1] = 1;
                        P->vehicle_number_stored_C[i] = v->vehicle_number;
                        P->vehicle_number_stored_C[i + 1] = v->vehicle_number;
                        v->ParkingType = 'C';
                        v->parkingNumber = i;
                        v->wing_id = 'B';
                        done = 1;
                    }
                }
            }

            if (done == 0)
            {
                P = &(c->pl);
                for (int i = 0; i < 10 && done == 0; i++)
                {
                    if (P->mapping_compact_spots[i] == 0 && P->mapping_compact_spots[i + 1] == 0)
                    {
                        P->mapping_compact_spots[i] = 1;
                        P->mapping_compact_spots[i + 1] = 1;
                        P->vehicle_number_stored_C[i] = v->vehicle_number;
                        P->vehicle_number_stored_C[i + 1] = v->vehicle_number;
                        v->ParkingType = 'C';
                        v->parkingNumber = i;
                        v->wing_id = 'C';
                        done = 1;
                    }
                }
            }
        }
    }
}
