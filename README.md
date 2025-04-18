# Ray Tracing in a Weekend  
## A Simple Ray Tracing Renderer

This is a basic ray tracer that renders a scene composed of spheres to a `.ppm` image file. It was built by following the excellent book [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

### Features
- Ray-sphere intersection
- Multiple material types:
  - Lambertian (diffuse)
  - Metal
  - Dielectric (glass, water, etc.)
- Texture Mapping
- Procedural Noise (e.g., Perlin noise)
- Support for additional geometric primitives (e.g., triangles, quads)
- Anti-aliasing via multiple samples per pixel
- Depth of field
- Motion blur
- Bounding Volume Hierarchy (BVH) with Axis-Aligned Bounding Boxes (AABB)
- Output to `.ppm` image format

### In-Progress Features
- Area and point lights
- Volumetric rendering (e.g., fog, smoke)

### Example Renders

**200 Samples per Pixel (Pre-Optimization)**  
_Render time: ~15 minutes_  
![Pre-Optimization Render](https://github.com/maybe-aidan/RayTracingInAWeekend/blob/master/res/200Samples1200w.png?raw=true)  

**500 Samples per Pixel (Post-Optimization + Motion Blur)**  
_Render time: ~5 minutes_  
![Post-Optimization Render](https://github.com/maybe-aidan/RayTracingInAWeekend/blob/master/res/500Samples1200w.png?raw=true) 
