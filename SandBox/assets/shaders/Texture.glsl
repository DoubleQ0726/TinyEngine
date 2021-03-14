#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 0) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 u_TexCoord;

void main()
{
	u_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
};

#shader fragment
#version 330 core

in vec2 u_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform float u_TilingFactor;

out vec4 color;

void main()
{
	color = texture(u_Texture, u_TexCoord * u_TilingFactor) * u_Color;
};