#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct pgm_image {
	int width;
	int height;
	int maxval;
	unsigned char *pixels; 
} pgm_t;

pgm_t *new_pgm_image(const int width, const int height, const int maxval)
{
	pgm_t *image = malloc(sizeof(pgm_t));
	assert(image);

	image->width = width;
	image->height = height;
	image->maxval = maxval;
	image->pixels = (unsigned char *) calloc(width * height , sizeof(unsigned char));
	assert(image->pixels);

	return image;
}

void skip_comments(FILE *file)
{
	char c;

	fscanf(file, " %c", &c);
	if (c == '#') {
		while (fgetc(file) != '\n');
	}
	else {
		fseek(file, -1, SEEK_CUR);
	}
}



pgm_t *load_pgm_image(const char *filename)
{
	int i=0;
	FILE *file = fopen(filename, "rb");
	assert(file);
	char width_string[6], height_string[6], maxval_string[6];
	int width, height, maxval;
	char m1, m2;

	

	skip_comments(file);
	fscanf(file, "%c%c", &m1, &m2);
	skip_comments(file);
	fscanf(file, " %s", width_string);
	width = atoi(width_string);

	skip_comments(file);
	fscanf(file, " %s", height_string);
	height = atoi(height_string);
	
	skip_comments(file);
	fscanf(file, " %s", maxval_string);
	maxval = atoi(maxval_string);

	

	pgm_t *image = new_pgm_image(width, height, maxval);



	skip_comments(file);
	for (i = 0; i < width * height; i++) {
        int pixel_value;
        fscanf(file, "%d", &pixel_value);
        image->pixels[i] = (unsigned char)pixel_value;
    }

	fclose(file);
	return image;
}



void store_pgm_image(const pgm_t *image, const char *filename)
{
	int i;
    assert(image && image->pixels);
    FILE *file = fopen(filename, "w"); // Open in text mode for P2 format
    assert(file);

    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", image->width, image->height);
    fprintf(file, "%d\n", image->maxval);


    for (i = 0; i < image->width * image->height; i++) {
        fprintf(file, "%d ", image->pixels[i]);
        if ((i + 1) % image->width == 0) {
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

pgm_t *sobel_filter(const pgm_t *image)
{
	register int x,y;
	register int x_sum, y_sum;
	const register int height = image->height, width = image->width;
	const int maxval = image->maxval;
	pgm_t *new_image = new_pgm_image(width, height, image->maxval);
	
	for (x = 1; x < height - 1; x++) {
		for (y = 1; y < width - 1; y++) {
			x_sum = (
				image->pixels[(x + 1)*width + (y + 1)] -
				image->pixels[(x + 1)*width + (y - 1)] +
				(image->pixels[   (x)*width + (y + 1)] << 1) -
				(image->pixels[   (x)*width + (y - 1)] << 1) +
				image->pixels[(x - 1)*width + (y + 1)] -
				image->pixels[(x - 1)*width + (y - 1)]
			);

			y_sum = (
				image->pixels[ (x + 1)*width + (y + 1)] +
				(image->pixels[(x + 1)*width + (y)    ] << 1) +
				image->pixels[ (x + 1)*width + (y - 1)] -
				image->pixels[ (x - 1)*width + (y + 1)] -
				(image->pixels[(x - 1)*width + (y)    ] << 1) -
				image->pixels[ (x - 1)*width + (y - 1)]
			);

			new_image->pixels[x * width + y] = sqrt(x_sum * x_sum + y_sum * y_sum);
		}
	}

	return new_image;
}


int main() {
	pgm_t *img = load_pgm_image("./dog.pgm");
	img = sobel_filter(img);
	store_pgm_image(img,"./dog2.pgm");
	return 0;
}
