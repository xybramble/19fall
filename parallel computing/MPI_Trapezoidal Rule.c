/* Parallelizing the Trapezoidal Rule:
1. Partition problem solution into tasks.
2. Identify communication channels between tasks.
3. Aggregate tasks into composite tasks.
4. Map composite tasks to cores. */
int main(void) {
  int my_rank, comm_sz, n = 1024, local_n;
  double a = 0.0, b = 3.0, h, local_a, local_b;
  double local_int, total_int;
  int source;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* my_rank is the process making this call */
  MPI_Comm_size(MPI_CONN_WORLD, &comm_sz); /* number of processes in the communicator */
  
  h = (b-a)/n; /* h is the same for all processes */
  local_n = n/comm_sz; /* number of trapezoids */
  
  local_a = a + my_rank*local_n*h;
  local_b = local_a + local_n*h;
  local_int = Trap(local_a, local_b, local_n, h); /* the function to compute square of trapezoid(s) */
  
  /* Message matching */
  if (my_rank != 0) {
    MPI_Send(&local_int, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); /* MPI_Send: the 5th para is send_tag */
  } else {
    total_int = local_int;
    for (source = 1; source < comm_sz; source++) {
      MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); /* MPI_Recv: the 5th para is recv_tag */
      total_int += local_int;
    }
  }
  
  if (my_rank == 0) {
    printf("With n = %d trapezoide, our estimate \n", n);
    printf("of the integral from %f to %f = %.15e\n", a, b, total_int);
  }
  MPI_Finalize();
  return 0;
} /* main */

double Trap(
  double left_endpt, /* in */
  double right_endpt, /* in */
  int trap_count, /* in */
  double base_len /* in */) {
  double estmate, x;
  int i;
  
  estimate = (f(left_endft) + f(right))/2.0;
  for (i=1; i<= trap_count-1; i++) {
    x = left_endft + i*base_len;
    estimate += f(x);
  }
  estimate = estimate*base_len;
  
  return estimate;
} /* Trap */
      
