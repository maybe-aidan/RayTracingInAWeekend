#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

#include <chrono>

class camera {
public:
	double aspect_ratio   = 1.0; // W / H
	int image_width       = 100; // Image width pixel count
	int samples_per_pixel = 10;
	int max_depth = 10;

	double vfov = 90; // Vertical view angle
	point3 lookfrom = point3(0, 0, 0); // origin vector
	point3 lookat = point3(0, 0, -1); // LookAt vector
	vec3 vup = vec3(0, 1, 0); // Up vector

	double defocus_angle = 0;
	double focus_dist = 10;

	color background;


	void render(const hittable& world) {
		auto start = std::chrono::high_resolution_clock::now();

		initialize();
		std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

		for (int j = 0; j < image_height; j++) {
			int percent = ((j * 1.0) / image_height) * 100;
			std::ostringstream oss;
			oss << "\rScanlines remaining: " << (image_height - j)
				<< ", " << percent << "% complete";
			std::string output = oss.str();
			output.resize(80, ' ');
			std::clog << output << std::flush;
			for (int i = 0; i < image_width; i++) {
				color pixel_color(0, 0, 0);
				for (int sample = 0; sample < samples_per_pixel; sample++) {
					ray r = get_ray(i, j);
					pixel_color += ray_color(r, max_depth, world);
				}
				write_color(std::cout, pixel_samples_scale * pixel_color);
			}
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

		std::ostringstream oss;
		oss << "\rFinished Rendering in " << duration.count() << " seconds.";
		std::string output = oss.str();
		output.resize(80, ' ');
		std::clog << output << std::flush;

		std::clog << "\n\nPress [ENTER] to close..." << std::endl;
		std::cin.get();
	}

private:
	int image_height;
	double pixel_samples_scale;
	point3 center;
	point3 pixel00_loc;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;

	vec3 u, v, w; // Camera frame basis vectors

	vec3 defocus_disk_u;
	vec3 defocus_disk_v;

	void initialize() {
		image_height = int(image_width / aspect_ratio);
		image_height = (image_height < 1) ? 1 : image_height;

		pixel_samples_scale = 1.0 / samples_per_pixel;

		center = lookfrom;

		auto theta = degrees_to_radians(vfov);
		auto h = std::tan(theta / 2);
		auto viewport_height = 2 * h * focus_dist;
		auto viewport_width = viewport_height * (double(image_width) / image_height);

		// Calculate the basis vectors for the camera coordinate frame
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w)); 
		v = cross(w, u); 

		// Calculate the vectors across the horizontal and down the vertical viewport edges
		auto viewport_u = viewport_width * u;
		auto viewport_v = viewport_height * -v;

		// Calcualte the horizontal and vertical delta vectors from pixel to pixel.
		pixel_delta_u = viewport_u / image_width;
		pixel_delta_v = viewport_v / image_height;

		// Calculate location of the upper left pixel
		auto viewport_upper_left = center - focus_dist*w - viewport_u / 2 - viewport_v / 2;

		pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

		auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
		defocus_disk_u = u * defocus_radius;
		defocus_disk_v = v * defocus_radius;
	}

	ray get_ray(int i, int j) {
		auto offset = sample_square();
		auto pixel_sample = pixel00_loc
			+ ((i + offset.x()) * pixel_delta_u)
			+ ((j + offset.y()) * pixel_delta_v);

		auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
		auto ray_direction = pixel_sample - ray_origin;
		auto ray_time = random_double();

		return ray(ray_origin, ray_direction, ray_time);

	}

	vec3 sample_square() const {
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	point3 defocus_disk_sample() const {
		auto p = random_in_unit_disk();
		return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
	}

	color ray_color(const ray& r, int depth, const hittable& world) const {
		if (depth <= 0) {
			return color(0, 0, 0);
		}

		hit_record rec;

		if (!world.hit(r, interval(0.001, infinity), rec)) {
			return background;
		}

		ray scattered;
		color attentuation;

		color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

		if (!rec.mat->scatter(r, rec, attentuation, scattered))
			return color_from_emission;
		
		color color_from_scatter = attentuation * ray_color(scattered, depth - 1, world);

		return color_from_emission + color_from_scatter;
	}
};

#endif
