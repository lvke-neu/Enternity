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
