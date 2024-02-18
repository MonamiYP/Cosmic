#version 410 core

layout (quads, equal_spacing, ccw) in;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_radius;

void main() {
    // Position location within patch of vertex
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // Get the positions of the 4 quad vertices
    vec4 p00 = gl_in[0].gl_Position; 
    vec4 p10 = gl_in[1].gl_Position;
    vec4 p01 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    vec4 p0 = (p10 - p00) * u + p00;
    vec4 p1 = (p11 - p01) * u + p01;
    vec4 p = (p1 - p0) * v + p0;

    float l = length(p);
    float scale = u_radius/l;

    vec4 scaledP = vec4(p.x * scale, p.y * scale, p.z * scale, p.w);

    gl_Position = u_projection * u_view * u_model * scaledP;
}