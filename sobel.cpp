#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cassert>

typedef struct pgm_image {
    int width;
    int height;
    int maxval;
    unsigned char* pixels;
} pgm_t;

pgm_t* new_pgm_image(const int width, const int height, const int maxval) {
    pgm_t* image = (pgm_t*)malloc(sizeof(pgm_t));
    assert(image);

    image->width = width;
    image->height = height;
    image->maxval = maxval;
    image->pixels = (unsigned char*)calloc(width * height, sizeof(unsigned char));
    assert(image->pixels);

    return image;
}

pgm_t* load_pgm_image_from_string(const std::string& pgm_data) {
    std::istringstream stream(pgm_data);
    assert(stream.good());

    char m1, m2;
    stream >> m1 >> m2;
    assert(m1 == 'P' && m2 == '2'); // Ensure it's a P2 format

    int width, height, maxval;
    stream >> width >> height >> maxval;

    pgm_t* image = new_pgm_image(width, height, maxval);

    for (int i = 0; i < width * height; i++) {
        int pixel_value;
        stream >> pixel_value;
        image->pixels[i] = (unsigned char)pixel_value;
    }

    return image;
}

std::string store_pgm_image_to_string(const pgm_t* image) {
    assert(image && image->pixels);
    std::ostringstream stream;

    stream << "P2\n";
    stream << image->width << " " << image->height << "\n";
    stream << image->maxval << "\n";

    for (int i = 0; i < image->width * image->height; i++) {
        stream << static_cast<int>(image->pixels[i]) << " ";
        if ((i + 1) % image->width == 0) {
            stream << "\n";
        }
    }

    return stream.str();
}

pgm_t* sobel_filter(const pgm_t* image) {
    int x, y, x_sum, y_sum;
    const int height = image->height, width = image->width;

    pgm_t* new_image = new_pgm_image(width, height, image->maxval);

    for (x = 1; x < height - 1; x++) {
        for (y = 1; y < width - 1; y++) {
            x_sum = (
                image->pixels[(x + 1) * width + (y + 1)] -
                image->pixels[(x + 1) * width + (y - 1)] +
                (image->pixels[(x) * width + (y + 1)] << 1) -
                (image->pixels[(x) * width + (y - 1)] << 1) +
                image->pixels[(x - 1) * width + (y + 1)] -
                image->pixels[(x - 1) * width + (y - 1)]
            );

            y_sum = (
                image->pixels[(x + 1) * width + (y + 1)] +
                (image->pixels[(x + 1) * width + (y)] << 1) +
                image->pixels[(x + 1) * width + (y - 1)] -
                image->pixels[(x - 1) * width + (y + 1)] -
                (image->pixels[(x - 1) * width + (y)] << 1) -
                image->pixels[(x - 1) * width + (y - 1)]
            );

            new_image->pixels[x * width + y] = static_cast<unsigned char>(
                std::sqrt(x_sum * x_sum + y_sum * y_sum)
            );
        }
    }

    return new_image;
}

int main() {
    // Example PGM image as a string
    std::string pgm_data =
        "P2\n"
        "5 5\n"
        "255\n"
        "0 0 0 0 0\n"
        "0 100 100 100 0\n"
        "0 100 255 100 0\n"
        "0 100 100 100 0\n"
        "0 0 0 0 0\n";

    // Load image from string
    pgm_t* img = load_pgm_image_from_string(pgm_data);

    // Apply Sobel filter
    pgm_t* filtered_img = sobel_filter(img);

    // Store image to string
    std::string filtered_pgm_data = store_pgm_image_to_string(filtered_img);

    // Print the resulting PGM string
    std::cout << "Filtered PGM Image:\n" << filtered_pgm_data;

    // Free allocated memory
    free(img->pixels);
    free(img);
    free(filtered_img->pixels);
    free(filtered_img);

    return 0;
}
