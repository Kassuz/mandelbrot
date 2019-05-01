#version 330 core

#define PI 3.14159265359

out vec4 FragColor;

in vec2 FragPos;

uniform vec2 c;
uniform float time;

vec2 cmpxmul(in vec2 a, in vec2 b) 
{
	return vec2(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
}

float cmpxmag(in vec2 c) 
{
    return sqrt(c.x * c.x + c.y * c.y);
}

vec4 Julia(in vec2 z, in vec2 c)
{
    vec2 res = cmpxmul(z, z) + c; 
    for (int i = 0; i < 200; i++)
    {
        res = cmpxmul(res, res) + c;
        if (cmpxmag(res) > 2.0)
        {
            // return vec4(i / 250.0, (300 -i) / 300.0, (200 -i) / 220.0, 1.0);
            if (i > 190)   
                return vec4(1.0, 0.0, 0.75, 1.0);
            else if (i > 180)   
                return vec4(1.0, 0.0, 0.5, 1.0);
            else if (i > 170)   
                return vec4(1.0, 0.0, 0.25, 1.0);
            else if (i > 160)
                return vec4(1.0, 0.0, 0.0, 1.0);
            else if (i > 150)   
                return vec4(1.0, 0.25, 0.0, 1.0);
            else if (i > 140)
                return vec4(1.0, 0.5, 0.0, 1.0);
            else if (i > 130)
                return vec4(1.0, 0.75, 0.0, 1.0);
            else if (i > 120)
                return vec4(1.0, 1.0, 0.0, 1.0);
            else if (i > 110)
                return vec4(0.75, 1.0, 0.0, 1.0);
            else if (i > 100)
                return vec4(0.5, 1.0, 0.0, 1.0);
            else if (i > 90)
                return vec4(0.25, 1.0, 0.0, 1.0);
            else if (i > 80)
                return vec4(0.0, 1.0, 0.0, 1.0);
            else if (i > 70)
                return vec4(0.0, 1.0, 0.25, 1.0);
            else if (i > 60)
                return vec4(0.0, 1.0, 0.5, 1.0);
            else if (i > 50)
                return vec4(0.0, 1.0, 0.75, 1.0);
            else if (i > 40)
                return vec4(0.0, 1.0, 1.0, 1.0);
            else if (i > 30)
                return vec4(0.0, 0.75, 1.0, 1.0);
            else if (i > 20)
                return vec4(0.0, 0.5, 1.0, 1.0);
            else if (i > 10)
                return vec4(0.0, 0.25, 1.0, 1.0);
            else
                return vec4(0.0, 0.0, 1.0, 1.0);
        }
    }
    return vec4(0.0, 0.0, 0.0, 1.0);
}


void main()
{
    FragColor = Julia(FragPos, c);
}