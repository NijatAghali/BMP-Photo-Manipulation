#include "autoadjust.h"
int isBmpFile(char *file)
{
  char *dot = strrchr(file, '.');
  if (dot != NULL && strcmp(dot, ".bmp") == 0)
  {
    return 1;
  }
  else
  {
    return -1;
  }
}

int main(int argc, char *argv[])
{
  // usage
  if (argc == 4)
  {
    if (strcmp(argv[2], "-o") == 0)
    {
      if (isBmpFile(argv[1]) != -1 && isBmpFile(argv[3]) != -1)
      {
        char *filename = argv[1];
        char *destname = argv[3];
        loadBMP(filename, destname);
      }
      else
      {
        printf("ERROR: you must provide a .bmp file name\n");
        return -1;
      }
    }
  }
  else if (strcmp(argv[1], "-h") == 0) // help flag
  {
    printf("Should be like \n\t./adjust source.bmp -o destination.bmp or\n\t./adjust source.bmp  > destination.bmp\n");
  }
  else
    printf("Invalid Usage\nUse -h for usage help\n");
  return 0;
}

void loadBMP(char *fileName, char *destName)
{
  FILE *file = fopen(fileName, "rb");
  if (file == NULL)
    printf("Please give an valid filename");

  // Reading Bit Header
  fread(bit_header.bfName, 2, 1, file);
  fread(&bit_header.bfSize, 3 * sizeof(int), 1, file);

  // Reading Dib Header
  fread(&dib_header, sizeof(struct DIB_Header), 1, file);
  dib_header.garbage = (char *)malloc(sizeof(char) * (dib_header.dbSize + 14));

  fseek(file, 0, SEEK_SET);
  fread(dib_header.garbage, sizeof(char), (dib_header.dbSize + 14), file);

  int nOfPixels = dib_header.dbWidth * dib_header.dbHeight; // number of pixels
  int n = dib_header.dbNofPixels / 8;

  struct Pixels *arr = malloc(nOfPixels * sizeof(struct Pixels));
  int pix;

  // Reading BMP File
  for (int i = 0; i < nOfPixels; i++)
  {
    if (dib_header.dbNofPixels == 32)
    {
      fread(&pix, 1, 1, file);
      arr[i].alpha = pix;
    }
    fread(&pix, 1, 1, file);
    arr[i].blue = pix;
    fread(&pix, 1, 1, file);
    arr[i].green = pix;
    fread(&pix, 1, 1, file);
    arr[i].red = pix;
  }

  // Finding Minimum Pixel
  int min = arr[0].red;
  for (int i = 0; i < nOfPixels; i++)
  {
    if (arr[i].red < min)
      min = arr[i].red;
    if (arr[i].green < min)
      min = arr[i].green;
    if (arr[i].blue < min)
      min = arr[i].blue;
  }

  // Finding Maximum Pixel
  int max = arr[0].red;
  for (int i = 0; i < nOfPixels; i++)
  {
    if (arr[i].red > max)
      max = arr[i].red;
    if (arr[i].green > max)
      max = arr[i].green;
    if (arr[i].blue > max)
      max = arr[i].blue;
  }

  // Brigthness
  for (int i = 0; i < nOfPixels; i++)
  {
    arr[i].red -= min;
    arr[i].green -= min;
    arr[i].blue -= min;

    if (arr[i].red < 0)
      arr[i].red = 0;
    if (arr[i].green < 0)
      arr[i].green = 0;
    if (arr[i].blue < 0)
      arr[i].blue = 0;
  }

  // Contrast
  double c;
  c = (double)255 / (max - min);
  for (int i = 0; i < nOfPixels; i++)
  {

    arr[i].red = arr[i].red * c;
    arr[i].green = arr[i].green * c;
    arr[i].blue = arr[i].blue * c;

    if (arr[i].red > 255)
      arr[i].red = 255;
    if (arr[i].green > 255)
      arr[i].green = 255;
    if (arr[i].blue > 255)
      arr[i].blue = 255;
  }

  // Write into New File
  FILE *fp = fopen(destName, "w");

  fwrite(dib_header.garbage, sizeof(char), (dib_header.dbSize + 14), fp);

  for (int i = 0; i < nOfPixels; i++)
  {
    if (dib_header.dbNofPixels == 32)
    {
      fwrite(&arr[i].alpha, 1, 1, fp);
    }
    fwrite(&arr[i].blue, 1, 1, fp);
    fwrite(&arr[i].green, 1, 1, fp);
    fwrite(&arr[i].red, 1, 1, fp);
  }
  fclose(file);
  fclose(fp);
}