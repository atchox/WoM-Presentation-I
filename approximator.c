/*
The program generates random co-ordinates and tests each co-ordinate to check if its closer to the center than any of the edges. An experiment consists of N tries with each outcome being a success or a failure (depending on whether or not the point lies in the target region). We repeat an experiment SD_COUNT number of times to find an average probaility and standard deviation. I exported the files to CSV formats. They contain each co-ordinate for a program run, its success(S) or failure(F) code. It also has the probabilities for all SD_COUNT experiments, the mean probability and the standard deviation. You may have to scroll down quite a bit. Some of the CSV files can get very large very very quickly. If excel can't handle it, you may want to comment out the code which writes every outcome to the file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SD_COUNT 50
#define X_UPPER_LIMIT 0.5
#define X_LOWER_LIMIT -0.5
#define Y_UPPER_LIMIT 0.5
#define Y_LOWER_LIMIT -0.5
// these define the dimensions of our dart-board

int main()
{
  int N;
  printf("Enter number of test cases: ");
  scanf("%d", &N);
  double x;                    //x co-ordinate random variable
  double y;                    //y co-ordinate random variable
  double d;                    //distance of x from center
  int c = 0;                  //counts number of darts successfully hitting the target
  double prob[SD_COUNT];       //records probability for each iteration for calculating standard deviation
  double sd;                   //records the standard deviation for the run
  double mean = 0.0;           //records the mean for standard deviation.
  char *filename[20];         //stores a unique filename for N

  srand((unsigned) (time(0)));
  sprintf(filename, "data_N%d.csv", N);
  FILE *f = fopen(filename, "w");

  for(int k = 0 ; k < SD_COUNT ; k++)
  {
    for (int i = 0 ; i < N ; i++)
    {
      x = X_LOWER_LIMIT + (double) (rand()) /((double)(RAND_MAX/(X_UPPER_LIMIT-X_LOWER_LIMIT)));
      y = Y_LOWER_LIMIT + (double) (rand()) /((double)(RAND_MAX/(Y_UPPER_LIMIT-Y_LOWER_LIMIT)));
      d = sqrt(x*x + y*y);

      if (d <= (X_UPPER_LIMIT - x) && d <= (x - X_LOWER_LIMIT) && d <= (Y_UPPER_LIMIT - y) && d <= (y - Y_LOWER_LIMIT))
      {
        fprintf(f, "%d,%f,%f,S,,", (i + 1), x, y);
        if(i%1000 == 0)
        {
          fprintf(f, "\n");
        }
        c++;
        continue;
      }
      fprintf(f, "%d,%f,%f,F,,", (i + 1), x, y);
      if(i%1000 == 0)
      {
        fprintf(f, "\n");
      }
    }
    fprintf(f, "\n");
    prob[k] = (double)c/N;
    mean += prob[k];
    c = 0;
  }
  fprintf(f, "\nProbabilities\n\n");

  mean = (mean/SD_COUNT);
  for(int j = 0 ; j < SD_COUNT ; j++)
  {
    fprintf(f, "%d,%f\n", (j + 1), prob[j]);
    sd += (prob[j] - mean)*(prob[j] - mean);
  }
  sd = sqrt(sd);
  fprintf(f, "\n");
  fprintf(f, "Mean,%f\n", mean);
  fprintf(f, "Standard deviation,%d,%f", SD_COUNT, sd);
  fclose(f);

  return 0;
}
