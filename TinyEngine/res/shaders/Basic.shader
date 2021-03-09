#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0);
};

#shader fragment
#version 330 core

out vec4 color;


void main()
{
	color = vec4(0.2, 0.3, 0.5, 1.0);
};