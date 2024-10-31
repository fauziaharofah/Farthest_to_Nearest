#include <cstdio>
#include <cmath>

float x[1000], y[1000], jarak[1000][1000], temp[1000][1000];
int urut[1000][1000], rute[1000][1000], permintaan[1000], kapasitas;
int jawaban[2000], jawaban2[1000], jawaban3[1000], pivot = 0, pivot2 = 0, pivot3 = 0;
float jaraktotal = 0, jaraktotal3 = 0, jaraktotal2 = 0;
int N, i, j, k = 1;
int l = 50, r = 50;
bool selesai = 1, flag[1000];

float hitung_jarak(int a, int b);
void urutkan();
int terjauh(int x);
int terdekat(int x);
void vrpvrp();
void vrpvrp5();
void vrpvrp6();
int terjauhx(int x0);
int terdekatx(int x0);
int terjauhy(int x0);
int terdekaty(int x0);
float min(float a, float b) {
  if (a <= b) return a;
  else return b;
}

int main() {
  FILE *fp;
  fp = fopen("hasil.txt", "w+");
  scanf("%d", &N);
  for (i = 0; i <= N; i++) {
    scanf("%f %f %d", &x[i], &y[i], &permintaan[i]);
    flag[i] = 0;
  }
  vrpvrp();
  vrpvrp5();
  vrpvrp6();
  if (min(jaraktotal,min(jaraktotal2,jaraktotal3)) == jaraktotal) 
    fprintf(fp, ",Solusi Inisial,,\n");
  else if (min(jaraktotal,min(jaraktotal2,jaraktotal3)) == jaraktotal2)
    fprintf(fp, ",,Solusi Inisial,\n");
  else if (min(jaraktotal,min(jaraktotal2,jaraktotal3)) == jaraktotal3)
    fprintf(fp, ",,,Solusi Inisial\n");
  fprintf(fp, ",FTNs,FTNx,FTNy\n");
  fprintf(fp, "Total Jarak,%f,%f,%f\n", jaraktotal, jaraktotal2, jaraktotal3);
  for (i = 0; i <= pivot || i <= pivot2 || i <= pivot3; i++) {
    if (i == 0) fprintf(fp, "Rute");
    fprintf(fp, ",");
    if (i <= pivot) fprintf(fp, "%d", jawaban[i]);
    fprintf(fp, ",");
    if (i <= pivot2) fprintf(fp, "%d", jawaban2[i]);
    fprintf(fp, ",");
    if (i <= pivot3) fprintf(fp, "%d\n", jawaban3[i]);
  } 
  return 0;
}

void vrpvrp6() {
  pivot3 = 0;
  jaraktotal3 = 0;
  for (i = 0; i <= 999; i++) {
    jawaban3[i] = 0;
    flag[i] = 0;
  }
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      jarak[i][j] = hitung_jarak(i, j);
      temp[i][j] = jarak[i][j];
      urut[i][j] = j;
      rute[i][j] = 0;
      // printf("%f ", jarak[i][j]);
    }
    // printf("\n");
  }
  urutkan();
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      // printf("%d ", urut[i][j]);
    }
    // printf("\n");
  }
  do {
    l = 500;
    r = 500;
    kapasitas = permintaan[0];
    jawaban3[pivot3] = 0;
    pivot3++;
    if (terjauhy(0) != -1) {
      rute[k][l] = terjauhy(0);
      flag[rute[k][l]] = 1;
      kapasitas -= permintaan[rute[k][l]];
      // printf("%d\n", kapasitas);
      if (terdekaty(rute[k][l]) != -1) {
        r++;
        rute[k][r] = terdekaty(rute[k][l]);
        flag[rute[k][r]] = 1;
        kapasitas -= permintaan[rute[k][r]];
      }
    }
    while (1) {
      if (jarak[rute[k][r]][0] > jarak[rute[k][l]][0]) {
        if (terdekaty(rute[k][r]) != -1) {
          rute[k][r+1] = terdekaty(rute[k][r]);
          flag[rute[k][r+1]] = 1;
          kapasitas -= permintaan[rute[k][r+1]];
          r++;
        } else break;
      } else {
        if (terdekaty(rute[k][l]) != -1) {
          rute[k][l-1] = terdekaty(rute[k][l]);
          flag[rute[k][l-1]] = 1;
          kapasitas -= permintaan[rute[k][l-1]];
          l--;
        } else break;
      }
      for (i = l; i <= r; i++) {
        // printf("%d ", rute[k][i]);
      }
      // printf("\n");
    }
    for (i = l; i <= r; i++) {
      // printf("%d ", rute[k][i]);
      jawaban3[pivot3] = rute[k][i];
      pivot3++;
    }
    // printf("\n");
    selesai = 1;
    for (i = 1; i <= N; i++) {
      if (!flag[i]) selesai = 0;
    }
    k++;
  } while (!selesai);
  jawaban3[pivot3] = 0;
  printf("Hasil FTNy: ");
  for (i = 0; i <= pivot3; i++) {
    printf("%d ", jawaban3[i]);
    jaraktotal3 += jarak[jawaban3[i]][jawaban3[i+1]];
  }
  printf("\n%f\n", jaraktotal3);
}

