/*serial pseudo-code*/
/*for each row of A*/
for (i=0;i<m;i++) {
    y[i] = 0.0;
    /*for each element of the row and each element of x*/
    for (j=0;j<n;j++)
    y[i] += A[i][j]*x[j];
}

/*pthreads matrix-vector multiplication*/
void *Pth_mat_vect(void* rank) {
    long my_rank = (long) rank;
    int i,j;
    int local_m = m/thread_count; //totally m rows, each thread has local_m rows
    int my_first_row = my_rank*local_m;
    int my_last_row = (my_rank+1)*local_m - 1;
    
    for (i=my_first_row;i<=my_last_row;i++) {
        y[i] = 0.0;
        for (j=0;j<n;j++)
            y[i] += A[i][j]*x[j];
    }
    return NULL;
} /*Pth_mat_vect*/
