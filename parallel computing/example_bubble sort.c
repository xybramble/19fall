/* First OpenMP Odd-Even Sort */
for (phase = 0; phase < n; phase++) {
  if(phase %2 == 0)
    # pragma omp parallel for num_threads(thread_count) \
      default(none) shared(a, n) private(i, tmp)
    for (i = 1; i < n; i += 2) {
      if (a[i-1] > a[i]) {
        tmp = a[i-1];
        a[i-1] = a[i];
        a[i] = tmp;
      }
    }
  else
    # pragma omp parallel for num_threads(thread_count) \
      default(none) shared(a, n) private(i, tmp)
    for (i = i; i < n-1; i += 2) {
      if(a[i] > a[i+1]) {
        tmp = a[i+1];
        a[i+1] = a[i];
        a[i] = tmp;
      }
    }
}

/* Second OpenMP Odd-Even Sort */
# pragma omp parallel for num_threads(thread_count) \
  default(none) shared(a, n) private(i, tmp)
for (phase = 0; phase < n; phase++) {
  if(phase %2 == 0)
    # pragma omp for
    for (i = 1; i < n; i += 2) {
      if (a[i-1] > a[i]) {
        tmp = a[i-1];
        a[i-1] = a[i];
        a[i] = tmp;
      }
    }
  else
    # pragma omp for
    for (i = i; i < n-1; i += 2) {
      if(a[i] > a[i+1]) {
        tmp = a[i+1];
        a[i+1] = a[i];
        a[i] = tmp;
      }
    }
}
