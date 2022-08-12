int mu[M];
int min_divisor[M];
int ans[M];

void init() {
    iota(min_divisor, min_divisor + M, 0);
    mu[1] = 1;
    for (int i = 2; i < M; ++i) {
        if (min_divisor[i / min_divisor[i]] == min_divisor[i]) {
            mu[i] = 0;
        } else {
            mu[i] = -mu[i / min_divisor[i]];
        }
        if (min_divisor[i] == i) {
            for (int j = i * i; j < M; j += i) {
                min_divisor[j] = min(min_divisor[j], i);
            }
        }
    }

    for (int d = 1; d < M; ++d) {
        for (int i = d; i < M; i += d) {
            ans[i] += mu[i/d] * f(i);
        }
    }
}

/*
  if f = g * 1, then g = (f * mu)
*/