void vrpvrp5() {
  jaraktotal2 = 0;
  pivot2 = 0;
  for (i = 0; i <= 999; i++) {
    jawaban2[i] = 0;
    flag[i] = 0;
  }
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      jarak[i][j] = hitung_jarak(i, j);
      temp[i][j] = jarak[i][j];
      urut[i][j] = j;
      rute[i][j] = 0;
      // printf("%f ", jarak[i][j]);
    }
    // printf("\n");
  }
  urutkan();
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      // printf("%d ", urut[i][j]);
    }
    // printf("\n");
  }
  do {
    l = 500;
    r = 500;
    kapasitas = permintaan[0];
    jawaban2[pivot2] = 0;
    pivot2++;
    if (terjauhx(0) != -1) {
      rute[k][l] = terjauhx(0);
      flag[rute[k][l]] = 1;
      kapasitas -= permintaan[rute[k][l]];
      // printf("%d\n", kapasitas);
      if (terdekatx(rute[k][l]) != -1) {
        r++;
        rute[k][r] = terdekatx(rute[k][l]);
        flag[rute[k][r]] = 1;
        kapasitas -= permintaan[rute[k][r]];
      }
    }
    while (1) {
      if (jarak[rute[k][r]][0] > jarak[rute[k][l]][0]) {
        if (terdekatx(rute[k][r]) != -1) {
          rute[k][r+1] = terdekatx(rute[k][r]);
          flag[rute[k][r+1]] = 1;
          kapasitas -= permintaan[rute[k][r+1]];
          r++;
        } else break;
      } else {
        if (terdekatx(rute[k][l]) != -1) {
          rute[k][l-1] = terdekatx(rute[k][l]);
          flag[rute[k][l-1]] = 1;
          kapasitas -= permintaan[rute[k][l-1]];
          l--;
        } else break;
      }
      for (i = l; i <= r; i++) {
        // printf("%d ", rute[k][i]);
      }
      // printf("\n");
    }
    for (i = l; i <= r; i++) {
      // printf("%d ", rute[k][i]);
      jawaban2[pivot2] = rute[k][i];
      pivot2++;
      // printf("%d ", pivot2);
    }
    // printf("\n");
    selesai = 1;
    for (i = 1; i <= N; i++) {
      if (!flag[i]) selesai = 0;
    }
    k++;
  } while (!selesai);
  jawaban2[pivot2] = 0;
  printf("Hasil FTNx: ");
  for (i = 0; i <= pivot2; i++) {
    printf("%d ", jawaban2[i]);
    jaraktotal2 += jarak[jawaban2[i]][jawaban2[i+1]];
  }
  printf("\n%f\n", jaraktotal2);
}

