# Enternity
My GameEngine Based on OpenGL

Blending:red is under the blue 
	ps shder(blue) ----> framebuffer(red)
	source: ps shder output
	destination: framebuffer

Batch Rendering

Ref的目的：为了不复制资源，我们用const T&，但是在多线程渲染或者其他场景下，在堆上创建的资源可能已经被释放了，所以使用Ref:addRef, Ref:release


Entity Component System(ECS 实体对象系统):Data drived
Scene---->GameObjects------>Components
场景需要能够存储实体
Entity:实体  Component:组件（数据） System: 方法/功能


mesh.bin

header:
	unsigned int VertexCount(顶点类型 默认写死，float3:position, float3:normal, float2:texcoord)
	unsigned int IndexCount(索引类型 默认写死，unsigned int)


模板缓冲:
	1、启用模板缓冲的写入。
	2、渲染物体，更新模板缓冲的内容。
	3、禁用模板缓冲的写入。
	4、渲染（其它）物体，这次根据模板缓冲的内容丢弃特定的片段。
	

Box2d: 
	1、world 
	2、rigidBody:刚体（静态刚体， 动态刚体）
	3、collider：对撞机