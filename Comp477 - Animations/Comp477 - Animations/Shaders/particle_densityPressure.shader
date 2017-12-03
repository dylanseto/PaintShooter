#version 430

#define WORK_GROUP_SIZE 128

layout(local_size_x = WORK_GROUP_SIZE) in;

layout(location = 0) in vec3 position;

void main() {

}