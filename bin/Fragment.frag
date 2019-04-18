#version 330 core

out vec4 FragColor;

in vec2 FragPos;

vec2 cmpxmul(in vec2 a, in vec2 b) 
{
	return vec2(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
}

float cmpxmag(in vec2 c) 
{
    return sqrt(c.x * c.x + c.y * c.y);
}

vec4 Madelbrot(in vec2 c)
{
    vec2 res = c; 
    for (int i = 0; i < 200; i++)
    {
        res = cmpxmul(res, res) + c;
        if (cmpxmag(res) > 2.0)
        {
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
    FragColor = Madelbrot(FragPos);
}