void vrpvrp() {
  pivot = 0;
  jaraktotal = 0;
  for (i = 0; i <= 1000; i++) {
    jawaban[i] = 0;
    flag[i] = 0;
  }
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      jarak[i][j] = hitung_jarak(i, j);
      temp[i][j] = jarak[i][j];
      urut[i][j] = j;
      rute[i][j] = 0;
      // printf("%f ", jarak[i][j]);
    }
    // printf("\n");
  }
  urutkan();
  for (i = 0; i <= N; i++) {
    for (j = 0; j <= N; j++) {
      // printf("%d ", urut[i][j]);
    }
    // printf("\n");
  }
  do {
    l = 500;
    r = 500;
    kapasitas = permintaan[0];
    jawaban[pivot] = 0;
    pivot++;
    if (terjauh(0) != -1) {
      rute[k][l] = terjauh(0);
      flag[rute[k][l]] = 1;
      kapasitas -= permintaan[rute[k][l]];
      // printf("%d\n", kapasitas);
      if (terdekat(rute[k][l]) != -1) {
        r++;
        rute[k][r] = terdekat(rute[k][l]);
        flag[rute[k][r]] = 1;
        kapasitas -= permintaan[rute[k][r]];
      }
    }
    while (1) {
      if (jarak[rute[k][r]][0] > jarak[rute[k][l]][0]) {
        if (terdekat(rute[k][r]) != -1) {
          rute[k][r+1] = terdekat(rute[k][r]);
          flag[rute[k][r+1]] = 1;
          kapasitas -= permintaan[rute[k][r+1]];
          r++;
        } else break;
      } else {
        if (terdekat(rute[k][l]) != -1) {
          rute[k][l-1] = terdekat(rute[k][l]);
          flag[rute[k][l-1]] = 1;
          kapasitas -= permintaan[rute[k][l-1]];
          l--;
        } else break;
      }
      for (i = l; i <= r; i++) {
        // printf("%d ", rute[k][i]);
      }
      // printf("\n");
    }
    for (i = l; i <= r; i++) {
      // printf("%d ", rute[k][i]);
      jawaban[pivot] = rute[k][i];
      pivot++;
    }
    // printf("\n");
    selesai = 1;
    for (i = 1; i <= N; i++) {
      if (!flag[i]) selesai = 0;
    }
    k++;
  } while (!selesai);
  jawaban[pivot] = 0;
  printf("Hasil FTNs: ");
  for (i = 0; i <= pivot; i++) {
    printf("%d ", jawaban[i]);
    jaraktotal += jarak[jawaban[i]][jawaban[i+1]];
  }
  printf("\n%f\n", jaraktotal);
}

int terdekat(int x) {
  for (int i = 1; i <= N; i++) {
    if (!flag[urut[x][i]] && kapasitas-permintaan[urut[x][i]] >= 0 && urut[x][i] != x) return urut[x][i];
  }
  return -1;
}

int terjauh(int x) {
  for (int i = N; i >= 1; i--) {
    if(!flag[urut[x][i]] && kapasitas-permintaan[urut[x][i]] >= 0 && urut[x][i] != x) return urut[x][i];
  }
  return -1;
}

int terdekatx(int x0) {
  for (int i = 1; i <= N; i++) {
    if (!flag[urut[x0][i]] && kapasitas-permintaan[urut[x0][i]] >= 0 && urut[x0][i] != x0 && (x[urut[x0][i]]-x[0])*(x[x0]-x[0]) >= 0) return urut[x0][i];
  }
  return -1;
}

int terjauhx(int x0) {
  for (int i = N; i >= 1; i--) {
    if(!flag[urut[x0][i]] && kapasitas-permintaan[urut[x0][i]] >= 0 && urut[x0][i] != x0 && (x[urut[x0][i]]-x[0])*(x[x0]-x[0]) >= 0) return urut[x0][i];
  }
  return -1;
}
int terdekaty(int x0) {
  for (int i = 1; i <= N; i++) {
    if (!flag[urut[x0][i]] && kapasitas-permintaan[urut[x0][i]] >= 0 && urut[x0][i] != x0 && (y[urut[x0][i]]-y[0])*(y[x0]-y[0]) >= 0) return urut[x0][i];
  }
  return -1;
}

int terjauhy(int x0) {
  for (int i = N; i >= 1; i--) {
    if(!flag[urut[x0][i]] && kapasitas-permintaan[urut[x0][i]] >= 0 && urut[x0][i] != x0 && (y[urut[x0][i]]-y[0])*(y[x0]-y[0]) >= 0) return urut[x0][i];
  }
  return -1;
}

float hitung_jarak(int a, int b) {
  return sqrt(pow((x[a]-x[b]), 2) + pow((y[a]-y[b]), 2));
}

void urutkan() {
  float tmp;
  int tmp2;
  for (int k = 0; k <= N; k++) {
    bool swapped = true;
    int j = 0;
    while (swapped) {
      swapped = false;
      j++;
      for (int i = 1; i <= N - j; i++) {
        if (temp[k][i] > temp[k][i+1]) {
          tmp = temp[k][i];
          temp[k][i] = temp[k][i+1];
          temp[k][i+1] = tmp;
          tmp2 = urut[k][i];
          urut[k][i] = urut[k][i+1];
          urut[k][i+1] = tmp2;
          swapped = true;
        }
      }
    }
  }
  return;
}