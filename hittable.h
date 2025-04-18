#ifndef HITTABLE_H
#define HITTABLE_H

#include "aabb.h"
#include "rtweekend.h"

class material;

class hit_record {
public:
	point3 p;
	vec3 normal;
	shared_ptr<material> mat;
	double t;
	double u;
	double v;
	bool front_face;

	void set_face_normal(const ray& r, const vec3& outward_normal) {
		// Sets hit record normal vector
		// NOTE: outward_normal is assumed to be unit length

		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable {
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;

	virtual aabb bounding_box() const = 0;
};

class translate : public hittable {
public:
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
		ray offset_r(r.origin() - offset, r.direction(), r.time());
	}

private:
	vec3 offset;
	shared_ptr<hittable> object;
};

#endif
