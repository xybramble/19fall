/* serial 
Start: 5, 9, 4, 3
Even phase: compare-swap (5,9) and (4,3) getting the list 5, 9, 3, 4
Odd phase: compare-swap (9,3) getting the list 5, 3, 9, 4
Even phase: compare-swap (5,3) and (9,4) getting the list 3, 5, 4, 9
Odd phase: compare-swap (5,4) getting the list 3, 4, 5, 9
*/
void Odd_even_sort( int a[], /* in/out */ int n, /* in */ ) {
  int phase, i, temp;
  for (phase = 0; phase < n; phase++)
    if (phase % 2 == 0) { /* even phase */
      for (i=1; i<n; i += 2)
        if(a[i-1] > a[i]) {
          temp = a[i];
          a[i] = a[i-1];
          a[i-1] = temp;
        }
    } else { /* odd phase */
      for (i=1; i<n-1; i+= 2)
        if (a[i] > a[i+1]) {
          temp = a[i];
          a[i] = a[i+1];
          a[i+1] = temp;
        }
    }
} /* odd_even sort */

/* parallel odd-even transposition sort 
start: 4 processes
after local sort
after phase 0: even. process0 and process1, process2 and process3
after phase 1: odd. process1 and process2
after phase 2: even. process0 and process1, process2 and process3
after phase 3: odd. process1 and process2
pseudo-code: 
Sort local keys:
for (phase=0; phase<comm_sz; phase++) {
  partner = Compute_partner(phase, my_rank);
  if (I'm not idle) {
      Send my keys to partner;
      Receive keys from partner;
      if (my_rank < partner)
        Keep smaller keys;
      else
        Keep larger keys;
      }
}
*/
/* Compute_partner */
if (phase % 2 == 0) /*even phase*/
  if (my_rank % 2 != 0) /*odd rank*/
    partner = my_rank - 1;
  else /*even rank*/
    partner = my_rank + 1;
else /*odd phase*/
  if (my_rank % 2 != 0) /*odd rank*/
    partner = my_rank + 1;
  else /*even rank*/
    partner = my_rank - 1;

if (partner == -1 || partner == comm_sz)
  partner = MPI_PROC_NULL

