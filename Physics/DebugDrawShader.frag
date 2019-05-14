std::string fragmentCode = ""
"#version 450 core\n"
"out vec4 FragColor;\n"
"uniform vec3 color;\n"
"void main() {\n"
    "FragColor = vec4(color, 1.0);\n"
"}\n";
