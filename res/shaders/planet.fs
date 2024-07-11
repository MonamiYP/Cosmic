#version 410 core

out vec4 FragColor;

uniform vec3 u_color;

float near = 1; 
float far  = 100; 
  
float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main() {
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    FragColor = vec4(u_color * vec3((1-depth)/depth), 1.0);
    // FragColor = vec4(u_color, 1.0);
} 