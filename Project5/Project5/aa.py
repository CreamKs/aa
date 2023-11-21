import bpy

# 구의 반지름을 지정합니다.
radius = 1.0

# 구를 생성합니다.
bpy.ops.mesh.primitive_sphere_add(radius=radius)

# 각 꼭짓점의 법선벡터를 계산합니다.
for vertex in bpy.context.object.data.vertices:
    vertex.normal = (vertex.co - bpy.context.object.location).normalized()

# obj 파일로 저장합니다.
bpy.ops.export_scene.obj(filepath="sphere_normals.obj")