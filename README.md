# OpenGl-Tutorial



# Rotate around the (1,1,-1) axis

### Rotate with cross product

>���������� ��� �� ������������� �� ����������� ���� ��  ������������ ����� ����� ��������� ��� ������������ ����� ��� ������������ ��� ������� ��������� �������� �� ��� ����� ��� ������� �� ������������� ��� �� ������� ��� ����� �����������.����� ��������� �� ����� ������� ���� ������������ ����� ��� ��� ����� ����������� ��� ������� ��� ����������.


<br>
<video src="./Figs/cross_rotation.mp4" controls="controls" width="320" height="200" autoplay style="float: left;">
</video>

```cpp
vec3 temp(1,1,-1);
vec3 Z(0, 0, -1);
temp = normalize(temp);
vec3 prod = cross(temp, Z);
float angle = acos(dot(temp, Z));
mat4 rotation = glm::rotate(mat4(), angle, prod);

```

<br>
<br>
<br>

### Rotate with Projection Maths

<br>
<video src="Projection_rotation.mp4" controls="controls" width="320" height="200" autoplay style="float: left;">
</video>

```cpp
vec3 temp(1, 1, -1);
float norm = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
float l = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
float angle_z = acos(temp.y / l);
float angle_x = acos(l / norm);
mat4 Rotation1 = glm::rotate(mat4(), -angle_z, vec3(0.0, 0.0, 1.0));
mat4 Rotation2 = glm::rotate(mat4(), -angle_x, vec3(1.0, 0.0, 0.0));

cubeMVP = view *rotation  *cubeScaling;

```

### Rotate Round An Axis
>�� ������� �� ��������� ��� ������ ������������ ��� �� ����������� ����� ������� �������������� �� �� __`view`__ ��� ���� �� ��� __`rotate`__,��� �� ������� �� ������� ���� ��� ������������� ����������� ����� �������  __`rotate`__ ��� ���� __`view`__


<br>

<video src="view_rotation.mp4" controls="controls" width="320" height="200" autoplay style="float: left;">
</video>


```cpp
 mat4 cubeMVP = rotation*view * cubeRotation *cubeScaling;

```

<br>

<br>
<br>
<br>
<br>
<br>

#### ����������
```
�� �������� ��� ������� � ���������� ���� ����� ���������������� ���� ��� ������ �� ���� ����������
```


___
<br>

## ������� ������

-  ```cpp 
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
    ```
    >����� ��� �� ��� �� ����������� �� ������� ,�� ��������� �� ��������� (GL_FILL) � ���� �� ���������� ������� ��� ������� ��� ������� 

<br>   
  

- ```cpp
    mat4 view = lookAt(
            vec3(0.2 * sin(time), 0, 0.2 * cos(time)),//position
            vec3(0.0f, 0.0f, 0.0f),//where to look at
            vec3(0.0f, 1.0f, 0.0f)//up vector
        );
    ```
    >��� �� ����� ��� ��������� ������ ���� ��� ��� y ,��� ��� ������� x-z

<br>

- ```cpp
    mat4 rotation = glm::rotate(mat4(), angle, prod);
    ```
    >angle:����� ����������� ,prod:������ �����������




