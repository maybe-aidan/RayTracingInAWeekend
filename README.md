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
- Emissive materials (lights)
- Anti-aliasing via multiple samples per pixel
- Depth of field
- Motion blur
- Bounding Volume Hierarchy (BVH) with Axis-Aligned Bounding Boxes (AABB)
- Output to `.ppm` image format

### In-Progress Features
- Volumetric rendering (e.g., fog, smoke)

### Example Renders

<table>
  <tr>
    <td>
      <strong>200 Samples per Pixel (Pre-Optimization)</strong><br>
      <em>Render time: ~15 minutes</em><br>
      <img src="https://github.com/maybe-aidan/RayTracingInAWeekend/blob/master/res/200Samples1200w.png?raw=true" width="100%">
    </td>
    <td>
      <strong>500 Samples per Pixel (Post-Optimization + Motion Blur)</strong><br>
      <em>Render time: ~5 minutes</em><br>
      <img src="https://github.com/maybe-aidan/RayTracingInAWeekend/blob/master/res/500Samples1200w.png?raw=true" width="100%">
    </td>
  </tr>
  <tr>
    <td>
      <strong>Cornell Box at 1000 Samples per Pixel</strong><br>
      <em>Render time: ~15 minutes</em><br>
      <img src="https://github.com/maybe-aidan/RayTracingInAWeekend/blob/master/res/cornell-box1000samples.png?raw=true" width="100%">
    </td>
    <td>
      <strong>Cornell Box at 10,000 Samples per Pixel (with a Glass Ball)</strong><br>
      <em>Render time: ~1 hour</em><br>
      <img src="https://github.com/maybe-aidan/RayTracingInAWeekend/blob/master/res/cornell10k.png?raw=true" width="100%">
    </td>
  </tr>
</table>

### Build Instructions

This project is built using **Microsoft Visual Studio Community 2022**, Version **17.11.2**.

### Steps:
1. Clone or download the repository.
2. Open the `.sln` file in Visual Studio.
3. Ensure the build configuration is set to `Release` or `Debug` as desired.
4. Under `Configuration Properties > Debugging > Command Arguments` add the following arguments:
<pre> > image.ppm </pre>
5. Build and Run the project (`Ctrl + F5` or click `Local Windows Debugger`).

### Dependencies
- [`stb_image`](https://github.com/nothings/stb): Header-only image loading library  
  (already included in the project, no setup required)
