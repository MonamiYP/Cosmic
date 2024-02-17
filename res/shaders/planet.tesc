#version 330 core

layout (vertices = 4) out;

uniform int u_outerTesselationLevel;
uniform int u_innerTesselationLevel;

void main() {
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    if (gl_InvocationID == 0) {
        gl_TessLevelOuter[0] = u_outerTesselationLevel;
        gl_TessLevelOuter[1] = u_outerTesselationLevel;
        gl_TessLevelOuter[2] = u_outerTesselationLevel;
        gl_TessLevelOuter[3] = u_outerTesselationLevel;

        gl_TessLevelInner[0] = u_innerTesselationLevel;
        gl_TessLevelInner[1] = u_innerTesselationLevel;
    }
}